
cd /afs/cern.ch/user/t/tholmes/ZMET/SusyZMETjetsWorkArea/Scripts/HandleSamples 
source setup.sh

export JOBOPTSEARCHPATH=/cvmfs/atlas.cern.ch/repo/sw/Generators/MC12JobOptions/latest/share/DSID__DS0:3__xxx:$JOBOPTSEARCHPATH
export DATAPATH=/cvmfs/atlas.cern.ch/repo/sw/Generators/MC12JobOptions/latest/share/DSID__DS0:3__xxx:$DATAPATH

cd __RUNPATH__

Generate_trf.py firstEvent=1 randomSeed=1234 runNumber=__DS__ ecmEnergy=13000 maxEvents=-1 jobConfig=__CONFIGNAME__ outputEVNTFile=__OUTPUT__
