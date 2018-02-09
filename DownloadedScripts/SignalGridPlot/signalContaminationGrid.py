import os, sys
lib_path = os.path.abspath('inputType')
sys.path.append(lib_path)

import ROOT
from ROOT import *
from array import array

def makePlots(hist,name):
    fa1 = ROOT.TF1("fa1","x",0,1200)
    fb1 = ROOT.TF1("fb1","x-100",0,1200)
    fa2 = ROOT.TF1("fa2","x",700,1100)
    fb2 = ROOT.TF1("fb2","x-100",700,1100)
    hist2 = hist.Clone()
    canvas = ROOT.TCanvas("canvas","testCanvas",600,600)
    mypad = ROOT.TPad("mypad","mypad",0.0,0.0,1.0,1.0)
    mypad.SetLeftMargin(0.15)
    mypad.Draw()
    mypad.cd()
    hist.Draw('TEXT45')
    fa1.Draw('same')
    fb1.Draw('same')
    canvas.Print("Plots/%s.eps"%(name))
    hist2.SetAxisRange(600, 1000,"Y");
    hist2.SetAxisRange(700, 1100,"X");
    hist2.Draw('TEXT45')
    fa2.Draw('same')
    fb2.Draw('same')
    canvas.Print("Plots/%s_zoomin.eps"%(name))

# hist_SL_xAOD = ROOT.TH2F("hist_SL_xAOD","",200,0,2000,120,0,1200)
# hist_SL_xAOD.SetStats(0)
# hist_SL_xAOD.SetTitle("")
# hist_SL_xAOD.GetXaxis().SetTitle("gluino mass")
# hist_SL_xAOD.GetYaxis().SetTitle("LSP mass")
# hist_SL_xAOD.GetYaxis().SetTitleOffset(1.8)
# hist_Z_xAOD = ROOT.TH2F("hist_Z_xAOD","",200,0,2000,120,0,1200)
# hist_Z_xAOD.SetStats(0)
# hist_Z_xAOD.SetTitle("")
# hist_Z_xAOD.GetXaxis().SetTitle("gluino mass")
# hist_Z_xAOD.GetYaxis().SetTitle("LSP mass")
# hist_Z_xAOD.GetYaxis().SetTitleOffset(1.8)

for inputFileName in os.listdir("GridPoints"):
    inputFile = open("GridPoints/"+inputFileName, 'r')
    hist_grid = ROOT.TH2F("hist_grid","",200,0,2000,120,0,1200)
    hist_grid.SetStats(0)
    hist_grid.GetXaxis().SetTitle("gluino mass")
    hist_grid.GetYaxis().SetTitle("LSP mass")
    hist_grid.GetYaxis().SetTitleOffset(1.8)
    hist_grid.SetTitle(inputFileName.strip(".txt"))
    if "SLN_" in inputFileName:
        gridType = "SLN"
    else:
        gridType = "Z"
    for line in inputFile:
        line = line.strip("\n")
        m1 = int(line.split('\t')[0]) #gluino
        m2 = int(line.split('\t')[1]) #chi10
        contamPercent = float(line.split('\t')[2])*100
        print(gridType, m1, m2, contamPercent)
        hist_grid.Fill(m1,m2,contamPercent)
    makePlots(hist_grid,inputFileName.strip(".txt"))
            # hist_SL_QA20.Fill(mass_gluino,mass_chi10,tree.GetEntries())
            # sr1_nevents = SR1_nevents(tree)
            # hist_SL_SR1.Fill(mass_gluino,mass_chi10,sr1_nevents)
            # sr2_nevents = SR2_nevents(tree)
            # hist_SL_SR2.Fill(mass_gluino,mass_chi10,sr2_nevents)
            # mll_nevents = []
            # mll_nevents = Mll_nevents(tree,(mass_gluino+mass_chi10)/2.-mass_chi10)
            # hist_SL_mll.Fill(mass_gluino,mass_chi10,(mass_gluino+mass_chi10)/2.-mass_chi10)
            # if mass_gluino==1400 and mass_chi10==300: hist_SL_mll_highlight.Fill(mass_gluino,mass_chi10,(mass_gluino+mass_chi10)/2.-mass_chi10)
            # if mass_gluino==800 and mass_chi10==740: hist_SL_mll_highlight.Fill(mass_gluino,mass_chi10,(mass_gluino+mass_chi10)/2.-mass_chi10)
        # if 'ZN1' in line:
            # tree = ROOT.TChain("outputTree", "TChain for the Tree in the root file")
            # line = line.split(':')[0]
            # masses = line.split('ZN1_')[1].split('_ntupleOutput')[0]
            # mass_gluino = int(masses.split('_')[0])
            # mass_chi10 = int(masses.split('_')[1])
            # print line
            # nextline = inputFile.next().strip('\n')
            # nextline.strip()
            # print nextline
            # fSIG = ROOT.TFile('%s/%s'%(line,nextline))
            # EventCountHist = fSIG.Get("EventCountHist")
            # total_signal = EventCountHist.GetBinContent(1)
            # tree.Add('%s/*.root'%(line))
            # print 'gluino %i chi10 %i total %i entries %i'%(mass_gluino,mass_chi10,total_signal,tree.GetEntries())
            # hist_Z_xAOD.Fill(mass_gluino,mass_chi10,total_signal)
            # hist_Z_QA20.Fill(mass_gluino,mass_chi10,tree.GetEntries())
            # sr1_nevents = SR1_nevents(tree)
            # hist_Z_SR1.Fill(mass_gluino,mass_chi10,sr1_nevents)
            # sr2_nevents = SR2_nevents(tree)
            # hist_Z_SR2.Fill(mass_gluino,mass_chi10,sr2_nevents)
            # mll_nevents = []
            # mll_nevents = Mll_nevents(tree,(mass_gluino+mass_chi10)/2.-mass_chi10)
            # hist_Z_mll.Fill(mass_gluino,mass_chi10,(mass_gluino+mass_chi10)/2.-mass_chi10)
            # if mass_gluino==1400 and mass_chi10==300: hist_Z_mll_highlight.Fill(mass_gluino,mass_chi10,(mass_gluino+mass_chi10)/2.-mass_chi10)
            # if mass_gluino==800 and mass_chi10==740: hist_Z_mll_highlight.Fill(mass_gluino,mass_chi10,(mass_gluino+mass_chi10)/2.-mass_chi10)
		
# makePlots(hist_SL_xAOD,'SL_from_xAOD')
# makePlots(hist_SL_QA20,'SL_from_QA20')
# makePlots(hist_SL_SR1,'SL_from_SR1')
# makePlots(hist_SL_SR2,'SL_from_SR2')
# makePlots(hist_SL_mll,'SL_from_mll')
# makePlots(hist_SL_mll_highlight,'SL_from_mll_highlight')
# makePlots(hist_Z_xAOD,'Z_from_xAOD')
# makePlots(hist_Z_QA20,'Z_from_QA20')
# makePlots(hist_Z_SR1,'Z_from_SR1')
# makePlots(hist_Z_SR2,'Z_from_SR2')
# makePlots(hist_Z_mll,'Z_from_mll')
# makePlots(hist_Z_mll_highlight,'Z_from_mll_highlight')
