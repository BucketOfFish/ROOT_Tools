import subprocess
import os
import shutil
import argparse

class bcolors:
    BLUE = '\033[95m'
    LIGHT = '\033[94m'
    ORANGE = '\033[91m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    ENDC = '\033[0m'


def main():
    parser = argparse.ArgumentParser("Download all samples matching the specified string (expanding wildcards) and remove any empty files.")
    parser.add_argument("sample", nargs="+", help = "The sample or samples (or wildcarded expressions) to download.")
    
    args = parser.parse_args()

    for sample in args.sample:
        out, err = subprocess.Popen(["rucio", "list-dids", sample], stdout=subprocess.PIPE, stderr=subprocess.PIPE).communicate()
        for line in out.split('\n'):
            if ("COLLECTION" in line or "CONTAINER" in line) and not "tid" in line:
                d = line.split()[0].split(":")[1]
                print ""
                print "Downloading sample:", bcolors.BOLD + bcolors.LIGHT + d + bcolors.ENDC
                print ""
                subprocess.Popen(["rucio","download",d]).wait()
                flist, ferr = subprocess.Popen(["rucio","list-files",d], stdout=subprocess.PIPE, stderr=subprocess.PIPE).communicate()
                print ""
                for info in flist.split('\n'):
                    if "root" not in info: 
                        continue
                    if int(info.split()[-1]) == 0:
                        empty = info.split()[0].split(":")[1]
                        print "Found an empty file, removing:", bcolors.BOLD + bcolors.ORANGE + empty + bcolors.ENDC
                        os.remove(os.path.join(d, empty))
                print ""
                print "Finished sample:", bcolors.BOLD + bcolors.LIGHT + d + bcolors.ENDC
                print ""


if __name__ == "__main__":
    main()
