#!/usr/bin/env python3
import os
import subprocess

def main():
    waveslist = os.listdir('../../waves')
    for wave in waveslist:
        cmd = "./a.out " + "../../waves/" + wave
        print(cmd)
        subprocess.call(cmd.split())
        cmd = ["gnuplot",  "-e", "\"set term png; set output '{0}.png'; plot 'output.csv' with lines\"".format(wave[:-4])]
        print(cmd)
        subprocess.call(cmd)


if __name__ == "__main__":
    main()
