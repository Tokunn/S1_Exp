#!/usr/bin/env python3
import os
import subprocess
import shutil

WAVEDIR = "../waves/"
TMPIMG = "imgoutput.png"
IMGDIR = "imgs/"

FFTAPP = "fft/a.out"
FFTDIR = "fft/"
FFTPLOT = FFTDIR + "plot.sh"
FFTIMGDIR = IMGDIR + "fft_imgs/"

def main():
    if not os.path.exists(IMGDIR):
        os.mkdir(IMGDIR)


    if not os.path.exists(FFTIMGDIR):
        os.mkdir(FFTIMGDIR)

    waveslist = os.listdir(WAVEDIR)
    print(waveslist)
    for wave in waveslist:
        cmd = FFTAPP + " " + WAVEDIR + wave
        print(cmd)
        subprocess.call(cmd.split())
        cmd = FFTPLOT
        print(cmd)
        subprocess.call(cmd)
        shutil.move(TMPIMG, FFTIMGDIR + "{0}.png".format(wave[:-4]))


if __name__ == "__main__":
    main()
