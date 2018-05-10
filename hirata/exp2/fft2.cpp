#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>

const int SEP = 128;
const int N = 4096;


void fft(std::vector<double> xr, std::vector<double> xi, double *Xr, double *Xi, int Nn )
{
  int i, j, k, n, n2;
  double theta, wr, wi, *rbuf, *ibuf;

  /*double sum = 0;
  for (i = 0; i < Nn; i++) {
      //std::cout << xr[i] << " ";
      sum += xr[i];
  }
  std::cout << sum << std::endl;*/

  rbuf = (double*)calloc( sizeof(double), Nn );
  ibuf = (double*)calloc( sizeof(double), Nn );

  i = j = 0 ;
  rbuf[j] = xr[j];  ibuf[j] = xi[j];
  for( j = 1 ; j < Nn-1 ; j++ ) {
    for( k = Nn/2 ; k <= i ; k /= 2 )  i -= k;
    i += k;
    rbuf[j] = xr[i];  ibuf[j] = xi[i];
  }
  rbuf[j] = xr[j];  ibuf[j] = xi[j];

  theta = -2.0*M_PI;
  for( n = 1 ; ( n2 = n*2 ) <= Nn ; n = n2 ) {
    theta *= 0.5;
    for ( i = 0 ; i < n ; i++ ) {
      wr = cos(theta*i);  wi = sin(theta*i);
      for ( j = i ; j < Nn ; j += n2 ) {
        k = j + n;
        Xr[j] = 1*rbuf[j] + (wr*rbuf[k] - wi*ibuf[k]);
        Xi[j] = 1*ibuf[j] + (wr*ibuf[k] + wi*rbuf[k]);
        Xr[k] = 1*rbuf[j] - (wr*rbuf[k] - wi*ibuf[k]);
        Xi[k] = 1*ibuf[j] - (wr*ibuf[k] + wi*rbuf[k]);
          }
    }
    for( i = 0 ; i < Nn ; i++ ) {
      rbuf[i] = Xr[i];
      ibuf[i] = Xi[i];
    }
  }
}



int main(int argc, char **argv) {
    char *filename;
    char defaultname[] = "../../waves/sinewave.txt";

    if (argc > 1) {
        filename = argv[1];
    }
    else {
        filename = defaultname;
    }
    std::ifstream ifs (filename, std::ifstream::in);
    std::ofstream ofs ("./output.csv");
    std::vector<double> wavedata_r;
    std::vector<double> wavedata_i(N, 0);
    std::vector<double> sep_wavedata_r(N/SEP, 0);
    std::vector<double> sep_wavedata_i(N/SEP, 0);
    std::string str;
    double Xr[N], Xi[N];
    std::vector<double> powersp;

    if (ifs.fail()) {
        printf("File open failed\n");
        return -1;
   }
    while (getline(ifs, str)) {
        double tmp_wavedata;
        tmp_wavedata = std::stof(str);
        wavedata_r.push_back(tmp_wavedata);
    }
    for (int i = 0; i < N; i+=N/SEP) {
        std::copy(wavedata_r.begin()+i, wavedata_r.begin()+i+N/SEP, sep_wavedata_r.begin());
        for (int j = 0 ; j < N/SEP; j++) {
            sep_wavedata_r[j] = sep_wavedata_r[j] * (0.54 - 0.46 * cos(2*M_PI*i/(N/SEP)/(N/SEP-1)));
        }

        fft(sep_wavedata_r, sep_wavedata_i, &Xr[i], &Xi[i], N/SEP);

        for (int j = 0; j < N/SEP; j++) {
            double tmp_power, log_power;
            tmp_power = Xr[j+i]*Xr[j+i] + Xi[j+i]*Xi[j+i];
            log_power = 10 * log10(tmp_power);
            powersp.push_back(log_power);
            //ofs << j*44100.0/4096.0 << "\t" <<  log_power << std::endl;
            ofs << i/(N/SEP) << "\t" << j*44100.0/4096.0 << "\t" <<  log_power << std::endl;
        }
    }


    ofs.close();

    return 0;
}
