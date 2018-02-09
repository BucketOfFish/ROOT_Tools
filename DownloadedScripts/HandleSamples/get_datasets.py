#!/usr/bin/env python

import os

#import pyAMI.client
#import pyAMI.atlas.api as AtlasAPI
#client = pyAMI.client.Client('atlas')
#AtlasAPI.init()
#AtlasAPI.list_datasets(client, patterns = ['mc12_8TeV.%'], type = 'AOD')

class Dataset:
    def __init__(self, ds_id, ds_name="", ds_gen="", ds_cs=-1, ds_nevents=0):
        self.id = ds_id
        self.name = ds_name
        self.cs = ds_cs
        self.nevents = ds_nevents
        self.gen = ds_gen

# Make lists of datasets used
signal_sets = []
background_sets = []

lines = []
with open('Datasets.tex') as f:
    lines = f.readlines()

for line in lines:
    # Find the dataset lines
    if len(line.split("&"))<3: continue
    dsid = line.split("&")[0]
    if not dsid.strip().isdigit(): continue

    id = int(dsid.strip())
    name = line.split("&")[1].strip().replace("\_", "_")
    gen = line.split("&")[2].split("{\sc")[1].split("}")[0].strip()

    ds = Dataset(id, name, gen, -1, 13000)

    # Fill the background lists
    if len(line.split("&")) == 4:
        print id, name, gen
        background_sets+=[ds]

    # Fill the signal lists
    if len(line.split("&")) == 3:
        print id, name, gen
        signal_sets+=[ds]

# Want datasets not excluded:
# No _30: >=900 unless mu <= 200
# _30: >=900 unless mu <= 400

for ds in signal_sets:

    new_job = open("RunScripts/job_makeEVNT_"+str(ds.id)+".sh", "w")
    config_dir = "/cvmfs/atlas.cern.ch/repo/sw/Generators/MC12JobOptions/latest/share/DSID"+str(ds.id)[:3]+"xxx/"
    config_file = ""
    for file in os.listdir(config_dir):
        if file.startswith("MC12."+str(ds.id)):
            config_file=file
    if config_file == "":
        print "COULDN'T FIND CONFIG FILE FOR DATASET", ds.id
        continue

    rundir_loc = "/afs/cern.ch/user/t/tholmes/ZMET/SusyZMETjetsWorkArea/Scripts/HandleSamples/RunDir/"
    rundir_loc += "EVNT_"+str(ds.id)
    if not os.path.exists(rundir_loc):
        os.makedirs(rundir_loc)

    with open('job_template_EVNT.sh') as f:
        for line in f.readlines():
            newline = line.replace("__DS__", str(ds.id))
            newline = newline.replace("__DS0:3__", str(ds.id)[:3])
            newline = newline.replace("__CONFIGNAME__", config_dir+config_file)
            newline = newline.replace("__RUNPATH__", rundir_loc)
            newline = newline.replace("__OUTPUT__", "/afs/cern.ch/work/t/tholmes/ZMETSamples/Signal/EVNT/EVNT."+str(ds.id)+"."+ds.name+".root")
            new_job.write(newline)
    new_job.close()
    os.chmod("RunScripts/job_makeEVNT_"+str(ds.id)+".sh", 0755)

sub_script = open("submit_EVNT.sh", "w")
for ds in signal_sets:
    has_30 = False
    if ds.name.endswith("_30_Zll"):
        has_30 = True
    m_glu = int(ds.name.split("_")[1])
    mu = int(ds.name.split("_")[2])
    print ds.name
    if has_30 and m_glu<900 and mu>400: continue
    if not has_30 and m_glu<900 and mu>200: continue
    print " Passed."
    sub_script.write("bsub -q 1nd -o Logs/out_makeEVNT_"+str(ds.id)+".txt /afs/cern.ch/user/t/tholmes/ZMET/SusyZMETjetsWorkArea/Scripts/HandleSamples/RunScripts/job_makeEVNT_"+str(ds.id)+".sh \n")
sub_script.close()


