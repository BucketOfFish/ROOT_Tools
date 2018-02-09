# vim: tabstop=4 noexpandtab shiftwidth=4
import logging
import shutil
import os
import errno
import sys
import re
import signal

logging.basicConfig(level=logging.INFO)

oldargv = sys.argv
sys.argv = [oldargv[0], "-b"]
logging.info("importing ROOT")
import ROOT
ROOT.gROOT
logging.info("OK")

import atexit
@atexit.register
def quite_exit():
    ROOT.gSystem.Exit(0)

# lets you interrupt the job by ctrl+C immediately
signal.signal(signal.SIGINT, signal.SIG_DFL)

logging.info("loading packages")
ROOT.gROOT.Macro("$ROOTCOREDIR/scripts/load_packages.C")
sys.argv = oldargv


logging.info("creating new sample handler")
sh_all = ROOT.SH.SampleHandler()

####################################
# change path to input sample here:
####################################
search_directories = []

basedir = "pileup_truth/"

#input_path = os.path.dirname(os.environ["ASG_TEST_FILE_MC"])
input_path = "/afs/cern.ch/work/b/bgui/AOD_Files/mc15_13TeV.361107.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zmumu.merge.AOD.e4397_s2608_r7042_r6282_tid07037303_00"
#input_path = "/afs/cern.ch/work/b/bgui/AOD_Files/mc15_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2608_s2183_r7042_r6282_tid06758885_00"

if input_path:
    if os.path.isdir(input_path):
        input_dir = input_path
        pattern = "*.root"
        pattern = "*.root.1"
        #  if "*" in input_dir or "?" in input_dir:
            #  print "Error, wildcards not supported in --input directory (only in filename)"
            #  sys.exit(1)
    else:
        input_dir, pattern = os.path.split(input_path)

    logging.info("input dir: %s", input_dir)
    logging.info("pattern: %s", pattern)
    search_directories.append(input_dir)




#search_directories = ("/ngse5/atlas/user/fmeloni/InDet_xAOD/",)
#search_directories = ("/ngse5/atlas/user/fmeloni/mc15_PU_xAOD/",)
#search_directories = ("/tmp/jmansour/data15_13TeV.00266904.express_express.merge.AOD.x339_m1435/",)
#search_directories = ("/tmp/jmansour/data15_13TeV.00266919.physics_MinBias.merge.AOD.f594_m1435/",)
#search_directories = ("/tmp/jmansour/data15_13TeV.00267223.physics_MinBias.merge.AOD.x340_m1435/",)
#search_directories = ("/tmp/jmansour/mc15_13TeV.159000.ParticleGenerator_nu_E50.recon.AOD.e3711_s2576_s2132_r6220_tid05293002_00/",)
# scan for datasets in the given directories
short_name = "default_set"
for directory in search_directories:
    ROOT.SH.ScanDir().filePattern(pattern).scan(sh_all, directory)

# set the name of the tree in our files
sh_all.setMetaString("nc_tree", "CollectionTree")

sh_all.Print()
for sample in sh_all:
    logging.info("%s: %d files" % (sample.name(), sample.numFiles()))
    for fn in sample.makeFileList():
        logging.info("  "+fn)

# print out the samples we found
logging.info("%d different datasets found scanning all directories", len(sh_all))

# this is the basic description of our job
logging.info("creating new job")
job = ROOT.EL.Job()
job.sampleHandler(sh_all)
  
# if options.nevents:
#     logging.info("processing only %d events", options.nevents)
#     job.options().setDouble(ROOT.EL.Job.optMaxEvents, options.nevents)
#job.options().setDouble(ROOT.EL.Job.optMaxEvents, 10)
#job.options().setDouble(ROOT.EL.Job.optMaxEvents, 1000)

# if options.skip_events:
#     logging.info("skipping first %d events", options.skip_events)
#     job.options().setDouble(ROOT.EL.Job.optSkipEvents, options.skip_events)

# Set up the job for xAOD access:
ROOT.xAOD.Init().ignore()


# add ntuple
alg = ROOT.TrkVtxAssoc()
output = "myOutput"
myOutput = ROOT.EL.OutputStream(output)
job.outputAdd(myOutput)
ntupleSvc = ROOT.EL.NTupleSvc(output)
job.algsAdd(ntupleSvc)
alg.outputName = output


# add our algorithm to the job
logging.info("adding algorithms")


method = "loose_method_cut"
# method = "tight_method_cut"

if method == "loose_method_cut":
    outdir = "loose_method_cut"
    alg = ROOT.TrkVtxAssoc()
    alg.description = "Loose association method"
    alg.directoryName = "looseassoc"
    alg.associationMethod = "Loose"
    alg.matchMethod = "smart"
    alg.doTrackCut = True
    alg.trackCutLevel = "TightPrimary"
    alg.trackMinPt = 400.
    alg.trackAbsPdgId = 211
    job.algsAdd(alg)

elif method == "tight_method_cut":
    outdir = "tight_method_cut"
    alg = ROOT.TrkVtxAssoc()
    alg.description = "Tight association method"
    alg.directoryName = "tightassoc"
    alg.associationMethod = "Tight"
    alg.matchMethod = "smart"
    alg.doTrackCut = True
    alg.trackCutLevel = "TightPrimary"
    alg.trackMinPt = 400.
    alg.trackAbsPdgId = 211
    job.algsAdd(alg)

else:
    log.error("Unknown method %s", method)
    sys.exit(1)

# # this doesnt work, we could do something like that in Athena:
# alg.m_trackSel = ROOT.InDet.InDetTrackSelectionTool("LooseTrackSelection");
# alg.m_trackSel.setProperty("CutLevel", "Loose")
# alg.m_trackSel.setProperty("minPt", 400.)
# alg.m_trackSel.initialize()
# print dir(alg.m_trackSel)

# make the driver we want to use
# this one works by running the algorithm directly
logging.info("creating driver")

logging.info("running on direct")
driver = ROOT.EL.DirectDriver()
logging.info("submit job")

realOutDir = basedir + outdir

if os.path.exists(realOutDir):
    logging.error("output path %s already exists", realOutDir)
    sys.exit(1)

logging.info("will create output directory %s", realOutDir)
#  while True:
#      logging.info("is this OK? [y/n]")
#      inp = raw_input().lower()
#      if inp == "y":
#          break
#      elif inp == "n":
#          logging.info("cancelling")
#          sys.exit(0)

try:
    os.makedirs(os.path.dirname(realOutDir))
except OSError:
    pass

driver.submit(job, realOutDir)
logging.info("the output dir is %s", realOutDir)
