#!/usr/bin/env python
import ROOT
import os

#Load ATLAS style
ROOT.gROOT.Macro("/afs/cern.ch/user/t/tholmes/atlasstyle-00-03-05/rootlogon.C");

# Functions for simplifying the plotting process

# Some colors I like
colors = [ROOT.kAzure+1, ROOT.kMagenta+1, ROOT.kTeal+1, ROOT.kBlue+1]
fill_colors = [ROOT.kAzure-9, ROOT.kMagenta-9, ROOT.kTeal-9, ROOT.kBlue-9, ROOT.kViolet-9, ROOT.kOrange-9, ROOT.kSpring-9]
more_colors = [ROOT.kAzure+2, ROOT.kGreen+2, ROOT.kPink+4, ROOT.kOrange+10, ROOT.kOrange, ROOT.kSpring+7]
#TColor::GetColor("#5dbe5d")
hopper_colors = [ROOT.TColor.GetColor('#e23f59'), ROOT.TColor.GetColor('#eab508'), ROOT.TColor.GetColor('#7fb00c'), ROOT.TColor.GetColor('#8a15b1'),
                 ROOT.TColor.GetColor('#57a1e8'), ROOT.TColor.GetColor('#e88000'), ROOT.TColor.GetColor('#1c587e'), ROOT.TColor.GetColor('#b8a91e'),
                 ROOT.TColor.GetColor('#19cbaf'), ROOT.TColor.GetColor('#322a2d'),]
hopper_fill_colors = [  ROOT.TColor.GetColor('#dd9b00'), ROOT.TColor.GetColor('#8394c5'), ROOT.TColor.GetColor('#312a2e'), ROOT.TColor.GetColor('#a5a231'),
                        ROOT.TColor.GetColor('#de5631'), ROOT.TColor.GetColor('#adad81'), ROOT.TColor.GetColor('#0f2634'), ROOT.TColor.GetColor('#344816') ]

def translateToCutString(py_str):
    cut_str = py_str.replace("and", "&&").replace("or", "||").replace("event.", "")
    return cut_str

def makeRatioPlot(h1, h2, h1name, h2name, xname, savename="", logy = False, ytitle=""):

    h1.Sumw2()
    h2.Sumw2()
    c = ROOT.TCanvas("c_"+savename, "c_"+savename, 800, 800)
    if logy: c.SetLogy()

    # Upper plot will be in pad1
    pad1 = ROOT.TPad("pad1", "pad1", 0, 0.3, 1, 1.0)
    pad1.SetBottomMargin(0) # Upper and lower plot are joined
    pad1.SetGridx()         # Vertical grid
    pad1.SetGridy()         # horizontal grid
    pad1.Draw()             # Draw the upper pad: pad1
    pad1.cd()               # pad1 becomes the current pad
    h1.SetStats(0)          # No statistics on upper plot
    maxy = 1.3*getMaximum([h1,h2])
    if logy:
        maxy = 100*maxy
        pad1.SetLogy()
    h2.SetMaximum(maxy)
    h2.SetMinimum(0)
    if logy: h2.SetMinimum(0.001)
    h2.Draw("hist")         # Draw h2 on top of h1
    h2_copy = h2.Clone("h2copy")
    h2_copy.SetFillStyle(3004)
    h2_copy.SetFillColor(ROOT.kBlack)
    h2_copy.SetMarkerSize(0)
    h2_copy.Draw("e2 same")
    h1.Draw("epsame")       # Draw h1

    # Do not draw the Y axis label on the upper plot and redraw a small
    # axis instead, in order to avoid the first label (0) to be clipped.
    h2.GetYaxis().SetLabelSize(0.)
    if logy: axis = ROOT.TGaxis( h1.GetXaxis().GetXmin(), 1, h1.GetXaxis().GetXmin(), maxy, 1, maxy, 510, "G")
    else: axis = ROOT.TGaxis( h1.GetXaxis().GetXmin(), 1, h1.GetXaxis().GetXmin(), maxy, 1, maxy)
    axis.SetLabelFont(43) # Absolute font size in pixel (precision 3)
    axis.SetLabelSize(20)
    axis.SetTitle(ytitle)

    # lower plot will be in pad
    c.cd()          # Go back to the main canvas before defining pad2
    pad2 = ROOT.TPad("pad2", "pad2", 0, 0.05, 1, 0.3)
    pad2.SetTopMargin(0)
    pad2.SetBottomMargin(0.3)
    pad2.SetGridx() # vertical grid
    pad2.SetGridy() # horizontal grid
    pad2.Draw()
    pad2.cd()       # pad2 becomes the current pad

    # Define the ratio plot
    h3 = h1.Clone("h3")
    h3.SetLineColor(ROOT.kBlack)
    h3.Sumw2()
    h3.SetStats(0)      # No statistics on lower plot
    h3.Divide(h2)
    #rmin = max(.5, .95*h3.GetMinimum())
    #rmax = min(1.5, 1.05*h3.GetMaximum())
    rmin = .7
    rmax = 1.3
    h3.SetMinimum(rmin)  # Define Y ..
    h3.SetMaximum(rmax) # .. range
    h3.SetMarkerStyle(20)
    h3.Draw("ep")       # Draw the ratio plot
    h4 = h2.Clone("h4")     # Make hist with error for h2
    for x in xrange(h4.GetNbinsX()):
        if h4.GetBinContent(x+1) != 0:
            h4.SetBinError(x+1,h4.GetBinError(x+1)/h4.GetBinContent(x+1))
        h4.SetBinContent(x+1,1)
    h4.Draw("e2 same")

    # h1 settings
    h1.SetLineColor(ROOT.kBlack)
    h1.SetLineWidth(2)
    h1.SetMarkerStyle(20)

    # Y axis h1 plot settings
    h1.GetYaxis().SetTitleSize(25)
    h1.GetYaxis().SetTitleFont(43)
    h1.GetYaxis().SetTitleOffset(1.55)

    # h2 settings
    h2.SetLineColor(ROOT.kBlack)
    h2.SetFillColor(ROOT.kYellow)
    h2.SetMarkerSize(0)
    h2.SetLineWidth(2)

    # Ratio plot (h3) settings
    h3.GetXaxis().SetTitle(xname)
    h3.SetTitle("") # Remove the ratio title
    h3.SetLineWidth(2)
    h4.SetLineWidth(2)
    h4.SetFillStyle(3004)
    h4.SetFillColor(ROOT.kBlack)
    h4.SetLineColor(ROOT.kBlack)
    h4.SetMarkerSize(0)

    # Y axis ratio plot settings
    h3.GetYaxis().SetTitle("ratio      ")
    h3.GetYaxis().SetNdivisions(505)
    h3.GetYaxis().SetTitleSize(25)
    h3.GetYaxis().SetTitleFont(43)
    h3.GetYaxis().SetTitleOffset(1.55)
    h3.GetYaxis().SetLabelFont(43) # Absolute font size in pixel (precision 3)
    h3.GetYaxis().SetLabelSize(20)

    # X axis ratio plot settings
    h3.GetXaxis().SetTitleSize(25)
    h3.GetXaxis().SetTitleFont(43)
    h3.GetXaxis().SetTitleOffset(4.05)
    h3.GetXaxis().SetLabelFont(43) # Absolute font size in pixel (precision 3)
    h3.GetXaxis().SetLabelSize(20)
    h3.GetXaxis().SetLabelOffset(.02)

    l = ROOT.TLine(h3.GetXaxis().GetXmin(),1.0,h3.GetXaxis().GetXmax(),1.0)
    l.SetLineColor(ROOT.kBlack)
    l.SetLineWidth(2)
    l.Draw("same")

    # Draw legend
    pad1.cd()
    leg = ROOT.TLegend(.5,.7,.8,.85)
    leg.AddEntry(h1, h1name, "p")
    leg.AddEntry(h2, h2name, "f")
    leg.Draw("same")
    axis.Draw()

    c.Update()
    #raw_input("...")
    if savename != "": c.SaveAs(savename)
    return c

def drawTwoPads(top_hists, bottom_hist, savename="", logTop=False, logBottom=False):

    c = ROOT.TCanvas("c", "c")
    leg = ROOT.TLegend(.78, .6, .88, .88)

    # Get maxes/mins of all hists
    maxy_top = 1.3*getMaximum(top_hists)
    miny_top = 0
    if logTop:
        maxy_top*=10
        miny_top = .000001

    # Upper plot will be in pad1
    pad1 = ROOT.TPad("pad1", "pad1", 0, 0.3, 1, 1.0)
    pad1.SetBottomMargin(0.1) # Upper and lower plot are close
    #pad1.SetGridx()         # Vertical grid
    pad1.SetGridy()         # horizontal grid
    pad1.Draw()             # Draw the upper pad: pad1
    pad1.cd()               # pad1 becomes the current pad

    top_hists[0].Draw("e")
    i=0
    for h in top_hists:
        h.SetMarkerSize(0)
        h.SetLineWidth(2)
        h.SetLineColor(more_colors[i])
        h.SetMaximum(maxy_top)
        h.SetMinimum(miny_top)
        h.Draw("e same")
        leg.AddEntry(h, h.GetName(), "l")
        i+=1
    leg.Draw()

    # lower plot will be in pad
    c.cd()          # Go back to the main canvas before defining pad2
    pad2 = ROOT.TPad("pad2", "pad2", 0, 0.05, 1, 0.3)
    pad2.SetTopMargin(0)
    pad2.SetBottomMargin(0.3)
    #pad2.SetGridx() # vertical grid
    pad2.SetGridy() # horizontal grid
    pad2.Draw()
    pad2.cd()       # pad2 becomes the current pad

    bottom_hist.SetMarkerSize(0)
    bottom_hist.SetFillStyle(3003)
    bottom_hist.SetFillColor(ROOT.kBlue-9)
    bottom_hist.SetLineColor(ROOT.kBlue-9)
    bottom_hist.Draw("e hist")

    # Top plot settings
    top_hists[0].GetXaxis().SetLabelSize(0)
    top_hists[0].GetYaxis().SetTitleSize(.045)
    top_hists[0].GetYaxis().SetTitleOffset(1.1)
    top_hists[0].GetYaxis().SetLabelSize(.045)

    # Y axis ratio plot settings
    bottom_hist.GetYaxis().SetNdivisions(505)
    bottom_hist.GetYaxis().SetTitleSize(15)
    bottom_hist.GetYaxis().SetTitleFont(43)
    bottom_hist.GetYaxis().SetTitleOffset(1.55)
    bottom_hist.GetYaxis().SetLabelFont(43) # Absolute font size in pixel (precision 3)
    bottom_hist.GetYaxis().SetLabelSize(15)

    # X axis ratio plot settings
    #bottom_hist.GetXaxis().SetTitleSize(15)
    bottom_hist.GetXaxis().SetTitleSize(0)
    bottom_hist.GetXaxis().SetTitleFont(43)
    bottom_hist.GetXaxis().SetTitleOffset(3.5)
    bottom_hist.GetXaxis().SetLabelFont(43) # Absolute font size in pixel (precision 3)
    #bottom_hist.GetXaxis().SetLabelSize(15)
    bottom_hist.GetXaxis().SetLabelSize(10)
    bottom_hist.GetXaxis().SetLabelOffset(.02)

    if logTop: pad1.SetLogy()
    if logBottom: pad2.SetLogy()
    c.Update()
    raw_input("...")
    if savename != "": c.SaveAs(savename)

def getTreesAndCrossSections(sample_list, input_loc, lumi=1.):
    total_n_events = 0
    total_weighted_events = 0
    t_ee = {}
    cs_weight_ee = {}
    for dsid in sample_list:

        # Find filename
        # Adding fix in case people have multiple versions of the same dsid -- only grab xxxxxx.root unless it doesn't exist
        file_name = ""
        for fn in os.listdir(input_loc):
            if fn == str(dsid)+".root": file_name = fn
        if file_name == "":
            for fn in os.listdir(input_loc):
                if str(dsid) in fn: file_name = fn
        if file_name == "":
            print "Couldn't find input file for dsid", dsid, ". Continuing."
            continue
        print "using filename", file_name

        if file_name.startswith("mc15_13TeV"): t_ee[dsid] = getTree(input_loc + file_name+"/big.root")
        else: t_ee[dsid] = getTree(input_loc + file_name)
        cs_weight_ee[dsid] = lumi*getCrossSection(int(dsid), False)

        # To make changes to XSs
        #if dsid in xrange(361381,361395+1) or dsid in xrange(361405, 361419+1):
        #    print "Making correction for high pT Zs."
        #    cs_weight_ee[dsid] *= 1.1

        if file_name.startswith("mc15_13TeV"): n_events = getNEvents(input_loc+file_name+"/", "big.root")
        else: n_events = getNEvents(input_loc, file_name)
        #print "Number of events:", n_events
        if n_events == 0:
            print "WARNING!!! FOUND 0 EVENTS IN FILE"
            cs_weight_ee[dsid] = 0
        else: cs_weight_ee[dsid] *= 1./n_events
        #print "Weight:", cs_weight_ee[dsid]
        total_n_events += n_events
        total_weighted_events += n_events*cs_weight_ee[dsid]

    print "Total unweighted events:", total_n_events
    print "Total weighted events:  ", total_weighted_events

    return (t_ee, cs_weight_ee)


def getCrossSection(dsid, verbose = True):
    # source_file = "/afs/cern.ch/user/t/tholmes/SusyZMET/trunk/SusyZMETjetsWorkArea/TheEventLoop/data/susy_crosssections_13TeV.txt"
    source_file = "/afs/cern.ch/user/m/mazhang/Projects/SUSYFramework/TheEventLoop/data/susy_crosssections_13TeV.txt"
    with open(source_file, 'r+') as f:
        for line in f.readlines():
            if not line.startswith(str(dsid)): continue
            if verbose: print "CS:", line.split()[2], "K:", line.split()[3], "FILT_EFF:", line.split()[4]
            return float(line.split()[2])*float(line.split()[3])*float(line.split()[4])
    if verbose: print "ERROR: COULDN'T FIND CS FOR", dsid, "IN SUSY FILE."
    return -1

def getNEvents(dir, match_str, weighted=True):
    total_events = 0
    file_names = os.listdir(dir)
    if match_str in file_names: file_names = [match_str] # Add a protection -- if you find exact name don't look for more
    for fn in file_names:
        fn = dir + fn
        if match_str not in fn: continue
        print dir
        f = ROOT.TFile(fn)
        h_events = f.Get("EventCountHist")
        if type(h_events) == ROOT.TObject:
            print "WARNING! DIDN'T FIND FILE"
        else:
            if weighted: total_events += h_events.GetBinContent(2)
            else: total_events += h_events.GetBinContent(1)
    return total_events

def getTree(input_file):
    print "Opening file", input_file
    t = ROOT.TChain('outputTree')
    t.Add(input_file)
    return t

def getDictHist(t, weights, hname, var, binstr="", sel_name="", verb=False):
    i=0
    for k in t.keys():
        indexed_sel_name = "%f*(%s)" % (weights[k], sel_name)
        if i==0: h = getHist(t[k], hname+str(i), var, binstr, indexed_sel_name, verbose=verb)
        else: h.Add(getHist(t[k], hname+str(i), var, binstr, indexed_sel_name, verbose=verb))
        i+=1
    if i==0: print "EMPTY KEYS!"
    return h

def getHist(t, hname, value_name, binstr="", sel_name="", verbose=False):
    draw_cmd = '%s>>%s' % (value_name, hname)
    if binstr != "":
        draw_cmd += "(%s)" % (binstr)
    if sel_name != "": t.Draw( draw_cmd, '(%s)' % (sel_name) )
    else: t.Draw( draw_cmd )
    if verbose: print draw_cmd, '(%s)' % (sel_name)
    h = ROOT.gROOT.FindObject(hname)
    return h

def scaleHists(hists, scaleMax=False):
    for h in hists:
        h.Sumw2()
        if scaleMax:
            if (h.GetMaximum()>0): h.Scale(1/h.GetMaximum())
        else:
            if (h.Integral()>0): h.Scale(1/h.Integral())

def getMaximum(hists, isLog=False):
    max_factor = 1.1
    if isLog: max_factor = 10
    maximum = max(hists[i].GetMaximum() for i in xrange(len(hists)))
    return maximum*max_factor

def getMinimum(hists, isLog=False):
    minimum = min(hists[i].GetMinimum() for i in xrange(len(hists)))
    return minimum

def getBinstr(hists, plot_frac=.99):

    xmaximum = 0
    xminimum = 0
    nbins = 50

    # Check if should be an int plot
    if "_n" in hists[0].GetName():
        max_int = max(hists[i].Integral() for i in xrange(len(hists)))
        ref_hist = hists[0]
        for h in hists:
            if h.Integral() == max_int: ref_hist = h
        xminimum = int(ref_hist.GetBinLowEdge(1))
        xmaximum = int(ref_hist.GetBinLowEdge(ref_hist.GetNbinsX())+3)
        nbins = xmaximum - xminimum
        return str(nbins)+","+str(xminimum)+","+str(xmaximum)

    for h in hists:
        if h.GetEntries()==0: continue
        found_edge = False
        # Get X max
        for x in xrange(h.GetNbinsX()):
            if x==0: continue
            #print "High", x, h.Integral(1, x), h.Integral(), h.GetBinLowEdge(x)
            if h.Integral(1, x) > plot_frac*h.Integral():
                newxmax = 1.1*h.GetBinLowEdge(x)
                if newxmax > xmaximum : xmaximum = newxmax
                found_edge = True
                break
        if not found_edge: xmaximum = ( h.GetBinLowEdge(h.GetNbinsX()) + h.GetBinWidth(h.GetNbinsX()) )


        # Get X min
        found_edge = False
        if h.GetBinLowEdge(1)==0: continue
        for x in reversed(xrange(h.GetNbinsX())):
            if x==0: continue
            #print "Low", x, h.Integral(x, h.GetNbinsX()), h.Integral(), h.GetBinLowEdge(x)
            if h.Integral(x, h.GetNbinsX()) > plot_frac*h.Integral():
                newxmin = 1.1*h.GetBinLowEdge(x)
                if newxmin < xminimum : xminimum = newxmin
                found_edge = True
                break
        if not found_edge: xminimum = ( h.GetBinLowEdge(1))

    return str(nbins)+","+str(xminimum)+","+str(xmaximum)

def printEfficiency(hist1, hist2):
    num = hist1.Integral(0,hist1.GetXaxis().GetNbins()+1)
    den = hist2.Integral(0,hist2.GetXaxis().GetNbins()+1)
    print "Efficiency for", hist1.GetName(), ":", str(num/den)

def drawStatsBoxes(hists, canname):
    # Draw once to get stats boxes
    ROOT.gStyle.SetOptStat(1)

    can = ROOT.TCanvas("temp_"+canname, "temp_"+canname)
    stats = []
    num = len(hists)
    top = .9# .85
    bottom = .25
    padding = .02
    width = (top-bottom-padding*num)/num

    #colors3 = [ROOT.kRed, ROOT.kBlue]
    #for x in xrange(len(hists)): hists[x].SetLineColor(colors[x])

    for x in xrange(len(hists)):
        name = hists[x].GetName().split("_")[1] + " " + hists[x].GetName().split("_")[2].split("3")[0]
        h = hists[x].Clone(name)
        if x==0: h.Draw()
        else: h.Draw('sames')
        can.Update()
        stats.append(h.GetListOfFunctions().FindObject("stats").Clone('Res_'+hists[x].GetName()))

        this_top = top - x*(width+padding)
        this_bottom = this_top - width

        #stats[x].SetX1NDC(0.15)
        #stats[x].SetX2NDC(0.35)
        stats[x].SetX1NDC(0.90)
        stats[x].SetX2NDC(0.70)
        stats[x].SetY1NDC(this_bottom)
        stats[x].SetY2NDC(this_top)
        stats[x].SetTextColor(hists[x].GetLineColor())
        stats[x].SetLineColor(hists[x].GetLineColor())

    ROOT.gStyle.SetOptStat(0)

    return stats

def addOverflow(h):
    h_tmp = h.Clone(h.GetName()+"_tmp")
    h_tmp.Reset()
    last_bin = h_tmp.GetNbinsX()
    h_tmp.SetBinContent(last_bin, h.GetBinContent(last_bin+1))
    h_tmp.SetBinError(last_bin, h.GetBinError(last_bin+1))
    h.Add(h_tmp)
    return h
