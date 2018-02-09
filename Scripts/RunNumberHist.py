import ROOT

oldFile = ROOT.TFile('oldData.root')
newFile = ROOT.TFile('newData.root')
oldData = oldFile.Get('outputTree')
newData = newFile.Get('outputTree')

oldRunCount = {}
newRunCount = {}

for event in oldData:
    oldRunCount[event.RunNumber] = oldRunCount.setdefault(event.RunNumber,0)+1

for event in newData:
    newRunCount[event.RunNumber] = newRunCount.setdefault(event.RunNumber,0)+1

for key in oldRunCount:
	if not key in newRunCount:
		newRunCount[key] = 0

for key in newRunCount:
	if not key in oldRunCount:
		newRunCount[key] = 0

oldHist = ROOT.TH1F('oldRunCount', '', len(oldRunCount.keys()), 0, len(oldRunCount.keys()))
for n, a in enumerate(sorted(oldRunCount.keys())):
    oldHist.SetBinContent(n+1, oldRunCount[a])
    oldHist.GetXaxis().SetBinLabel(n+1, str(a))

newHist = ROOT.TH1F('newRunCount', '', len(newRunCount.keys()), 0, len(newRunCount.keys()))
for n, a in enumerate(sorted(newRunCount.keys())):
    newHist.SetBinContent(n+1, newRunCount[a])
    newHist.GetXaxis().SetBinLabel(n+1, str(a))

ROOT.gStyle.SetOptStat(0)
oldHist.Draw()
newHist.SetLineColor(ROOT.kRed)
newHist.Draw("same")
legend = ROOT.TLegend(0.6,0.6,0.8,0.8)
legend.AddEntry(oldHist, "Old Data")
legend.AddEntry(newHist, "New Data")
legend.Draw()
