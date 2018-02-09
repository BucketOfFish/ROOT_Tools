#!/usr/bin/env python
import csv
import ROOT
import os
from math import *
from array import array
execfile("plotHelper.py")
execfile("defineChannels.py")

#To use pyami
import pyAMI.client
import pyAMI.atlas.api as AtlasAPI
client = pyAMI.client.Client('atlas')
AtlasAPI.init()

ROOT.gStyle.SetLegendBorderSize(0)
#ROOT.gROOT.SetBatch()
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptTitle(0)
ROOT.TH1.SetDefaultSumw2()

# Idea:
# For various regions, check the impact of theory variations on the final output

cross_sections = {}

nominals = [
        "user.tholmes.mc15_13TeV.361063.Sherpa_CT10_llll.merge.DAOD_TRUTH1.e3836_p2436_ntupleOutput.root",
        "user.tholmes.mc15_13TeV.361064.Sherpa_CT10_lllvSFMinus.merge.DAOD_TRUTH1.e3836_p2436_ntupleOutput.root",
        "user.tholmes.mc15_13TeV.361065.Sherpa_CT10_lllvOFMinus.merge.DAOD_TRUTH1.e3836_p2436_ntupleOutput.root",
        "user.tholmes.mc15_13TeV.361066.Sherpa_CT10_lllvSFPlus.merge.DAOD_TRUTH1.e3836_p2436_ntupleOutput.root",
        "user.tholmes.mc15_13TeV.361067.Sherpa_CT10_lllvOFPlus.merge.DAOD_TRUTH1.e3836_p2436_ntupleOutput.root",
        "user.tholmes.mc15_13TeV.361068.Sherpa_CT10_llvv.merge.DAOD_TRUTH1.e3836_p2436_ntupleOutput.root",
        "user.tholmes.mc15_13TeV.361073.Sherpa_CT10_ggllll.merge.DAOD_TRUTH1.e3836_p2436_ntupleOutput.root",
        "user.tholmes.mc15_13TeV.361077.Sherpa_CT10_ggllvv.merge.DAOD_TRUTH1.e3836_p2436_ntupleOutput.root",
        "user.tholmes.mc15_13TeV.361084.Sherpa_CT10_WqqZll.merge.DAOD_TRUTH1.e3836_p2436_ntupleOutput.root",
        "user.tholmes.mc15_13TeV.361086.Sherpa_CT10_ZqqZll.merge.DAOD_TRUTH1.e3926_p2436_ntupleOutput.root",
        ]

categories = {
        "VV": ["user.tholmes.mc15_13TeV.361068.Sherpa_CT10_llvv.merge.DAOD_TRUTH1.e3836_p2436_ntupleOutput.root",
                    "user.tholmes.mc15_13TeV.361077.Sherpa_CT10_ggllvv.merge.DAOD_TRUTH1.e3836_p2436_ntupleOutput.root"],
        "WZ": ["user.tholmes.mc15_13TeV.361064.Sherpa_CT10_lllvSFMinus.merge.DAOD_TRUTH1.e3836_p2436_ntupleOutput.root",
                    "user.tholmes.mc15_13TeV.361065.Sherpa_CT10_lllvOFMinus.merge.DAOD_TRUTH1.e3836_p2436_ntupleOutput.root",
                    "user.tholmes.mc15_13TeV.361066.Sherpa_CT10_lllvSFPlus.merge.DAOD_TRUTH1.e3836_p2436_ntupleOutput.root",
                    "user.tholmes.mc15_13TeV.361067.Sherpa_CT10_lllvOFPlus.merge.DAOD_TRUTH1.e3836_p2436_ntupleOutput.root"],
        "ZZ": ["user.tholmes.mc15_13TeV.361063.Sherpa_CT10_llll.merge.DAOD_TRUTH1.e3836_p2436_ntupleOutput.root",
                    "user.tholmes.mc15_13TeV.361073.Sherpa_CT10_ggllll.merge.DAOD_TRUTH1.e3836_p2436_ntupleOutput.root"]
        }

# file_loc = "/afs/cern.ch/work/t/tholmes/ZMETSamples/variations/"
file_loc = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/v1_02/TheoryVariations/"

n_events = {

        361063: 2999000,
        361064: 450000,
        361065: 900000,
        361066: 600000,
        361067: 1200000,
        361068: 5942000,
        361073: 502000,
        361077: 200000,
        361084: 250000,
        361086: 100000,
        363089: 200000 ,
        363088: 200000 ,
        363087: 200000 ,
        363086: 200000 ,
        363085: 200000 ,
        363083: 250000 ,
        363082: 250000 ,
        363081: 250000 ,
        363080: 250000 ,
        363079: 250000 ,
        363078: 250000 ,
        363077: 6000000,
        363076: 6000000,
        363075: 6000000,
        363074: 6000000,
        363073: 5999000,
        363072: 6000000,
        363071: 1200000,
        363070: 1200000,
        363069: 1200000,
        363068: 1200000,
        363067: 1200000,
        363066: 1200000,
        363065: 600000 ,
        363064: 600000 ,
        363063: 600000 ,
        363062: 600000 ,
        363061: 600000 ,
        363060: 600000 ,
        363058: 900000 ,
        363057: 900000 ,
        363056: 900000 ,
        363055: 900000 ,
        363054: 900000 ,
        363053: 450000 ,
        363052: 450000 ,
        363051: 450000 ,
        363050: 450000 ,
        363049: 450000 ,
        363048: 450000 ,
        363047: 2498000,
        363046: 2498800,
        363045: 2500000,
        363044: 2499800,
        363043: 2500000,
        363042: 2499800,
        }

regions = {
        "SRZ": "lep_pT[0]>50 && lep_pT[1]>25 && jet_n>1 && is_OS && DPhi_METJetLeading>0.4 && DPhi_METJetSecond>0.4 && MET_NonInt>225 && HTincl>600 && mll>81 && mll<101 && channel < 2",
        "VRS": "lep_pT[0]>50 && lep_pT[1]>25 && jet_n>1 && is_OS && DPhi_METJetLeading>0.4 && DPhi_METJetSecond>0.4 && MET_NonInt>100 && MET_NonInt<200 && HTincl>600 && mll>81 && mll<101 && channel < 2",
        "CRT": "lep_pT[0]>50 && lep_pT[1]>25 && jet_n>1 && is_OS && DPhi_METJetLeading>0.4 && DPhi_METJetSecond>0.4 && MET_NonInt>225 && HTincl>600 && ((mll>45 && mll<81) || mll>101) && channel < 2",
        "VRT": "lep_pT[0]>50 && lep_pT[1]>25 && jet_n>1 && is_OS && DPhi_METJetLeading>0.4 && DPhi_METJetSecond>0.4 && MET_NonInt>100 && MET_NonInt<200 && HTincl>600 && ((mll>45 && mll<81) || mll>101) && channel < 2",
        "SR-Low": "lep_pT[0]>25 && lep_pT[1]>25 && channel<2 && is_OS && mll>12 && jet_n>1 && DPhi_METJetLeading>0.4 && DPhi_METJetSecond>0.4 && MET_NonInt>200",
        "SR-Med": "lep_pT[0]>25 && lep_pT[1]>25 && channel<2 && is_OS && mll>12 && jet_n>1 && DPhi_METJetLeading>0.4 && DPhi_METJetSecond>0.4 && MET_NonInt>250 && HT>400",
        "SR-High": "lep_pT[0]>25 && lep_pT[1]>25 && channel<2 && is_OS && mll>12 && jet_n>1 && DPhi_METJetLeading>0.4 && DPhi_METJetSecond>0.4 && MET_NonInt>200 && HT>700",
        "VR-Low": "lep_pT[0]>25 && lep_pT[1]>25 && channel<2 && is_OS && mll>12 && jet_n>1 && DPhi_METJetLeading>0.4 && DPhi_METJetSecond>0.4 && MET_NonInt>100 && MET_NonInt<200",
        "VR-Med": "lep_pT[0]>25 && lep_pT[1]>25 && channel<2 && is_OS && mll>12 && jet_n>1 && DPhi_METJetLeading>0.4 && DPhi_METJetSecond>0.4 && MET_NonInt>100 && MET_NonInt<200 && HT>400",
        "VR-High": "lep_pT[0]>25 && lep_pT[1]>25 && channel<2 && is_OS && mll>12 && jet_n>1 && DPhi_METJetLeading>0.4 && DPhi_METJetSecond>0.4 && MET_NonInt>100 && MET_NonInt<200 && HT>700",
        "VRWZ": "VRWZ",
        "VRZZ": "VRZZ",
        "VR3L": "VR3L",
        }

regions["SRZ+VRS"] = "(%s) || (%s)" % (regions["SRZ"], regions["VRS"])
regions["CRT+VRT"] = "(%s) || (%s)" % (regions["CRT"], regions["VRT"])
regions["SR+VR-Low"] = "(%s) || (%s)" % (regions["SR-Low"], regions["VR-Low"])
regions["SR+VR-Med"] = "(%s) || (%s)" % (regions["SR-Med"], regions["VR-Med"])
regions["SR+VR-High"] = "(%s) || (%s)" % (regions["SR-High"], regions["VR-High"])

lumi = 3209.05

# Returns in pb
def getXS(dsid):
    xs = getCrossSection(int(dsid), verbose=False)
    if xs == -1:
        #print "using pyami for dsid", dsid
        fname = ""
        files = os.listdir(file_loc)
        for f in files:
            if dsid in f: fname = f.strip("_ntupleOutput\.root\/").strip("user\.tholmes\.")
        fname = "m" + fname
        info = AtlasAPI.get_dataset_info(client, fname)[0]
        #if (info.get('crossSection_unit') != 'nano barn'): print 'WARNING: Cross section listed in', info.get('crossSection_unit'),"!!"
        xs = 1000*float(info.get('approx_crossSection'))*float(info.get('approx_GenFiltEff'))

    return xs

def getEventsInReg(file_loc, fname, reg, xs):

    dsid = int(fname.split(".")[3])
    t = ROOT.TChain('ntupleOutput')
    t.Add(file_loc+fname+"/*.root")
    n_unweighted = t.Draw("channel", regions[reg])
    n_passed = n_unweighted*lumi*xs#getXS(str(dsid))/n_events[dsid]

    return (n_passed, n_unweighted)

def replaceMissingSamples(weighted_events, var, reg, upordown, nom):
    # If it exists just return it
    if var in weighted_events.keys():
        if reg in weighted_events[var].keys():
            if upordown in weighted_events[var][reg].keys():
                if nom in weighted_events[var][reg][upordown].keys():
                    return weighted_events[var][reg][upordown][nom]
    # Otherwise, get average for that value
    new_val = 0
    for nom in weighted_events[var][reg][upordown].keys():
        new_val += weighted_events[var][reg][upordown][nom]
    new_val /= len(weighted_events[var][reg][upordown].keys())
    return new_val

for cat in nominals:
    cross_sections[int(cat.split(".")[3])] = getXS(cat.split(".")[3])

# for each general category
# need each variation for the summed samples in category
# if variation doesn't exist, take average value for category

variations = ["qsf", "renorm", "fac"]
regions_to_use = ["SRZ","VRS","CRT","VRT","SR-Low","SR-Med","SR-High","VR-Low","VR-Med","VR-High","VRWZ","VRZZ","VR3L"]
# regions_to_use = ["VRWZ","VRZZ","VR3L"]
# regions_to_use = ["SR+VR-Low", "SR+VR-Med", "SR+VR-High"]

for cat in categories.keys():
    print "======================================================================================="
    print "======================================================================================="
    print cat

    # Create dictionaries to store important info
    # Dictionary should have yield in region / nominal yield
    weighted_events = {}
    nominal_values = {}

    for nom in categories[cat]:
        print nom
        nominal_values[nom] = {}
        for reg in regions_to_use:

            identifier = nom.split(".")[4]
            nom_dsid = int(nom.split(".")[3])
            (nominal_value, nominal_unweighted) = getEventsInReg(file_loc, nom, reg, cross_sections[nom_dsid]/n_events[nom_dsid])
            nominal_values[nom][reg] = nominal_value

            for var in variations:
                if var not in weighted_events.keys(): weighted_events[var] = {}
                if reg not in weighted_events[var].keys(): weighted_events[var][reg] = {}
                for upordown in ["4", "025"]:
                    if upordown not in weighted_events[var][reg].keys(): weighted_events[var][reg][upordown] = {}
                    fname = ""
                    for f in os.listdir(file_loc):
                        if (var+upordown in f) and (identifier in f):
                            var_dsid = int(f.split(".")[3])
                            (var_value, var_unweighted) = getEventsInReg(file_loc, f, reg, cross_sections[nom_dsid]/n_events[var_dsid])
                            print "\t", var+upordown, "\t", reg, "\t",  var_unweighted
                            if nominal_value>0:
                                weighted_events[var][reg][upordown][nom] = var_value / nominal_value
                            else:
                                weighted_events[var][reg][upordown][nom] = 0

    print_str = "%10s" % ""
    for reg in regions_to_use: print_str += "\t%10s" % reg
    print print_str

    total_uncertainty = {}
    for reg in regions_to_use: total_uncertainty[reg] = 0
    for var in variations:
        print_str = "%10s" % var
        for reg in regions_to_use:
            var_up = 0
            var_down = 0
            nom_yield = 0
            for nom in weighted_events[var][reg]["4"].keys():
                var_up += weighted_events[var][reg]["4"][nom] * nominal_values[nom][reg]
                nom_yield += nominal_values[nom][reg]
            if nom_yield>0:
                var_up /= nom_yield
            else:
                var_up = 0
            nom_yield = 0
            for nom in weighted_events[var][reg]["025"].keys():
                var_down += weighted_events[var][reg]["025"][nom] * nominal_values[nom][reg]
                nom_yield += nominal_values[nom][reg]
            if nom_yield>0:
                var_down /= nom_yield
            else:
                var_down = 0

            print_str += "\t%.2f     " % (.5*(var_up-var_down))
            total_uncertainty[reg] = sqrt(total_uncertainty[reg]**2 + (.5*(var_up-var_down))**2)
        print print_str
    print_str = "%10s" % "total"
    for reg in regions_to_use:
        print_str += "\t%.2f     " % total_uncertainty[reg]
    print print_str
