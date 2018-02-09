#!/usr/bin/env python

import os
import shutil

dsid = "157622"
dsname = "Pythia_AUET2B_CTEQ6L1_GGMHiggsinoNLSP_1000_500_30_Zll"

incl_path = "00-14-81/Generators/MC12JobOptions/common/"
incl1 = "Pythia_AUET2B_CTEQ6L1_Common.py"
incl2 = "Pythia_Base_Fragment.py"

jobopt = "MC12."+dsid+"."+dsname+".py"
jobopt_path = "00-14-81/Generators/MC12JobOptions/share/DSID"+dsid[:3]+"xxx/"

# Write new job options file
new_opts = open("Samples/"+jobopt, "w")
with open(jobopt_path+jobopt) as f:
    for line in f.readlines():
        new_opts.write(line.replace("MC12JobOptions", "Samples/").replace("slha_file = ", "slha_file = "+jobopt_path))
new_opts.close()

# Write new included file
new_incl = open("Samples/"+incl1, "w")
with open(incl_path+incl1) as f:
    for line in f.readlines():
        new_incl.write(line.replace("MC12JobOptions/", incl_path))
new_incl.close()

command = "Generate_trf.py ecmEnergy=13000"
command += " runNumber="+dsid
command += " firstEvent=1 maxEvents=5000 randomSeed=1"
command += " jobConfig=Samples/MC12."+dsid+"."+dsname+".py"
command += " outputEVNTFile=Samples/EVNT."+dsid+"."+dsname+".root"

print command
os.system(command)

