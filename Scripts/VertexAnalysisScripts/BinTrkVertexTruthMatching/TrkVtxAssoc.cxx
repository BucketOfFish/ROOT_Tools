#include <TrkVtxAssocStudy/TrkVtxAssoc.h>

//#define InfoPrimary

// this is needed to distribute the algorithm to the workers
ClassImp(TrkVtxAssoc)

TrkVtxAssoc::TrkVtxAssoc(): associationMethod(""), directoryName(""), description(""), doTrackCut(false), 
  trackCutLevel("TightPrimary"), trackMinPt(-1), trackAbsPdgId(-1), matchMethod("smart"), m_trackSel(0)
{
  Info("TrkVtxAssoc", "---");
}


EL::StatusCode TrkVtxAssoc :: setupJob (EL::Job& job)
{
  Info("setupJob", "---");
  job.useXAOD();

  return EL::StatusCode::SUCCESS;
}


EL::StatusCode TrkVtxAssoc :: histInitialize ()
{
  outputName = "myOutput";
  TFile *outputFile = wk()->getOutputFile(outputName);
  tree = new TTree("tree", "tree");
  tree->SetDirectory( outputFile );
  
  tree->Branch("EventNumber", &EventNumber);
  tree->Branch("RunNumber", &RunNumber);
  tree->Branch("vRAssoc", &vRAssoc);
  tree->Branch("vTAssoc", &vTAssoc);
  tree->Branch("vTAssocJM", &vTAssocJM);
  tree->Branch("vTrackIsFake", &vTrackIsFake);
  tree->Branch("vTRAssoc", &vTRAssoc);
  tree->Branch("vNoTRAssoc", &vNoTRAssoc);
  tree->Branch("vNoTRFAssoc", &vNoTRFAssoc);
  tree->Branch("vIsPrompt", &vIsPrompt);
  tree->Branch("vIsKs", &vIsKs);
  tree->Branch("vIsKsSec", &vIsKsSec);
  tree->Branch("vIsSMeson", &vIsSMeson);
  tree->Branch("vIsSBaryon", &vIsSBaryon);
  tree->Branch("vIsCMeson", &vIsCMeson);
  tree->Branch("vIsCBaryon", &vIsCBaryon);
  tree->Branch("vIsBMeson", &vIsBMeson);
  tree->Branch("vIsBBaryon", &vIsBBaryon);
  tree->Branch("vIsSec", &vIsSec);
  tree->Branch("vIsSecVetoKsSec", &vIsSecVetoKsSec);
  tree->Branch("vpt_track", &vpt_track);
  tree->Branch("vpe_track", &vpe_track);
  tree->Branch("veta_track", &veta_track);
  tree->Branch("vphi_track", &vphi_track);
  tree->Branch("vd0_track", &vd0_track);
  tree->Branch("vd0sig_track", &vd0sig_track);
  tree->Branch("vdzSinTheta_track", &vdzSinTheta_track);
  tree->Branch("vTrackWeight_track", &vTrackWeight_track);
  tree->Branch("vchi2R_track", &vchi2R_track);
  tree->Branch("vchi2RNDF_track", &vchi2RNDF_track);
  tree->Branch("vmuActual_track", &vmuActual_track);
  tree->Branch("vvertexmatchweight_track", &vvertexmatchweight_track);
  tree->Branch("vtruthmatchprob_track", &vtruthmatchprob_track);
  tree->Branch("vtruthLink_track", &vtruthLink_track);
  tree->Branch("vParticleStatus_track", &vParticleStatus_track);
  tree->Branch("vParticleBarcode_track", &vParticleBarcode_track);
  tree->Branch("vParticlePdgId_track", &vParticlePdgId_track);
  tree->Branch("vParentStatus_track", &vParentStatus_track);
  tree->Branch("vParentBarcode_track", &vParentBarcode_track);
  tree->Branch("vParentPdgId_track", &vParentPdgId_track);
  
  Info("histInitialize", "---");
  
  return EL::StatusCode::SUCCESS;
}


EL::StatusCode TrkVtxAssoc :: fileExecute ()
{
  return EL::StatusCode::SUCCESS;
}


EL::StatusCode TrkVtxAssoc :: changeInput (bool firstFile)
{
  (void)firstFile;

  Info("changeInput", "filename: %s", wk()->inputFile()->GetName());
  return EL::StatusCode::SUCCESS;
}


EL::StatusCode TrkVtxAssoc :: initialize ()
{
  Info("initialize", "--");
  
  std::string prefix{""};
  if (directoryName != "") {
    prefix = directoryName + "_";
  }
  
  //auto tool = new CP::MuonTrackVertexAssociationTool("Muon");
  //auto tool = new CP::ElectronTrackVertexAssociationTool("Electron");
  auto tool = new CP::LooseTrackVertexAssociationTool("Loose");
  //auto tool = new CP::TightTrackVertexAssociationTool("Tight");
  //auto tool = new CP::BaseTrackVertexAssociationTool("Base");
  CHECK_EXC(tool->setProperty("dzSinTheta_cut", 10.0));
  CHECK_EXC(tool->setProperty("d0_cut", 10.0));
  //CHECK_EXC(tool->setProperty("d0sig_cut", 10.0));
  CHECK_EXC(tool->initialize());
  // todo: put in a vector etc so we can test multiple tools
  m_tvatool = tool;
  
  m_matchTool = new InDetVertexTruthMatchTool(prefix+"MatchTool");
  // m_matchTool->msg().setLevel(MSG::DEBUG);
  CHECK_EXC( m_matchTool->setProperty("trackMatchProb", 0.5) );
  CHECK_EXC( m_matchTool->setProperty("vertexMatchWeight", 0.7) );
  CHECK_EXC( m_matchTool->initialize() );
  
  // Todo: it would be nice if we could set this from the steering
  // script, but that only seems to be possible in athena
  if (doTrackCut) {
    m_trackSel = new InDet::InDetTrackSelectionTool(prefix+"TrackSelection");
    CHECK_EXC( m_trackSel->setProperty("CutLevel", trackCutLevel) );
    CHECK_EXC( m_trackSel->setProperty("minPt", trackMinPt) );
    CHECK_EXC( m_trackSel->initialize() );
  }
  
  m_tracktruthhelper = new TrackTruthHelpers();
  
  m_event = wk()->xaodEvent();
  
  m_eventCounter = 0;
  m_HSeventCounter = 0;
  m_PUeventCounter = 0;
  
#ifdef InfoPrimary
  Info(" ", " ");
  Info("Definition  ", "prompt: prompt particles (barcode<200e3)");
  Info("Definition  ", "Ks: K short pdgId=310 (barcode<200e3)");
  Info("Definition  ", "KsSec: K short pdgId=310 (barcode>200e3)");
  Info("Definition  ", "s.meson: strange meson (barcode<200e3)");
  Info("Definition  ", "s.baryon: strange baryon (barcode<200e3)");
  Info("Definition  ", "c.meson: charm meson (barcode<200e3)");
  Info("Definition  ", "c.baryon: charm baryon (barcode<200e3)");
  Info("Definition  ", "b.meson: beauty meson (barcode<200e3)");
  Info("Definition  ", "b.baryon: beauty baryon (barcode<200e3)");
  Info("Definition  ", "Sec Part: secondary particle (barcode>200e3 && veto KsSec)");
  Info("Definition  ", "truth !Parent: reco track linked to truth particle which has ProdVtx but has no truth parent");
  Info("Definition  ", "truth !ProdV: reco track linked to truth particle which has no ProdVtx");
  Info("Definition  ", "!truth: reco track not linked to truth particle");
  Info("Definition  ", "prompt, truth !Parent and truth !ProdV are all counted as prompt particles");
  Info(" ", " ");
  Info("track/particle type ", "truthMatchProbability, nstatus, nbarcode, npdgId, truthparentstatus, truthparentbarcode, nparentpdgId");
#endif
  
  return EL::StatusCode::SUCCESS;
}


EL::StatusCode TrkVtxAssoc :: execute ()
{
  const bool debug = false;
  
  if( (m_eventCounter % 1000) ==0 ) Info("execute()", "Event number = %i", m_eventCounter );
  m_eventCounter++;
  
  const xAOD::EventInfo *event{0};
  CHECK_EXC(m_event->retrieve(event, "EventInfo"));
  if (debug) {
    Info("execute", "-----------------------------------------");
    Info("execute", "Run %d, event number %llu", event->runNumber(), event->eventNumber());
  }
  
  EventNumber = event->eventNumber();
  RunNumber = event->runNumber();
  
  const xAOD::TrackParticleContainer *tracks{0};
  CHECK_EXC(m_event->retrieve(tracks, "InDetTrackParticles"));
  
  const xAOD::VertexContainer *vertices;
  CHECK_EXC(m_event->retrieve(vertices, "PrimaryVertices"));
  
  const xAOD::TruthEventContainer *truthEvents{0};
  CHECK_EXC( m_event->retrieve(truthEvents, "TruthEvents") );
  if (debug) {
    Info("execute", "%lu truth events", truthEvents->size());
  }
  
  CHECK_EXC( m_matchTool->matchVertices(*vertices) );
  
  std::vector<const xAOD::TrackParticle *> goodTracks;
  
  // for the fake rate calculation, we want to let the tool under test
  // try to match fake tracks to vertices
  for (const auto trk : *tracks) {
    // does the track pass the cut?
    if (m_trackSel && !m_trackSel->accept(trk)) continue;
    goodTracks.push_back(trk);
  } // loop over all tracks
  
  // accessor for the vertex matching type
  xAOD::Vertex::Decorator<InDetVertexTruthMatchUtils::VertexMatchType> getMatchType("VertexMatchType");
  xAOD::Vertex::Decorator<std::vector<InDetVertexTruthMatchUtils::VertexTruthMatchInfo>> getMatchInfo("TruthEventMatchingInfos");
  
  // accessor for the track's truth match probability
  xAOD::TrackParticle::ConstAccessor<float> trk_truthProbAcc("truthMatchProbability");
  
  // accessor for the vertex's track particle links
  xAOD::Vertex::ConstAccessor<xAOD::Vertex::TrackParticleLinks_t> trkAcc("trackParticleLinks");
  
  vRAssoc.clear();
  vTAssoc.clear();
  vTAssocJM.clear();
  vTrackIsFake.clear();
  vTRAssoc.clear();
  vNoTRAssoc.clear();
  vNoTRFAssoc.clear();
  vIsPrompt.clear();
  vIsKs.clear();
  vIsKsSec.clear();
  vIsSMeson.clear();
  vIsSBaryon.clear();
  vIsCMeson.clear();
  vIsCBaryon.clear();
  vIsBMeson.clear();
  vIsBBaryon.clear();
  vIsSec.clear();
  vIsSecVetoKsSec.clear();
  vpt_track.clear();
  vpe_track.clear();
  veta_track.clear();
  vphi_track.clear();
  vd0_track.clear();
  vd0sig_track.clear();
  vdzSinTheta_track.clear();
  vTrackWeight_track.clear();
  vchi2R_track.clear();
  vchi2RNDF_track.clear();
  vmuActual_track.clear();
  vvertexmatchweight_track.clear();
  vtruthmatchprob_track.clear();
  vtruthLink_track.clear();
  vParticleStatus_track.clear();
  vParticleBarcode_track.clear();
  vParticlePdgId_track.clear();
  vParentStatus_track.clear();
  vParentBarcode_track.clear();
  vParentPdgId_track.clear();
  
  // outer loop over all vertices
  // we could also iterate over InDetVertexTruthMatchUtils::hardScatterMatches?
  const xAOD::Vertex *recoVertex = nullptr;
  recoVertex = InDetVertexTruthMatchUtils::bestHardScatterMatch(*vertices);
  
  if (recoVertex) {
    auto matchType = getMatchType(*recoVertex);
    
    const xAOD::TruthVertex *tvMatched = nullptr;
    double vertexMatchWeight = 0.;
    
    // changed this to allow fake vertices
    using InDetVertexTruthMatchUtils::VertexMatchType;
    
    // ignore dummy vertices
    //if (matchType == VertexMatchType::DUMMY) continue;
    if (matchType != VertexMatchType::DUMMY) {
      
      auto infos = getMatchInfo(*recoVertex);
      // only consider the dominant contribution, i.e. the first infopair
      const auto &infopair = *begin(infos);
      
      auto link = infopair.first;
      float weight = infopair.second;
      
      const xAOD::TruthEvent *truthHSEvent = nullptr;
      const xAOD::TruthPileupEvent *truthPUEvent = nullptr;
      if (link.isValid()) {
	if ((*link)->type() == xAOD::Type::TruthEvent) {
	  //const xAOD::TruthEvent* truthEvent = dynamic_cast<const xAOD::TruthEvent *>(*link);
	  truthHSEvent = dynamic_cast<const xAOD::TruthEvent *>(*link);
	  tvMatched = truthHSEvent->truthVertex(0);
	  vertexMatchWeight = weight;
	  m_HSeventCounter ++;
	} else if ((*link)->type() == xAOD::Type::TruthPileupEvent) {
	  //const xAOD::TruthPileupEvent* truthPileupEvent = dynamic_cast<const xAOD::TruthPileupEvent *>(*link);
	  truthPUEvent = dynamic_cast<const xAOD::TruthPileupEvent *>(*link);
	  tvMatched = truthPUEvent->truthVertex(0);
	  vertexMatchWeight = weight;
	  m_PUeventCounter ++;
	  Info("Opps!", "Pileup truth event!");
	} else {
	  Info("Opps!!", "the main contribution is from fakes!");
	}
      }   
      
      //// Interested in Truth Hard Scatter Event 
      //if (truthHSEvent) {
	
	//// Inner Loop Over All Tracks
	for (const auto trk : goodTracks) {
	  
	  // good T-V match or not?
	  bool goodTruthAssoc = false;
	  bool goodTruthAssocJM = false;
	  // if not good T-V match: is the track fake?
	  
	  // This should give THE matched vertex for a given track
	  auto vxLink = m_tvatool->getUniqueMatchVertexLink(*trk, *vertices);
	  // T-V matched by the tool or not?
	  bool recoAssoc = vxLink.isValid() && ((*vxLink) == recoVertex);
	  
	  const xAOD::TruthParticle *truthParticle = m_tracktruthhelper->truthParticle(trk);
	  //const xAOD::TruthVertex *tvtrackParticle = nullptr;
	  
	  ElementLink< xAOD::TruthParticleContainer > truthLink = trk->auxdata<ElementLink< xAOD::TruthParticleContainer >>("truthParticleLink");
	  
	  if (truthLink.isValid()) {
	    ElementLink<DataVector<xAOD::TruthEventBase_v1>> truthPEvent = (*truthLink)->auxdata<ElementLink<xAOD::TruthEventBaseContainer>>("TruthEventLink");
	    if (truthHSEvent == *truthPEvent) goodTruthAssoc = true;
	    //tvtrackParticle = (*truthPEvent)->truthVertex(0);
	  }
	  
	  bool trackIsFake = m_tracktruthhelper->isFake(trk);
	  bool IsSec = m_tracktruthhelper->isSecondary(trk);
	  
	  auto tvFromTruthTrack = truthParticle ? truthParticle->prodVtx() : nullptr;
	  
	  // Check if the truth vertex from the truth track
	  // equals the truth vertex from the reco vertex.
	  // If that is true, we have a truth association.
	  if (tvFromTruthTrack && tvMatched) {
	    if (tvFromTruthTrack->x() == tvMatched->x() &&
		tvFromTruthTrack->y() == tvMatched->y() &&
		tvFromTruthTrack->z() == tvMatched->z()) {
	      goodTruthAssocJM = true;
	    }
	  }
	  
	  float truthMatchProb = trk_truthProbAcc(*trk);
	  
	  int nparticlestatus = -1;
	  int nparticlebarcode = -1;
	  int nparticlepdgId = 0;
	  int nparentstatus = -1;
	  int nparentbarcode = -1;
	  int nparentpdgId = 0;
	  int nIsPrompt = 0;
	  int nIsKs = 0;
	  int nIsKsSec = 0;
	  int nIsSMeson = 0;
	  int nIsSBaryon = 0;
	  int nIsCMeson = 0;
	  int nIsCBaryon = 0;
	  int nIsBMeson = 0;
	  int nIsBBaryon = 0;
	  int nIsSecVetoKsSec = 0;
	  
	  if (truthParticle) {
	    //if (truthLink.isValid()) {
	    nparticlestatus = truthParticle->status();
	    nparticlebarcode = truthParticle->barcode();
	    nparticlepdgId = truthParticle->pdgId();
	    
	    const xAOD::TruthParticle *truthParent = nullptr;
	    bool hasProdV = truthParticle->hasProdVtx();
	    if (nparticlestatus == 1 && nparticlebarcode > 0 && nparticlebarcode <= 200000 && !truthParticle->isNeutral()) {
	      if (hasProdV) {
		truthParent = truthParticle->parent(0);
		//// Separate out long-lived resonances from primary particles
		if (truthParent) {
		  nparentstatus = truthParent->status();
		  nparentbarcode = truthParent->barcode();
		  nparentpdgId = truthParent->pdgId();
		  if (fabs(nparentpdgId) == 310) {
		    nIsKs = 1;
		  } else if (truthParent->isStrangeMeson()) {
		    nIsSMeson = 1;
		  } else if (truthParent->isStrangeBaryon()) {
		    nIsSBaryon = 1;
		  } else if (truthParent->isCharmMeson()) {
		    nIsCMeson = 1;
		  } else if (truthParent->isCharmBaryon()) {
		    nIsCBaryon = 1;
		  } else if (truthParent->isBottomMeson()) {
		    nIsBMeson = 1;
		  } else if (truthParent->isBottomBaryon()) {
		    nIsBBaryon = 1;
		  } else { //// Prompt particles
		    nIsPrompt = 1;
		  }
		} else {
		  nIsPrompt = 1;
		}
	      } else {
		nIsPrompt = 1;
	      }
	    }
	    
	    //// Secondary particles
	    if (IsSec) {
	      if (hasProdV) {
		truthParent = truthParticle->parent(0);
		if (truthParent) {
		  if (truthParent->pdgId() == 310) {
		    nIsKsSec = 1;
		  } else {
		    nIsSecVetoKsSec = 1;
		  }
		} else {
		  nIsSecVetoKsSec = 1;
		}
	      } else {
		nIsSecVetoKsSec = 1;
	      }
	    }
	    
	  }
	  
	  float vx_z0 = recoVertex->z();
	  float trk_z0 = trk->z0();
	  float beamspot_z0 = trk->vz();
	  float theta = trk->theta();
	  double d0sig = xAOD::TrackingHelpers::d0significance(trk, event->beamPosSigmaX(), event->beamPosSigmaY(),event->beamPosSigmaXY());
	  double dzSinTheta = (trk_z0 - vx_z0 + beamspot_z0) * sin(theta);
	  uint8_t nTRTHits{0};
	  uint8_t nSCTHits{0};
	  uint8_t nPixelHits{0};
	  if (!trk->summaryValue(nTRTHits, xAOD::numberOfTRTHits)) {
	    Info("execute", "Warning, could not get number of TRT hits");
	  }
	  if (!trk->summaryValue(nSCTHits, xAOD::numberOfSCTHits)) {
	    Info("execute", "Warning, could not get number of SCT hits");
	  }
	  if (!trk->summaryValue(nPixelHits, xAOD::numberOfPixelHits)) {
	    Info("execute", "Warning, could not get number of Pixel hits");
	  }
	  float muActual = event->actualInteractionsPerCrossing();
	  
	  float trackWeight = 0;
	  for (size_t i = 0; i < recoVertex->nTrackParticles(); i++) {
	    if (recoVertex->trackParticle(i) == trk) {
	      // found
	      trackWeight = recoVertex->trackWeight(i);
	      break;
	    }
	  }
	  
	  if (recoAssoc) {
	    vRAssoc.push_back(1);
	  } else {
	    vRAssoc.push_back(0);
	  }
	  if (goodTruthAssoc) {
	    vTAssoc.push_back(1);
	  } else {
	    vTAssoc.push_back(0);
	  }
	  if (goodTruthAssocJM) {
	    vTAssocJM.push_back(1);
	  } else {
	    vTAssocJM.push_back(0);
	  }
	  if (recoAssoc && goodTruthAssoc) {
	    vTRAssoc.push_back(1);
	  } else {
	    vTRAssoc.push_back(0);
	  }
	  if (trackIsFake) {
	    vTrackIsFake.push_back(1);
	  } else {
	    vTrackIsFake.push_back(0);
	  }
	  if (truthLink.isValid()) {
	    vtruthLink_track.push_back(1);
	  } else {
	    vtruthLink_track.push_back(0);
	  }
	  if (recoAssoc && !goodTruthAssoc && !trackIsFake) {
	    vNoTRAssoc.push_back(1);
	  } else {
	    vNoTRAssoc.push_back(0);
	  }
	  if (recoAssoc && !goodTruthAssoc && trackIsFake) {
	    vNoTRFAssoc.push_back(1);
	  } else {
	    vNoTRFAssoc.push_back(0);
	  }
	  if (IsSec) {
	    vIsSec.push_back(1);
	  } else {
	    vIsSec.push_back(0);
	  }
	  
	  vIsPrompt.push_back(nIsPrompt);
	  vIsKs.push_back(nIsKs);
	  vIsKsSec.push_back(nIsKsSec);
	  vIsSMeson.push_back(nIsSMeson);
	  vIsSBaryon.push_back(nIsSBaryon);
	  vIsCMeson.push_back(nIsCMeson);
	  vIsCBaryon.push_back(nIsCBaryon);
	  vIsBMeson.push_back(nIsBMeson);
	  vIsBBaryon.push_back(nIsBBaryon);
	  vIsSecVetoKsSec.push_back(nIsSecVetoKsSec);
	  vpt_track.push_back(trk->pt() / 1000.);
	  vpe_track.push_back(trk->e() / 1000.);
	  veta_track.push_back(trk->eta());
	  vphi_track.push_back(trk->phi());
	  vd0_track.push_back(trk->d0());
	  vd0sig_track.push_back(d0sig);
	  vdzSinTheta_track.push_back(dzSinTheta);
	  vchi2R_track.push_back(trk->chiSquared());
	  vchi2RNDF_track.push_back(trk->chiSquared() / trk->numberDoF());
	  vTrackWeight_track.push_back(trackWeight);
	  vmuActual_track.push_back(muActual);
	  vvertexmatchweight_track.push_back(vertexMatchWeight);
	  vtruthmatchprob_track.push_back(truthMatchProb);
	  vParticleStatus_track.push_back(nparticlestatus);
	  vParticleBarcode_track.push_back(nparticlebarcode);
	  vParticlePdgId_track.push_back(nparticlepdgId);
	  vParentStatus_track.push_back(nparentstatus);
	  vParentBarcode_track.push_back(nparentbarcode);
	  vParentPdgId_track.push_back(nparentpdgId);
	  
	} // Loop Over All Reco Tracks
	//} // Truth Hard Scatter Event
    } // Ignore Dummy Vertices
  } // bestHardScaterMatched Primary Reco Vertex
  
  //          goodTruthAssoc  trackIsFake
  // case 1:  true            false
  // case 2:  false           false
  // case 3:  false           true
  
  tree->Fill();
  
  return EL::StatusCode::SUCCESS;
}


EL::StatusCode TrkVtxAssoc :: postExecute ()
{
  return EL::StatusCode::SUCCESS;
}


EL::StatusCode TrkVtxAssoc :: finalize ()
{
  Info("finalize() ", "m_eventCounter = %i", m_eventCounter);
  Info("finalize() ", "m_HSeventCounter = %i", m_HSeventCounter);
  Info("finalize() ", "m_PUeventCounter = %i", m_PUeventCounter);
  return EL::StatusCode::SUCCESS;
}


EL::StatusCode TrkVtxAssoc :: histFinalize ()
{
  return EL::StatusCode::SUCCESS;
}
