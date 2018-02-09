#!/usr/bin/env python
import ROOT

# Define signal region, then remove all events in it from the file

# Define events to remove
ee_trig_str = "( e.channel==1 and ( (e.lep_pT[0]>65 and e.HLT_e60_lhmedium) or (e.lep_pT[0]<65 and e.HLT_2e17_lhloose) ) )"
mm_trig_str = "( e.channel==0 and ( (e.lep_pT[0]>55 and e.HLT_mu50) or ( (e.lep_pT[0]<55 and e.HLT_mu24_mu8noL1) ) ) )"

sr_string = "(e.lep_pT[1]>25 and e.is_OS and e.jet_n>1 and e.MET>225 and e.HTincl>600 and e.mll>81 and e.mll<10 and e.DPhi_METJetLeading>0.4 and e.DPhi_METJetSecond>0.4)"
sr_string += " and (%s or %s) " % (ee_trig_str,mm_trig_str)

#sr_string = "e.HT>100"

# Set up input/output files
input_file = "/afs/cern.ch/work/t/tholmes/ZMETSamples/eos/atlas/user/t/tholmes/Ntuples/v00-15-nosyst/Data/data.root"
output_file = "/afs/cern.ch/work/t/tholmes/ZMETSamples/eos/atlas/user/t/tholmes/Ntuples/v00-15-nosyst/Data/data_blinded.root"
#input_file = "/afs/cern.ch/work/t/tholmes/ZMETSamples/Current_Ntuples/v00-15/Data/data.root"
#output_file = "/afs/cern.ch/work/t/tholmes/ZMETSamples/Current_Ntuples/v00-15/Data/data_blinded.root"
print "Opening file", input_file
old_file = ROOT.TFile(input_file, 'READ')
t_in = old_file.Get('outputTree')

new_file = ROOT.TFile(output_file, 'RECREATE')
t_out = t_in.CloneTree(0)

# Loop over entries
max_events = t_in.GetEntries()

i_event = 0
n_passed = 0
for e in t_in:

    if i_event % 10000 == 0:
        print 'Processing event %i of %i' % (i_event, max_events)

    is_sr = eval(sr_string)

    if not is_sr:
        t_out.Fill()
        n_passed += 1

    i_event += 1

# Close files
new_file.Write()
old_file.Close()
new_file.Close()

# Don't print this with the real SR!!!
#print "Passed", n_passed, "/", max_events, "events."
