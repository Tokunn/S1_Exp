#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const int N = 4096;

void dft(std::vector<double> xr, std::vector<double> xi, double *Xr, double *Xi, int N )
/*	xr, xi: 信号の実数部と虚数部の配列
	Xr, Xi: フーリエスペクトルの実数部と虚数部の配列
	N: 信号長						*/
{
  int k, n;

  for( k = 0 ; k < N ; k++ ) {
    for( n = 0 ; n < N ; n++ ) {
       //ここにDFTの計算を入れる 
       Xr[k] += xr[n] * cos(2*M_PI*n*k/N) + xi[n] * sin(2*M_PI*n*k/N);
       Xi[k] += xi[n] * cos(2*M_PI*n*k/N) - xr[n] * sin(2*M_PI*n*k/N);
    }
   //std::cout << Xr[k] << std::endl;
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

    dft(wavedata_r, wavedata_i, Xr, Xi, N);

    for (int i = 0; i < N; i++) {
        double tmp_power, log_power;
        //std::cout << Xi[i] << std::endl;
        tmp_power = Xr[i]*Xr[i] + Xi[i]*Xi[i];
        log_power = 10 * log10(tmp_power);
        powersp.push_back(log_power);
        //std::cout << log_power << std::endl;
        ofs << i*44100.0/4096.0 << "\t" <<  log_power << std::endl;
    }

    ofs.close();

    //std::cout << powersp.size() << std::endl;
    return 0;
}
