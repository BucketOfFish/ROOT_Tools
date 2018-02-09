import ROOT
ROOT.gROOT.Macro('$ROOTCOREDIR/scripts/load_packages.C')
ROOT.xAOD.Init()

f = ROOT.TFile.Open("DAOD_SUSY2.05892065._000002.pool.root.1")
t = ROOT.xAOD.MakeTransientTree(f, "CollectionTree")
f_out = ROOT.TFile("output.root", "recreate")
h_mll = ROOT.TH1F('mll','mll',50,0,200)
h_pID = ROOT.TH1F('pID','pID',200,0,200)

for entry in xrange(t.GetEntries()):
    if entry%1000==0:
        print(""+str(entry)+" out of "+str(t.GetEntries()))
    t.GetEntry(entry)
    nZlep = 0;
    ZlepIndex1 = 0;
    ZlepIndex2 = 0;
    for i in xrange(t.TruthParticles.size()):
        p = t.TruthParticles.at(i)
        if not p.parent():
            continue
        pID = p.parent().pdgId()
        ID = p.pdgId()
        h_pID.Fill(pID)
        if (abs(pID)==23):
            if (abs(ID)==11 or abs(ID)==13):
                nZlep = nZlep+1;
                if (nZlep==1):
                    p1 = p 
                elif (nZlep==2):
                    p2 = p
    if (nZlep==2):
        l1 = ROOT.TLorentzVector()
        l2 = ROOT.TLorentzVector()
        l1.SetPtEtaPhiM(p1.pt(), p1.eta(), p1.phi(), p1.m())
        l2.SetPtEtaPhiM(p2.pt(), p2.eta(), p2.phi(), p2.m())
        M = (l1+l2).M()/1000
        h_mll.Fill(M)

f_out.Write()
f_out.Close()
