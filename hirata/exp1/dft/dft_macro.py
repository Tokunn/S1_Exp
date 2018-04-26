#!/usr/bin/env python3
import os
import subprocess
import shutil

def main():
    if not os.path.exists('./imgs'):
        os.mkdir('./imgs')

    waveslist = os.listdir('../../waves')
    for wave in waveslist:
        cmd = "./a.out " + "../../waves/" + wave
        print(cmd)
        subprocess.call(cmd.split())
        cmd = "./plot.sh"
        print(cmd)
        subprocess.call(cmd)
        shutil.move("./imgoutput.png", "./imgs/{0}.png".format(wave[:-4]))


if __name__ == "__main__":
    main()
