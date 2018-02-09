export AtlasSetup=/afs/cern.ch/atlas/software/dist/AtlasSetup
alias asetup='source $AtlasSetup/scripts/asetup.sh'
asetup 17.2.13.10,slc5,gcc43
export DATAPATH=/cvmfs/atlas.cern.ch/repo/sw/Generators/MC12JobOptions/latest/common:$DATAPATH
export DATAPATH=/cvmfs/atlas.cern.ch/repo/sw/Generators/MC12JobOptions/latest/susycontrol:$DATAPATH
export JOBOPTSEARCHPATH=/cvmfs/atlas.cern.ch/repo/sw/Generators/MC12JobOptions/latest/common:$JOBOPTSEARCHPATH
export JOBOPTSEARCHPATH=/cvmfs/atlas.cern.ch/repo/sw/Generators/MC12JobOptions/latest/susycontrol:$JOBOPTSEARCHPATH
export SUSYCONTROL=/cvmfs/atlas.cern.ch/repo/sw/Generators/MC12JobOptions/latest/susycontrol
export DATAPATH=/cvmfs/atlas.cern.ch/repo/sw/Generators/MC12JobOptions/latest/share:$DATAPATH
export JOBOPTSEARCHPATH=/cvmfs/atlas.cern.ch/repo/sw/Generators/MC12JobOptions/latest/share:$JOBOPTSEARCHPATH
export JOBOPTSEARCHPATH=/cvmfs/atlas.cern.ch/repo/sw/Generators/MC12JobOptions/latest/share/DSID157xxx:$JOBOPTSEARCHPATH
export DATAPATH=/cvmfs/atlas.cern.ch/repo/sw/Generators/MC12JobOptions/latest/share/DSID157xxx:$DATAPATH
