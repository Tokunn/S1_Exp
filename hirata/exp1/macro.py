#!/usr/bin/env python3
import os
import subprocess
import shutil

WAVEDIR = "../waves/"
TIMEMES = "./measuretime.sh"
TMPIMG = "imgoutput.png"
IMGDIR = "imgs/"
PLOT = "./plot.sh"

DFTAPP = "dft/a.out"
DFTDIR = "dft/"
DFTPLOT = DFTDIR + "plot.sh"
DFTIMGDIR = IMGDIR + "dft_imgs/"

FFTAPP = "fft/a.out"
FFTDIR = "fft/"
FFTPLOT = FFTDIR + "plot.sh"
FFTIMGDIR = IMGDIR + "fft_imgs/"

def main():
    print("##################### START ####################")
    if not os.path.exists(IMGDIR):
        os.mkdir(IMGDIR)

    print("##################### TIME ####################")
    cmd = TIMEMES
    subprocess.call(cmd.split())

    print("\n\n##################### DFT ####################")
    if not os.path.exists(DFTIMGDIR):
        os.mkdir(DFTIMGDIR)
    waveslist = os.listdir(WAVEDIR)
    print(waveslist)
    for wave in waveslist:
        cmd = DFTAPP + " " + WAVEDIR + wave
        print(cmd)
        subprocess.call(cmd.split())
        cmd = PLOT
        print(cmd)
        subprocess.call(cmd)
        shutil.move(TMPIMG, DFTIMGDIR + "{0}.png".format(wave[:-4]))


    print("\n\n##################### FFT ####################")
    if not os.path.exists(FFTIMGDIR):
        os.mkdir(FFTIMGDIR)
    waveslist = os.listdir(WAVEDIR)
    print(waveslist)
    for wave in waveslist:
        cmd = FFTAPP + " " + WAVEDIR + wave
        print(cmd)
        subprocess.call(cmd.split())
        cmd = PLOT
        print(cmd)
        subprocess.call(cmd)
        shutil.move(TMPIMG, FFTIMGDIR + "{0}.png".format(wave[:-4]))


if __name__ == "__main__":
    main()
