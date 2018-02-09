#!/usr/bin/env python
import ROOT
import os
import pyAMI.client
import pyAMI.atlas.api as AtlasAPI

# Check if it's likely that we have a buggy number of AOD events
# To start, just checking AMI for the full original number, then seeing if it's higher.

# Set up pyAMI
client = pyAMI.client.Client('atlas')
AtlasAPI.init()

# Dir for MC files
mc_dir = "/afs/cern.ch/work/t/tholmes/ZMETSamples/eos/atlas/user/l/longjon/Ntuples/v00-13/"
#mc_dir = "/afs/cern.ch/work/t/tholmes/ZMETSamples/eos/atlas/user/t/tholmes/Ntuples/v00-11/"
# expect to have the form user.zmarshal.361443.e4133_s2608_s2183_r6869_r6282_p2419.zmetjets-v00-11_Sep2815_ntupleOutput.root
# with files in that dir

bad_dids = []

for d in os.listdir(mc_dir):
    if not d.endswith(".root"): continue
    if not "_p2411" in d: continue
    #if not "zmarshal.361" in d: continue
    print d

    # Get total number of events
    n_aod_events = 0
    for f in os.listdir(mc_dir+d):
        tf = ROOT.TFile(mc_dir+d+'/'+f, 'READ')
        n_aod_events += tf.Get('EventCountHist').GetBinContent(1)

    # Compare to AMI value
    did = d.split(".")[2]
    tags = d.split(".")[3].split("_p")[0]

    # Don't check data
    if did.startswith("00"): continue

    # Get all possible AODs for the output ntuple
    base_files = AtlasAPI.list_datasets(client, patterns = ['mc15_13TeV.'+did+'%merge.AOD%'+tags+'%'], type = 'AOD')
    print "-------------------------------------------------------------------------"
    print "Ntuple name:", d
    print base_files[0]['ldn']

    if len(base_files) > 1:
        print "Found more than one matching AOD."
        print "For file", f
        print "using", base_files[0]['ldn']

    info = AtlasAPI.get_dataset_info(client, base_files[0]['ldn'])[0]
    n_real_events = info.get('totalEvents')
    if float(n_real_events) < float(n_aod_events):
        print "\033[91m Error in dsid", did
        bad_dids += [did]
    print "\t Real number of AOD events:", n_real_events
    print "\t EventCountHist number:    ", n_aod_events
    print "\t Ratio:                    ", float(n_aod_events)/float(n_real_events)
    print '\033[0m'

print "All dids with bad weights:"
print bad_dids

