#!/usr/bin/env python

import os

# Make lists of datasets used
signal_ids = []
background_sets = []

EVNT_dir = "/afs/cern.ch/work/t/tholmes/ZMETSamples/Signal/"
for file in os.listdir(EVNT_dir+"EVNT"):
    if file.startswith("EVNT."):

        id = file.split(".")[1]
        name = file.split(".")[2]
        signal_ids+=[id]

        rundir_loc = "/afs/cern.ch/work/t/tholmes/ZMETSamples/Signal/TRUTH/Run_"+id
        if not os.path.exists(rundir_loc):
            os.makedirs(rundir_loc)

        new_job = open("RunScripts/job_makeTRUTH_"+id+".sh", "w")
        with open('job_template_TRUTH.sh') as f:
            for line in f.readlines():
                newline = line.replace("__INPUT__", EVNT_dir+"EVNT/"+file)
                newline = newline.replace("__OUTDIR__", EVNT_dir+"TRUTH/Run_"+id)
                newline = newline.replace("__OUTPUT__", file.split("EVNT.")[1])
                new_job.write(newline)
        new_job.close()
        os.chmod("RunScripts/job_makeTRUTH_"+id+".sh", 0755)

sub_script = open("submit_TRUTH.sh", "w")
for id in signal_ids:
    sub_script.write("bsub -q 1nd -o Logs/out_makeTRUTH_"+id+".txt RunScripts/job_makeTRUTH_"+id+".sh \n")
sub_script.close()
