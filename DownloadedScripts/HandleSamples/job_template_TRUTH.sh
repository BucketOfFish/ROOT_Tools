source /afs/cern.ch/user/t/tholmes/.bash_profile
cd __OUTDIR__
asetup 19.1.X.Y-VAL,rel_3,AtlasDerivation,here --nightliesarea=/afs/cern.ch/atlas/software/builds/nightlies
Reco_tf.py --inputEVNTFile __INPUT__ --outputDAODFile __OUTPUT__ --reductionConf MCGN1

