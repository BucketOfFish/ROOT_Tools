#include <iostream>


#include "VertexAnalysis/VertexAnalysis.h"
#include "InDetTruthVertexValidation/InDetVertexTruthMatchUtils.h"


VertexAnalysis::VertexAnalysis() {
    m_entryNumber = 0;
}

VertexAnalysis::~VertexAnalysis() {
}


// Return pointers to histograms and a stream name to help categorize output
std::vector< std::pair<TH1*,std::string> > VertexAnalysis::bookHistograms() {

    std::vector< std::pair<TH1*,std::string> > histoAndStream;


    //---
    // Plots that depend only on the vertexContainer and will work for any, even if data or no matching done.
    std::string streamName = "default";

    h_nVtx = new TH1F("h_nVtx", "N vertices", 50, -0.5, 100.5);
    h_nVtx->GetXaxis()->SetTitle("n_{Vtx}");
    histoAndStream.push_back(std::make_pair(h_nVtx,streamName));

    h_mu = new TH1F("h_mu","actualIntPerXing;actualIntPerXing",101,-0.5,100.5);
    histoAndStream.push_back(std::make_pair(h_mu,streamName));

    p_nVtx_Mu = new TProfile("p_nVtx_Mu", "p_nVtx_Mu", 101, -0.5, 100.5);
    p_nVtx_Mu->GetYaxis()->SetTitle("n_{Vtx}");
    p_nVtx_Mu->GetXaxis()->SetTitle("{\\mu}");
    histoAndStream.push_back(std::make_pair(p_nVtx_Mu,streamName));

    //overall position
    h_x = new TH1F("h_x","x pos of vertices", 50, -0.05, 0.05);
    h_x->GetXaxis()->SetTitle("x [mm]");
    histoAndStream.push_back(std::make_pair(h_x,streamName));

    h_y = new TH1F("h_y","y pos of vertices", 50, -0.05, 0.05);
    h_y->GetXaxis()->SetTitle("y [mm]");
    histoAndStream.push_back(std::make_pair(h_y,streamName));

    h_z = new TH1F("h_z","z pos of vertices", 50, -200.0, 200.0);
    h_z->GetXaxis()->SetTitle("z [mm]");
    histoAndStream.push_back(std::make_pair(h_z,streamName));

    h_HSTruex = new TH1F("h_HSTruex","x pos of vertices", 200, -0.2, 0.2);
    h_HSTruex->GetXaxis()->SetTitle("x [mm]");
    histoAndStream.push_back(std::make_pair(h_HSTruex,streamName));

    h_HSTruey = new TH1F("h_HSTruey","y pos of vertices", 200, -0.2, 0.2);
    h_HSTruey->GetXaxis()->SetTitle("y [mm]");
    histoAndStream.push_back(std::make_pair(h_HSTruey,streamName));

    h_HSTruez = new TH1F("h_HSTruez","z pos of vertices", 200, -200.0, 200.0);
    h_HSTruez->GetXaxis()->SetTitle("z [mm]");
    histoAndStream.push_back(std::make_pair(h_HSTruez,streamName));

    h_HSRecox = new TH1F("h_HSRecox","x pos of vertices", 200, -0.2, 0.2);
    h_HSRecox->GetXaxis()->SetTitle("x [mm]");
    histoAndStream.push_back(std::make_pair(h_HSRecox,streamName));

    h_HSRecoy = new TH1F("h_HSRecoy","y pos of vertices", 200, -0.2, 0.2);
    h_HSRecoy->GetXaxis()->SetTitle("y [mm]");
    histoAndStream.push_back(std::make_pair(h_HSRecoy,streamName));

    h_HSRecoz = new TH1F("h_HSRecoz","z pos of vertices", 200, -200.0, 200.0);
    h_HSRecoz->GetXaxis()->SetTitle("z [mm]");
    histoAndStream.push_back(std::make_pair(h_HSRecoz,streamName));

    //delta z between vertices
    h_Dz = new TH1F("h_Dz", "h_Dz", 100, -20.0, 20.0);
    h_Dz->GetXaxis()->SetTitle("#Deltaz [mm]");
    histoAndStream.push_back(std::make_pair(h_Dz,streamName));

    //delta x,y,z between reco and truth HS vertices
    h_xHSRes = new TH1F("h_xHSRes", "h_xHSRes", 20, -0.05, 0.05);
    h_yHSRes = new TH1F("h_yHSRes", "h_yHSRes", 20, -0.05, 0.05);
    h_zHSRes = new TH1F("h_zHSRes", "h_zHSRes", 20, -0.1, 0.1);
    h_xHSRes->GetXaxis()->SetTitle("#Deltax(reco-truth) [mm]");
    h_yHSRes->GetXaxis()->SetTitle("#Deltay(reco-truth) [mm]");
    h_zHSRes->GetXaxis()->SetTitle("#Deltaz(reco-truth) [mm]");
    histoAndStream.push_back(std::make_pair(h_xHSRes,streamName));
    histoAndStream.push_back(std::make_pair(h_yHSRes,streamName));
    histoAndStream.push_back(std::make_pair(h_zHSRes,streamName));



    //---
    // Plots that depend on a matching info decorated vertexContainer.
    streamName = "TruthMatching";


    h_nClass = new TH1F("h_nClass", "h_nClass", 4, -0.5, 3.5);
    h_nClass->GetXaxis()->SetTitle("n_{Class}");
    h_nClass->GetXaxis()->SetBinLabel(1, "Matched");
    h_nClass->GetXaxis()->SetBinLabel(2, "Merged");
    h_nClass->GetXaxis()->SetBinLabel(3, "Split");
    h_nClass->GetXaxis()->SetBinLabel(4, "Fake");
    histoAndStream.push_back(std::make_pair(h_nClass,streamName));

    //selection and reconstruction efficiencies
    h_HSSelEff = new TH1F("h_HSSelEff", "h_HSSelEff", 2, -0.5, 3.5);
    h_HSSelEff->GetXaxis()->SetTitle("n_{Class}");
    h_HSSelEff->GetXaxis()->SetBinLabel(1, "Selected");
    h_HSSelEff->GetXaxis()->SetBinLabel(2, "Not Selected");
    histoAndStream.push_back(std::make_pair(h_HSSelEff,streamName));
    h_HSRecEff = new TH1F("h_HSRecEff", "h_HSRecEff", 2, -0.5, 3.5);
    h_HSRecEff->GetXaxis()->SetTitle("n_{Class}");
    h_HSRecEff->GetXaxis()->SetBinLabel(1, "Reconstructed");
    h_HSRecEff->GetXaxis()->SetBinLabel(2, "Not Reconstructed");
    histoAndStream.push_back(std::make_pair(h_HSRecEff,streamName));

    //number of tracks associated to HS vertex, and their sumPt2
    h_HSnTracks = new TH1F("h_HSnTracks", "h_HSnTracks", 100, 0, 500.0);
    h_HSnTracks->GetXaxis()->SetTitle("Number of Tracks Associated with HS");
    histoAndStream.push_back(std::make_pair(h_HSnTracks,streamName));
    h_HSTrackPts = new TH1F("h_HSTrackPts", "h_HSTrackPts", 100, 0, 400.0);
    h_HSTrackPts->GetXaxis()->SetTitle("Pt of Tracks Associated with HS (GeV)");
    histoAndStream.push_back(std::make_pair(h_HSTrackPts,streamName));
    h_HSSumPtTracks = new TH1F("h_HSSumPtTracks", "h_HSSumPtTracks", 100, 0, 1000);
    h_HSSumPtTracks->GetXaxis()->SetTitle("SumPt of Tracks Associated with HS (GeV)");
    histoAndStream.push_back(std::make_pair(h_HSSumPtTracks,streamName));
    h_HSSumPt2Tracks = new TH1F("h_HSSumPt2Tracks", "h_HSSumPt2Tracks", 100, 0, 10000);
    h_HSSumPt2Tracks->GetXaxis()->SetTitle("SumPt^2 of Tracks Associated with HS (GeV^2)");
    histoAndStream.push_back(std::make_pair(h_HSSumPt2Tracks,streamName));

    //number of tracks associated to HS vertex, and their sumPt2 for muons
    h_HSnTracksMuons = new TH1F("h_HSnTracksMuons", "h_HSnTracksMuons", 100, 0, 500.0);
    h_HSnTracksMuons->GetXaxis()->SetTitle("Number of Muon Tracks Associated with HS");
    histoAndStream.push_back(std::make_pair(h_HSnTracksMuons,streamName));
    h_HSTrackPtsMuons = new TH1F("h_HSTrackPtsMuons", "h_HSTrackPtsMuons", 100, 0, 100.0);
    h_HSTrackPtsMuons->GetXaxis()->SetTitle("Pt of Muon Tracks Associated with HS (GeV)");
    histoAndStream.push_back(std::make_pair(h_HSTrackPtsMuons,streamName));
    h_HSSumPtTracksMuons = new TH1F("h_HSSumPtTracksMuons", "h_HSSumPtTracksMuons", 100, 0, 1000);
    h_HSSumPtTracksMuons->GetXaxis()->SetTitle("SumPt of Muon Tracks Associated with HS (GeV)");
    histoAndStream.push_back(std::make_pair(h_HSSumPtTracksMuons,streamName));
    h_HSSumPt2TracksMuons = new TH1F("h_HSSumPt2TracksMuons", "h_HSSumPt2TracksMuons", 100, 0, 10000);
    h_HSSumPt2TracksMuons->GetXaxis()->SetTitle("SumPt^2 of Muon Tracks Associated with HS (GeV^2)");
    histoAndStream.push_back(std::make_pair(h_HSSumPt2TracksMuons,streamName));

    //number of tracks associated to HS vertex, and their sumPt2 for nonmuons
    h_HSnTracksNonMuons = new TH1F("h_HSnTracksNonMuons", "h_HSnTracksNonMuons", 100, 0, 500.0);
    h_HSnTracksNonMuons->GetXaxis()->SetTitle("Number of NonMuon Tracks Associated with HS");
    histoAndStream.push_back(std::make_pair(h_HSnTracksNonMuons,streamName));
    h_HSTrackPtsNonMuons = new TH1F("h_HSTrackPtsNonMuons", "h_HSTrackPtsNonMuons", 100, 0, 100.0);
    h_HSTrackPtsNonMuons->GetXaxis()->SetTitle("Pt of NonMuon Tracks Associated with HS (GeV)");
    histoAndStream.push_back(std::make_pair(h_HSTrackPtsNonMuons,streamName));
    h_HSSumPtTracksNonMuons = new TH1F("h_HSSumPtTracksNonMuons", "h_HSSumPtTracksNonMuons", 100, 0, 1000);
    h_HSSumPtTracksNonMuons->GetXaxis()->SetTitle("SumPt of NonMuon Tracks Associated with HS (GeV)");
    histoAndStream.push_back(std::make_pair(h_HSSumPtTracksNonMuons,streamName));
    h_HSSumPt2TracksNonMuons = new TH1F("h_HSSumPt2TracksNonMuons", "h_HSSumPt2TracksNonMuons", 100, 0, 10000);
    h_HSSumPt2TracksNonMuons->GetXaxis()->SetTitle("SumPt^2 of NonMuon Tracks Associated with HS (GeV^2)");
    histoAndStream.push_back(std::make_pair(h_HSSumPt2TracksNonMuons,streamName));

    //number of tracks associated to non-HS vertices
    h_nTracks = new TH1F("h_nTracks", "h_nTracks", 10, 0, 50.0);
    h_nTracks->GetXaxis()->SetTitle("Number of Tracks Associated with non-HS Vertices");
    histoAndStream.push_back(std::make_pair(h_nTracks,streamName));

    //percentage of correctly associated tracks (for all vertices)
    h_percentCorrectTracks  = new TH1F("h_percentCorrectTracks  ", "h_percentCorrectTracks  ", 50, 0, 1.0);
    h_percentCorrectTracks ->GetXaxis()->SetTitle("Percentage of Correctly Associated Tracks in a Vertex");
    histoAndStream.push_back(std::make_pair(h_percentCorrectTracks,streamName));

    //z distance between splits matching same true interaction
    h_DzSplits = new TH1F("h_DzSplits", "h_DzSplits", 200, -10.0, 10.0);
    h_DzSplits->GetXaxis()->SetTitle("#Deltaz [mm]");
    histoAndStream.push_back(std::make_pair(h_DzSplits,streamName));

    //number of vertex type v. mu
    p_nMatch_Mu = new TProfile("p_nMatch_Mu", "p_nMatch_Mu", 101, -0.5, 100.5);
    p_nMatch_Mu->GetYaxis()->SetTitle("n_{Match}");
    p_nMatch_Mu->GetXaxis()->SetTitle("{\\mu}");
    histoAndStream.push_back(std::make_pair(p_nMatch_Mu,streamName));

    p_nMerge_Mu = new TProfile("p_nMerge_Mu", "p_nMerge_Mu", 101, -0.5, 100.5);
    p_nMerge_Mu->GetYaxis()->SetTitle("n_{Merge}");
    p_nMerge_Mu->GetXaxis()->SetTitle("{\\mu}");
    histoAndStream.push_back(std::make_pair(p_nMerge_Mu,streamName));

    p_nSplit_Mu = new TProfile("p_nSplit_Mu", "p_nSplit_Mu", 101, -0.5, 100.5);
    p_nSplit_Mu->GetYaxis()->SetTitle("n_{Split}");
    p_nSplit_Mu->GetXaxis()->SetTitle("{\\mu}");
    histoAndStream.push_back(std::make_pair(p_nSplit_Mu,streamName));

    p_nFake_Mu = new TProfile("p_nFake_Mu", "p_nFake_Mu", 101, -0.5, 100.5);
    p_nFake_Mu->GetYaxis()->SetTitle("n_{Fake}");
    p_nFake_Mu->GetXaxis()->SetTitle("{\\mu}");
    histoAndStream.push_back(std::make_pair(p_nFake_Mu,streamName));

    //rate plots v. mu
    p_MatchRate_Mu = new TProfile("p_MatchRate_Mu", "p_MatchRate_Mu", 101, -0.5, 100.5);
    p_MatchRate_Mu->GetYaxis()->SetTitle("MatchRate");
    p_MatchRate_Mu->GetXaxis()->SetTitle("{\\mu}");
    histoAndStream.push_back(std::make_pair(p_MatchRate_Mu,streamName));

    p_MergeRate_Mu = new TProfile("p_MergeRate_Mu", "p_MergeRate_Mu", 101, -0.5, 100.5);
    p_MergeRate_Mu->GetYaxis()->SetTitle("MergeRate");
    p_MergeRate_Mu->GetXaxis()->SetTitle("{\\mu}");
    histoAndStream.push_back(std::make_pair(p_MergeRate_Mu,streamName));

    p_SplitRate_Mu = new TProfile("p_SplitRate_Mu", "p_SplitRate_Mu", 101, -0.5, 100.5);
    p_SplitRate_Mu->GetYaxis()->SetTitle("SplitRate");
    p_SplitRate_Mu->GetXaxis()->SetTitle("{\\mu}");
    histoAndStream.push_back(std::make_pair(p_SplitRate_Mu,streamName));

    p_FakeRate_Mu = new TProfile("p_FakeRate_Mu", "p_FakeRate_Mu", 101, -0.5, 100.5);
    p_FakeRate_Mu->GetYaxis()->SetTitle("FakeRate");
    p_FakeRate_Mu->GetXaxis()->SetTitle("{\\mu}");
    histoAndStream.push_back(std::make_pair(p_FakeRate_Mu,streamName));


    //rate plots v. number of reco vertices
    p_MatchProbability_nVtx = new TProfile("p_MatchProbability_nVtx", "p_MatchProbability_nVtx", 101, -0.5, 100.5);
    p_MatchProbability_nVtx->GetYaxis()->SetTitle("MatchProbability");
    p_MatchProbability_nVtx->GetXaxis()->SetTitle("n_{Vtx}");
    histoAndStream.push_back(std::make_pair(p_MatchProbability_nVtx,streamName));

    p_MergeProbability_nVtx = new TProfile("p_MergeProbability_nVtx", "p_MergeProbability_nVtx", 101, -0.5, 100.5);
    p_MergeProbability_nVtx->GetYaxis()->SetTitle("MergeProbability");
    p_MergeProbability_nVtx->GetXaxis()->SetTitle("n_{Vtx}");
    histoAndStream.push_back(std::make_pair(p_MergeProbability_nVtx,streamName));

    p_SplitProbability_nVtx = new TProfile("p_SplitProbability_nVtx", "p_SplitProbability_nVtx", 101, -0.5, 100.5);
    p_SplitProbability_nVtx->GetYaxis()->SetTitle("SplitProbability");
    p_SplitProbability_nVtx->GetXaxis()->SetTitle("n_{Vtx}");
    histoAndStream.push_back(std::make_pair(p_SplitProbability_nVtx,streamName));

    p_FakeProbability_nVtx = new TProfile("p_FakeProbability_nVtx", "p_FakeProbability_nVtx", 101, -0.5, 100.5);
    p_FakeProbability_nVtx->GetYaxis()->SetTitle("FakeProbability");
    p_FakeProbability_nVtx->GetXaxis()->SetTitle("n_{Vtx}");
    histoAndStream.push_back(std::make_pair(p_FakeProbability_nVtx,streamName));


    //hard scatter categorization
    h_HSCategory = new TH1F("h_HSCategory", "h_HSCategory", 5, -0.5, 4.5);
    h_HSCategory->GetXaxis()->SetTitle("HSCategory");
    h_HSCategory->GetXaxis()->SetBinLabel(1, "Clean");
    h_HSCategory->GetXaxis()->SetBinLabel(2, "Low PU");
    h_HSCategory->GetXaxis()->SetBinLabel(3, "High PU");
    h_HSCategory->GetXaxis()->SetBinLabel(4, "Split");
    h_HSCategory->GetXaxis()->SetBinLabel(5, "No match");  
    histoAndStream.push_back(std::make_pair(h_HSCategory,streamName));

    // also v. mu
    h_HSCategory_Mu = new TH2F("h_HSCategory_vMu","h_HSCategory_vMu;#mu;HSCategory",101,-0.5,100.5,5,-0.5,4.5);
    h_HSCategory_Mu->GetYaxis()->SetBinLabel(1, "Clean");
    h_HSCategory_Mu->GetYaxis()->SetBinLabel(2, "Low PU");
    h_HSCategory_Mu->GetYaxis()->SetBinLabel(3, "High PU");
    h_HSCategory_Mu->GetYaxis()->SetBinLabel(4, "Split");
    h_HSCategory_Mu->GetYaxis()->SetBinLabel(5, "No match");  
    histoAndStream.push_back(std::make_pair(h_HSCategory_Mu,streamName));

    // truth events, pileup
    h_nTruthEvents = new TH1F("h_nTruthEvents", "h_nTruthEvents", 100, 0, 100);
    h_nTruthEvents->GetYaxis()->SetTitle("");
    h_nTruthEvents->GetXaxis()->SetTitle("Number of Truth Events");
    histoAndStream.push_back(std::make_pair(h_nTruthEvents,streamName));

    h_nTruthPileupEvents = new TH1F("h_nTruthPileupEvents", "h_nTruthPileupEvents", 50, 0, 50);
    h_nTruthPileupEvents->GetYaxis()->SetTitle("");
    h_nTruthPileupEvents->GetXaxis()->SetTitle("Number of Truth Pileup Events");
    histoAndStream.push_back(std::make_pair(h_nTruthPileupEvents,streamName));

    h_nTruthVertices = new TH1F("h_nTruthVertices", "h_nTruthVertices", 100, 0, 3000);
    h_nTruthVertices->GetYaxis()->SetTitle("");
    h_nTruthVertices->GetXaxis()->SetTitle("Number of Truth Vertices");
    histoAndStream.push_back(std::make_pair(h_nTruthVertices,streamName));

    h_nTruthParticles = new TH1F("h_nTruthParticles", "h_nTruthParticles", 100, 0, 10000);
    h_nTruthParticles->GetYaxis()->SetTitle("");
    h_nTruthParticles->GetXaxis()->SetTitle("Number of Truth Particles");
    histoAndStream.push_back(std::make_pair(h_nTruthParticles,streamName));

    h_nTruthPileupVertices = new TH1F("h_nTruthPileupVertices", "h_nTruthPileupVertices", 100, 0, 3000);
    h_nTruthPileupVertices->GetYaxis()->SetTitle("");
    h_nTruthPileupVertices->GetXaxis()->SetTitle("Number of Truth Pileup Vertices");
    histoAndStream.push_back(std::make_pair(h_nTruthPileupVertices,streamName));

    h_nTruthPileupParticles = new TH1F("h_nTruthPileupParticles", "h_nTruthPileupParticles", 100, 0, 3000);
    h_nTruthPileupParticles->GetYaxis()->SetTitle("");
    h_nTruthPileupParticles->GetXaxis()->SetTitle("Number of Truth Pileup Particles");
    histoAndStream.push_back(std::make_pair(h_nTruthPileupParticles,streamName));

    h_TruthPileupx = new TH1F("h_TruthPileupx","x pos of truth pileup vertices", 200, -0.2, 0.2);
    h_TruthPileupx->GetXaxis()->SetTitle("x [mm]");
    histoAndStream.push_back(std::make_pair(h_TruthPileupx,streamName));

    h_TruthPileupy = new TH1F("h_TruthPileupy","y pos of truth pileup vertices", 200, -0.2, 0.2);
    h_TruthPileupy->GetXaxis()->SetTitle("y [mm]");
    histoAndStream.push_back(std::make_pair(h_TruthPileupy,streamName));

    h_TruthPileupz = new TH1F("h_TruthPileupz","z pos of truth pileup vertices", 200, -200.0, 200.0);
    h_TruthPileupz->GetXaxis()->SetTitle("z [mm]");
    histoAndStream.push_back(std::make_pair(h_TruthPileupz,streamName));

    p_Vtx_Reco_True = new TH2F("p_Vtx_Reco_True", "Number of reco vs. true vertices", 80,0,80,80,0,80);  
    p_Vtx_Reco_True->GetXaxis()->SetTitle("Number of Truth Vertices");
    p_Vtx_Reco_True->GetYaxis()->SetTitle("Number of Reco Vertices");
    histoAndStream.push_back(std::make_pair(p_Vtx_Reco_True,streamName));
    //Test histograms

    h_TestHist1 = new TH1F("h_TestHist1","Test histogram 1", 10, 0, 10);
    h_TestHist1->GetXaxis()->SetTitle("Number");
    histoAndStream.push_back(std::make_pair(h_TestHist1,streamName));

    h_TestHist2 = new TH1F("h_TestHist2","Test histogram 2", 100, 0, 100);
    h_TestHist2->GetXaxis()->SetTitle("Number");
    histoAndStream.push_back(std::make_pair(h_TestHist2,streamName));

    h_TestHist3 = new TH1F("h_TestHist3","Test histogram 3", 200, 0, 200);
    h_TestHist3->GetXaxis()->SetTitle("Number");
    histoAndStream.push_back(std::make_pair(h_TestHist3,streamName));

    for (int i=0; i<10; i++) {
        TH1F* hist = new TH1F(TString("h_HSzSplit_"+std::to_string(i)),"z pos of decay vertices from split HS", 800, -100.0, 100.0);
        hist->GetXaxis()->SetTitle("z [mm]");
        histoAndStream.push_back(std::make_pair(hist,streamName));
        h_HSzSplits.push_back(hist);
    }

    return histoAndStream;
}

void VertexAnalysis::fillZChain(TH1F* hist, const xAOD::TruthVertex *thisVert) {
    hist->Fill(thisVert->z());
    for (int i=0; i<thisVert->nOutgoingParticles(); i++) {
        if (thisVert->outgoingParticle(i)->hasDecayVtx())
            fillZChain(hist, thisVert->outgoingParticle(i)->decayVtx());
    }
}

int VertexAnalysis::execute(const xAOD::VertexContainer &vertexContainer, 
        const xAOD::EventInfo & eventInfo,
        const xAOD::TruthEventContainer *const truthEventContainer,
        const xAOD::TruthPileupEventContainer *const truthPileupEventContainer,
        const xAOD::TrackParticleContainer *const trackContainer) {

    //this namespace has a few useful things from truth matching code
    //typedefs for the decoration types, enums of vertex classification, and helper analysis methods
    //its also has a very long name, so lets use it
    //ill try to leave it in a few places below to make things more obvious where they come from
    using namespace InDetVertexTruthMatchUtils;

    // Up the event count.
    m_entryNumber++;

    //---
    // Plots that depend only on the vertexContainer and will work for any, even if data or no matching done.
    size_t vertexContainerSize = vertexContainer.size();

    int nVtx = 0;
    std::vector<std::vector<double>> recoVectorPos = {};

    for(size_t i = 0; i < vertexContainerSize; ++i) {
        if(xAOD::VxType::NoVtx == vertexContainer[i]->vertexType())  continue;

        nVtx++;

        h_x->Fill(vertexContainer[i]->x());
        h_y->Fill(vertexContainer[i]->y());
        h_z->Fill(vertexContainer[i]->z());

        recoVectorPos.push_back({vertexContainer[i]->x(), vertexContainer[i]->y(), vertexContainer[i]->z()});

        for(size_t j = i + 1; j < vertexContainerSize; ++j) {
            if(xAOD::VxType::NoVtx == vertexContainer[j]->vertexType())  continue;

            h_Dz->Fill(vertexContainer[j]->z() - vertexContainer[i]->z());

        }
    }


    h_nVtx->Fill(nVtx);
    float mu = eventInfo.actualInteractionsPerCrossing();
    h_mu->Fill(mu);
    p_nVtx_Mu->Fill(mu,nVtx);

    //---


    //---
    // Plots that depend on a matching info decorated vertexContainer.

    // Decorators needed for vertex analysis.
    xAOD::Vertex::Decorator< InDetVertexTruthMatchUtils::VertexMatchType > matchTypeDecorator("VertexMatchType");
    xAOD::Vertex::Decorator< std::vector< InDetVertexTruthMatchUtils::VertexTruthMatchInfo > > truthMatchInfoDecorator("TruthEventMatchingInfos");
    xAOD::Vertex::Decorator< std::vector< ElementLink< xAOD::VertexContainer > > > splitPartnerDecorator("SplitPartners");

    //check that there is more than just a dummy vertex, and that it has matching information
    bool matchingDone = ( vertexContainer.size() > 0 && 
            vertexContainer[0]->vertexType() != xAOD::VxType::NoVtx &&
            matchTypeDecorator.isAvailable(*(vertexContainer[0])) );

    if(!matchingDone) {
        return 0;
    }

    int nTypes[InDetVertexTruthMatchUtils::NTYPES] = { 0 };

    auto bestHSMatch = InDetVertexTruthMatchUtils::bestHardScatterMatch(vertexContainer);
    if (bestHSMatch==0)
        return 0;

    //Checkpoint - I want to call a function which prints the track info for all tracks associated to each vertex
    InDetVertexTruthMatchUtils::printTrackVertexAssociations(vertexContainer);

    for(size_t i = 0; i < vertexContainerSize; ++i) {
        if(xAOD::VxType::NoVtx == vertexContainer[i]->vertexType()) continue;

        VertexMatchType & type = matchTypeDecorator( *(vertexContainer[i]) );
        //always count the types
        nTypes[type]++;

        //can make special plots for types of interest
        if( type == SPLIT ) {

            std::vector< ElementLink< xAOD::VertexContainer > > &splitPartners = splitPartnerDecorator(*(vertexContainer[i]));

            std::vector<VertexTruthMatchInfo> &truthMatchInfo = truthMatchInfoDecorator(*(vertexContainer[i]));
            auto truthMatchVertex = truthMatchInfo[0].first;
            std::cout<<"Split\t("<<vertexContainer[i]->x()<<","<<vertexContainer[i]->y()<<","<<vertexContainer[i]->z()<<")\tTruth\t("<<(*truthMatchVertex)->truthVertex(0)->x()<<","<<(*truthMatchVertex)->truthVertex(0)->y()<<","<<(*truthMatchVertex)->truthVertex(0)->z()<<")"<<std::endl;
            
            for(auto partner : splitPartners) {
                if(partner.index() < i) {//skip lower idx partners to avoid double counting
                    continue;
                } else {
                    h_DzSplits->Fill((*partner)->z() - vertexContainer[i]->z());
                }
            }

        } //if split

        //Track association
        
        if (bestHSMatch != vertexContainer[i])
            h_nTracks->Fill(InDetVertexTruthMatchUtils::nTracks(vertexContainer[i]));
        h_percentCorrectTracks->Fill(InDetVertexTruthMatchUtils::percentCorrectTracks(vertexContainer[i]));
    }

    h_nClass->Fill(MATCHED, nTypes[MATCHED]);
    h_nClass->Fill(MERGED,  nTypes[MERGED]);
    h_nClass->Fill(SPLIT,   nTypes[SPLIT]);
    h_nClass->Fill(FAKE,    nTypes[FAKE]);

    float MatchProbability = ((float)nTypes[MATCHED]) / nVtx;
    float MergeProbability = ((float)nTypes[MERGED]) / nVtx;
    float SplitProbability = ((float)nTypes[SPLIT]) / nVtx;
    float FakeProbability = ((float)nTypes[FAKE]) / nVtx;

    p_MatchProbability_nVtx->Fill(nVtx, MatchProbability);
    p_MergeProbability_nVtx->Fill(nVtx, MergeProbability);
    p_SplitProbability_nVtx->Fill(nVtx, SplitProbability);
    p_FakeProbability_nVtx->Fill(nVtx, FakeProbability);
    //---


    //---
    // Plots that depend on Mu.

    p_nMatch_Mu->Fill(mu, nTypes[MATCHED]);
    p_nMerge_Mu->Fill(mu, nTypes[MERGED]);
    p_nSplit_Mu->Fill(mu, nTypes[SPLIT]);
    p_nFake_Mu->Fill(mu,  nTypes[FAKE]);

    float MatchRate = ((float)nTypes[MATCHED]) / mu;
    float MergeRate = ((float)nTypes[MERGED]) / mu;
    float SplitRate = ((float)nTypes[SPLIT]) / mu;
    float FakeRate = ((float)nTypes[FAKE]) / mu;

    p_MatchRate_Mu->Fill(mu, MatchRate);
    p_MergeRate_Mu->Fill(mu, MergeRate);
    p_SplitRate_Mu->Fill(mu, SplitRate);
    p_FakeRate_Mu->Fill(mu, FakeRate);
    //---


    //---
    // Hard scatter plots.
    // ToDo: Check what these depend on.
    InDetVertexTruthMatchUtils::HardScatterType type = InDetVertexTruthMatchUtils::classifyHardScatter(vertexContainer);
    h_HSCategory->Fill(type);
    h_HSCategory_Mu->Fill(mu,type);
    if (type==0)
        h_HSSelEff->Fill(1);
    else
        h_HSSelEff->Fill(2);
    if (type<3)
        h_HSRecEff->Fill(1);
    else
        h_HSRecEff->Fill(2);

    //if (type==HSSPLIT && splitCount<10) {
        //fillZChain(h_HSzSplits[splitCount++], truthEventContainer->at(0)->truthVertex(0));
        //float Tz = truthEventContainer->at(0)->truthVertex(0)->z(); 
        //std::cout<<"HS z Position: "<<Tz<<std::endl;
        //std::cout<<"Pileup z Positions Close to HS: ";
        //for (int i=0; i<(int)truthPileupEventContainer->size(); i++) {
            //float PUz = truthPileupEventContainer->at(i)->truthVertex(0)->z();
            //if (abs(PUz - Tz) < 10)
                //std::cout<<PUz<<" ";
        //}
        //std::cout<<std::endl;
        //std::cout<<"Reco z Positions Close to HS: ";
        //for(size_t i = 0; i < vertexContainerSize; ++i) {
            //if(xAOD::VxType::NoVtx == vertexContainer[i]->vertexType())  continue;
            //float Vz = vertexContainer[i]->z();
            //if (abs(Vz - Tz) < 10)
                //std::cout<<Vz<<" ";
        //}
        //std::cout<<std::endl;
    //}

    // Truth hard scatter
    // Assuming hard scatter vertex is just the first one
    auto trueHS = truthEventContainer->at(0)->truthVertex(0);
    //auto trueHS = truthEventContainer->at(0)->signalProcessVertex();
    h_zHSRes->Fill(bestHSMatch->z() - trueHS->z());
    h_xHSRes->Fill(bestHSMatch->x() - trueHS->x());
    h_yHSRes->Fill(bestHSMatch->y() - trueHS->y());
    h_HSRecox->Fill(bestHSMatch->x());
    h_HSRecoy->Fill(bestHSMatch->y());
    h_HSRecoz->Fill(bestHSMatch->z());
    h_HSTruex->Fill(trueHS->x());
    h_HSTruey->Fill(trueHS->y());
    h_HSTruez->Fill(trueHS->z());
    
    h_HSnTracks->Fill(InDetVertexTruthMatchUtils::nTracks(bestHSMatch));
    for (auto pt:InDetVertexTruthMatchUtils::TrackPts(bestHSMatch)) {
        h_HSTrackPts->Fill(pt);
    }
    h_HSSumPtTracks->Fill(InDetVertexTruthMatchUtils::SumPtTracks(bestHSMatch));
    h_HSSumPt2Tracks->Fill(InDetVertexTruthMatchUtils::SumPt2Tracks(bestHSMatch));
    
    h_HSnTracksMuons->Fill(InDetVertexTruthMatchUtils::nTracks(bestHSMatch,1));
    for (auto pt:InDetVertexTruthMatchUtils::TrackPts(bestHSMatch,1)) {
        h_HSTrackPtsMuons->Fill(pt);
    }
    h_HSSumPtTracksMuons->Fill(InDetVertexTruthMatchUtils::SumPtTracks(bestHSMatch,1));
    h_HSSumPt2TracksMuons->Fill(InDetVertexTruthMatchUtils::SumPt2Tracks(bestHSMatch,1));

    h_HSnTracksNonMuons->Fill(InDetVertexTruthMatchUtils::nTracks(bestHSMatch,2));
    for (auto pt:InDetVertexTruthMatchUtils::TrackPts(bestHSMatch,2)) {
        h_HSTrackPtsNonMuons->Fill(pt);
    }
    h_HSSumPtTracksNonMuons->Fill(InDetVertexTruthMatchUtils::SumPtTracks(bestHSMatch,2));
    h_HSSumPt2TracksNonMuons->Fill(InDetVertexTruthMatchUtils::SumPt2Tracks(bestHSMatch,2));

    // Truth events
    int n_truthParticles=0;
    int n_truthVertices=0;
    int n_truthPileupParticles=0;
    int n_truthPileupVertices=0;
    std::vector<std::vector<double>> truthVectorPos = {};

    h_nTruthEvents->Fill(truthEventContainer->size());
    for (int i=0; i<(int)truthEventContainer->size(); i++) {
        auto event = truthEventContainer->at(i);
        n_truthParticles+=event->nTruthParticles();
        n_truthVertices+=event->nTruthVertices();
        truthVectorPos.push_back({event->truthVertex(0)->x(), event->truthVertex(0)->y(), event->truthVertex(0)->z()});
    }
    h_nTruthParticles->Fill(n_truthParticles);
    h_nTruthVertices->Fill(n_truthVertices);
        
    if (truthPileupEventContainer != NULL) {
        h_nTruthPileupEvents->Fill(truthPileupEventContainer->size());
        for (int i=0; i<(int)truthPileupEventContainer->size(); i++) {
            auto event = truthPileupEventContainer->at(i);
            n_truthPileupParticles+=event->nTruthParticles();
            n_truthPileupVertices+=event->nTruthVertices();
            //First vertex for each pileup event
            h_TruthPileupx->Fill(event->truthVertex(0)->x());
            h_TruthPileupy->Fill(event->truthVertex(0)->y());
            h_TruthPileupz->Fill(event->truthVertex(0)->z());
            truthVectorPos.push_back({event->truthVertex(0)->x(), event->truthVertex(0)->y(), event->truthVertex(0)->z()});
            for (size_t k=0; k<event->truthVertex(0)->nOutgoingParticles(); k++) {
                h_TestHist2->Fill(event->truthVertex(0)->outgoingParticle(k)->status());
            }
            //for (size_t j=0; j<event->nTruthVertices(); j++) {
                //h_TestHist1->Fill(event->truthVertex(j)->nOutgoingParticles());
                //for (size_t k=0; k<event->truthVertex(j)->nOutgoingParticles(); k++) {
                    //h_TestHist2->Fill(event->truthVertex(j)->outgoingParticle(k)->status());
                    //if (event->truthVertex(j)->outgoingParticle(k)->hasDecayVtx() == false)
                        //h_TestHist3->Fill(i);
                //}
            //}
        }
        h_nTruthPileupParticles->Fill(n_truthPileupParticles);
        h_nTruthPileupVertices->Fill(n_truthPileupVertices);
        p_Vtx_Reco_True->Fill(truthPileupEventContainer->size()+truthEventContainer->size(),nVtx); 
    }

    //if (m_entryNumber<=11) {
        //std::cout<<"Event "<<m_entryNumber-1<<std::endl;
        //std::cout<<"Truth Vertices"<<std::endl;
        //for (int i=0; i<(int)truthVectorPos.size(); i++) {
            //std::cout<<truthVectorPos[i][0]<<"\t"<<truthVectorPos[i][1]<<"\t"<<truthVectorPos[i][2]<<std::endl;
        //}
        //std::cout<<"Reco Vertices"<<std::endl;
        //for (int i=0; i<(int)recoVectorPos.size(); i++) {
            //std::cout<<recoVectorPos[i][0]<<"\t"<<recoVectorPos[i][1]<<"\t"<<recoVectorPos[i][2]<<std::endl;
        //}
    //}

    return 0;
}
