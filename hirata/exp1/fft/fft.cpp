#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const int N = 4096;


void fft(std::vector<double> xr, std::vector<double> xi, double *Xr, double *Xi, int Nn )
/*	xr, xi: 信号の実数部と虚数部の配列
	Xr, Xi: フーリエスペクトルの実数部と虚数部の配列
	N: 信号長						*/
{
  int i, j, k, n, n2;
  double theta, wr, wi, *rbuf, *ibuf;

  /* 配列領域確保 */
  rbuf = (double*)calloc( sizeof(double), Nn );
  ibuf = (double*)calloc( sizeof(double), Nn );

  /* xr[]とxi[]をビットリバーサルしたものをrbuf[]とibuf[]に格納 */
  i = j = 0 ;
  rbuf[j] = xr[j];  ibuf[j] = xi[j];
  for( j = 1 ; j < Nn-1 ; j++ ) {
    for( k = Nn/2 ; k <= i ; k /= 2 )  i -= k;
    i += k;
    rbuf[j] = xr[i];  ibuf[j] = xi[i];
  }
  rbuf[j] = xr[j];  ibuf[j] = xi[j];

  /* バタフライ演算 */
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
        /*
        ここにバタフライ演算（下式）を入れる。
        　X[j] = 1*buf[j] + W*buf[k];
        　X[k] = 1*buf[j] - W*buf[k];
        */
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
        //tmp_wavedata = tmp_wavedata * (0.54 - 0.46 * cos(2*M_PI*i/(N-1)));
        //std::cout << "[" << tmp_wavedata << "]" << std::endl;
        wavedata_r.push_back(tmp_wavedata);
    }
    for (int i =0 ; i < N; i++) {
        wavedata_r[i] = wavedata_r[i] * (0.54 - 0.46 * cos(2*M_PI*i/(N-1)));
        //std::cout << "[" << wavedata_r[i] << "]" << std::endl;
    }

    //std::cout << wavedata_r.size() << std::endl;

    fft(wavedata_r, wavedata_i, Xr, Xi, N);

    for (int i = 0; i < N; i++) {
        double tmp_power, log_power;
        //std::cout << Xi[i] << std::endl;
        tmp_power = Xr[i]*Xr[i] + Xi[i]*Xi[i];
        log_power = 10 * log10(tmp_power);
        powersp.push_back(log_power);
        //std::cout << i << "\t" <<  log_power << std::endl;
        ofs << i << "\t" <<  log_power << std::endl;
        //ofs << log_power << std::endl;
    }

    ofs.close();

    //std::cout << powersp.size() << std::endl;
    return 0;
}
