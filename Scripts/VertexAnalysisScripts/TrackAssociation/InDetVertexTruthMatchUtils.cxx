#include "InDetTruthVertexValidation/InDetVertexTruthMatchUtils.h"

namespace InDetVertexTruthMatchUtils {

    namespace { 
        bool isHardScatterEvent( const ElementLink<xAOD::TruthEventBaseContainer> evlink ) {
            //good link of type "TruthEvent" (not truthpileupevent) and the first one in the collection
            return ( evlink.isValid() && (*evlink)->type() == xAOD::Type::TruthEvent && evlink.index() == 0 );
        }
    }

    //find highest weight match to the hard scatter interaction
    //in the case of splitting user can take care to check this is really "best"
    // --> example:
    // vertex 0 is 90% hard scatter with many tracks, and 10% another vertex
    // vertex 1 is 100% hard scatter with few tracks.  
    // this algorithm will pick vertex 1, but user may want to use vertex 0 (accessible from splitting link decoration)
    const xAOD::Vertex * bestHardScatterMatch( const xAOD::VertexContainer & vxContainer ) {
        //accessors for decorations
        xAOD::Vertex::Decorator<std::vector<VertexTruthMatchInfo> > matchInfoDecor("TruthEventMatchingInfos");

        std::vector<std::pair<const xAOD::Vertex*, size_t> > allMatches = hardScatterMatches( vxContainer );

        //look for the highest weight
        float bestw = 0.;
        const xAOD::Vertex * best = 0;

        for( auto it : allMatches ) {
            std::vector<VertexTruthMatchInfo> & info = matchInfoDecor( *(it.first) );
            //go to the index of the HS match in the info vector, and check the weight
            if( info[ it.second ].second > bestw ) {
                bestw = info[ it.second ].second;
                best = it.first;
            }
        }

        //if didn't find any matches will return 0
        return best;
    }

    //Checkpoint - print all info for tracks associated to all vertices
    void printTrackVertexAssociations( const xAOD::VertexContainer & vxContainer ) {
        gROOT->ProcessLine(".! ls TrackAssociation/ -1 | wc -l > TrackAssociation/count.txt ");
        std::ifstream count;
        std::ofstream myfile;
        count.open ("TrackAssociation/count.txt");
        int nFiles = 0;
        count >> nFiles;
        //std::cout<<nFiles<<std::endl;
        count.close();
        myfile.open ("TrackAssociation/TrackAssociation_"+std::to_string(nFiles-1)+".txt");
        //myfile<<"New Event"<<std::endl;
        myfile<<"vtxX vtxY vtxZ d0 z0 phi eta qOverP pT truVtxX truVtxY truVtxZ trkWeight correctVtx d0sig z0sig phi0sig thetasig qOverPsig is_HS"<<std::endl;
        auto HSvtx = bestHardScatterMatch(vxContainer);
        for( auto vtx : vxContainer ) {
            //Print percent of correctly associated tracks
            xAOD::Vertex::ConstAccessor<xAOD::Vertex::TrackParticleLinks_t> trkAcc("trackParticleLinks");
            xAOD::Vertex::ConstAccessor<std::vector<float> > weightAcc("trackWeights");
            //Make list of all truth vertices attached to particle links from this reco vertex, and count how many tracks link there
            std::map<const xAOD::Vertex*,int> vertices;
            if (vtx==HSvtx)
                myfile<<"HS Vertex\t";
            else
                myfile<<"New Vertex\t";
            myfile<<vtx->x()<<"\t";
            myfile<<vtx->y()<<"\t";
            myfile<<vtx->z()<<std::endl;
            if(trkAcc.isAvailable(*vtx) && weightAcc.isAvailable(*vtx) ) {
                const xAOD::Vertex::TrackParticleLinks_t & trkParts = trkAcc( *vtx );
                const std::vector<float> & trkWeights = weightAcc( *vtx );
                int foundTracks = trkParts.size();
                for (int i=0; i<foundTracks; i++) {
                    //xAOD::TrackParticle_v1 type
                    auto trackParticle = trkParts[i];
                    auto trackWeight = trkWeights[i];
                    //Print track parameters in Perigee coordinates
                    const xAOD::Vertex* newVert = (*trackParticle)->vertex();
                    if (newVert == 0) continue;
                    myfile<<(*trackParticle)->d0()<<"\t";
                    myfile<<fabs((*trackParticle)->z0() + (*trackParticle)->vz() - (*vtx)->z())<<"\t";
                    myfile<<(*trackParticle)->phi0()<<"\t";
                    myfile<<(*trackParticle)->eta()<<"\t";
                    myfile<<(*trackParticle)->qOverP()<<"\t";
                    myfile<<(*trackParticle)->pt()<<"\t";
                    //Find truth particle
                    ElementLink< xAOD::TruthParticleContainer > truthLink = (*trackParticle)->auxdata<ElementLink< xAOD::TruthParticleContainer > >("truthParticleLink");
                    if (truthLink==0) {
                        //std::cout<<"Checkpoint fail"<<std::endl;
                        myfile<<"-999\t-999\t-999\t0\t0"<<std::endl;
                        continue;
                    }
                    //myfile<<(*truthLink)->eta()<<std::endl;
                    myfile<<(*((*truthLink)->auxdata<ElementLink<xAOD::TruthEventBaseContainer> >("TruthEventLink")))->truthVertex(0)->x()<<"\t";
                    myfile<<(*((*truthLink)->auxdata<ElementLink<xAOD::TruthEventBaseContainer> >("TruthEventLink")))->truthVertex(0)->y()<<"\t";
                    myfile<<(*((*truthLink)->auxdata<ElementLink<xAOD::TruthEventBaseContainer> >("TruthEventLink")))->truthVertex(0)->z()<<"\t";
                    myfile<<trackWeight<<"\t";
                    myfile<<isCorrectTrack(trackParticle, vtx)<<std::endl;
                    //Count how many tracks go to each truth vertex
                    if (vertices.find(newVert) == vertices.end()) vertices[newVert]=1;
                    else vertices[newVert]++;
					float d0_significance = fabs((*trackParticle)->d0()) / sqrt((*trackParticle)->definingParametersCovMatrix()(0,0));
					float z0_significance = fabs((*trackParticle)->z0()) / sqrt((*trackParticle)->definingParametersCovMatrix()(1,1));
					float phi0_significance = fabs((*trackParticle)->phi0()) / sqrt((*trackParticle)->definingParametersCovMatrix()(2,2));
					float theta_significance = fabs((*trackParticle)->theta()) / sqrt((*trackParticle)->definingParametersCovMatrix()(3,3));
					float qOverP_significance = fabs((*trackParticle)->qOverP()) / sqrt((*trackParticle)->definingParametersCovMatrix()(4,4));
                    myfile<<d0_significance<<"\t";
                    myfile<<z0_significance<<"\t";
                    myfile<<phi0_significance<<"\t";
                    myfile<<theta_significance<<"\t";
                    myfile<<qOverP_significance<<"\t";
					if (vtx==HSvtx)
						myfile<<"1\t";
					else
						myfile<<"0\t";
                }
            }
            //for (auto iter=vertices.begin(); iter!=vertices.end(); ++iter) {
                //myfile << "Key: " << iter->first->z() << " Value:" << iter->second << std::endl;
            //}
            ////Using common mode truth vertex matching - truth vert with most tracks associated is taken as correct one - print z position of truth common vertex
            //int correctTracks=0;
            //const xAOD::Vertex_v1* truthVtx;
            //for (auto it=vertices.begin(); it!=vertices.end(); ++it) {
                //if (it->second > correctTracks) {
                    //correctTracks = it->second;
                    //truthVtx = it->first;
                //}
            //}
            //myfile<<vtx->z()<<std::endl;
            //myfile<<truthVtx->z()<<std::endl;
        }
        myfile<<std::endl;
        myfile.close();
    }

    //number of tracks associated to a vertex
    int nTracks( const xAOD::Vertex* vtx, int muonOption ) {
        int foundTracks=0;
        xAOD::Vertex::ConstAccessor<xAOD::Vertex::TrackParticleLinks_t> trkAcc("trackParticleLinks");
        if(trkAcc.isAvailable(*vtx)) {
            const xAOD::Vertex::TrackParticleLinks_t & trkParts = trkAcc( *vtx );
            foundTracks = trkParts.size();
        }
        return foundTracks;
    }

    //percent of tracks correctly associated to a vertex - using common (mode) truth vertex origin matching
    float percentCorrectTracks( const xAOD::Vertex* vtx) {
        int foundTracks=1;
        xAOD::Vertex::ConstAccessor<xAOD::Vertex::TrackParticleLinks_t> trkAcc("trackParticleLinks");
        //Make list of all (reco?) vertices attached to particle links from this reco vertex, and count how many tracks link there
        std::map<const xAOD::TruthVertex*,int> vertices;
        if(trkAcc.isAvailable(*vtx)) {
            const xAOD::Vertex::TrackParticleLinks_t & trkParts = trkAcc( *vtx );
            foundTracks = trkParts.size();
            for (int i=0; i<foundTracks; i++) {
                auto trackParticle = trkParts[i];
                ElementLink< xAOD::TruthParticleContainer > truthLink = (*trackParticle)->auxdata<ElementLink< xAOD::TruthParticleContainer > >("truthParticleLink");
                if (truthLink==0) continue;
                const xAOD::TruthVertex* newVert = (*((*truthLink)->auxdata<ElementLink<xAOD::TruthEventBaseContainer> >("TruthEventLink")))->truthVertex(0);
                if (newVert == 0) continue;
                if (vertices.find(newVert) == vertices.end()) vertices[newVert]=1;
                else vertices[newVert]++;
            }
        }
        //Using common mode vertex matching - vert with most tracks associated is taken as correct one
        int correctTracks=0;
        for (auto it=vertices.begin(); it!=vertices.end(); ++it) {
            if (it->second > correctTracks)
                correctTracks = it->second;
        }
        return (float)correctTracks/(float)foundTracks;
    }

    //whether a track is correct
    int isCorrectTrack ( ElementLink<DataVector<xAOD::TrackParticle_v1> > trackParticle, const xAOD::Vertex* vtx) {
        int foundTracks=1;
        xAOD::Vertex::ConstAccessor<xAOD::Vertex::TrackParticleLinks_t> trkAcc("trackParticleLinks");
        //Make list of all (reco?) vertices attached to particle links from this reco vertex, and count how many tracks link there
        std::map<const xAOD::TruthVertex*,int> vertices;
        if(trkAcc.isAvailable(*vtx)) {
            const xAOD::Vertex::TrackParticleLinks_t & trkParts = trkAcc( *vtx );
            foundTracks = trkParts.size();
            for (int i=0; i<foundTracks; i++) {
                auto part = trkParts[i];
                ElementLink< xAOD::TruthParticleContainer > truthLink = (*part)->auxdata<ElementLink< xAOD::TruthParticleContainer > >("truthParticleLink");
                if (truthLink==0) continue;
                const xAOD::TruthVertex* newVert = (*((*truthLink)->auxdata<ElementLink<xAOD::TruthEventBaseContainer> >("TruthEventLink")))->truthVertex(0);
                if (newVert == 0) continue;
                if (vertices.find(newVert) == vertices.end()) vertices[newVert]=1;
                else vertices[newVert]++;
            }
        }
        //Using common mode vertex matching - vert with most tracks associated is taken as correct one
        const xAOD::TruthVertex_v1* correctVertex=0;
        int correctTracks=0;
        for (auto it=vertices.begin(); it!=vertices.end(); ++it) {
            if (it->second > correctTracks)
                correctVertex = it->first;
                correctTracks = it->second;
        }
        ElementLink< xAOD::TruthParticleContainer > truthLink = (*trackParticle)->auxdata<ElementLink< xAOD::TruthParticleContainer > >("truthParticleLink");
        const xAOD::TruthVertex* trueVertex = (*((*truthLink)->auxdata<ElementLink<xAOD::TruthEventBaseContainer> >("TruthEventLink")))->truthVertex(0);
        return (trueVertex==correctVertex);
    }

    //Pt distribution of tracks associated to a vertex
    std::vector<double> TrackPts( const xAOD::Vertex* vtx, int muonOption ) {
        std::vector<double> pts;
        xAOD::Vertex::ConstAccessor<xAOD::Vertex::TrackParticleLinks_t> trkAcc("trackParticleLinks");
        if(trkAcc.isAvailable(*vtx)) {
            const xAOD::Vertex::TrackParticleLinks_t & trkParts = trkAcc( *vtx );
            int nTracks = trkParts.size();
            for (int count=0;count<nTracks;++count)
                pts.push_back((**trkParts[count]).pt()*.001);
        }
        return pts;
    }

    //SupPt of tracks associated to a vertex
    int SumPtTracks( const xAOD::Vertex* vtx, int muonOption ) {
        int sumTracks=0;
        xAOD::Vertex::ConstAccessor<xAOD::Vertex::TrackParticleLinks_t> trkAcc("trackParticleLinks");
        if(trkAcc.isAvailable(*vtx)) {
            const xAOD::Vertex::TrackParticleLinks_t & trkParts = trkAcc( *vtx );
            int nTracks = trkParts.size();
            for (int count=0;count<nTracks;++count)
                sumTracks += (**trkParts[count]).pt()*.001;
        }
        return sumTracks;
    }
    
    //SupPt2 of tracks associated to a vertex
    int SumPt2Tracks( const xAOD::Vertex* vtx, int muonOption ) {
        int sumTracks=0;
        xAOD::Vertex::ConstAccessor<xAOD::Vertex::TrackParticleLinks_t> trkAcc("trackParticleLinks");
        if(trkAcc.isAvailable(*vtx)) {
            const xAOD::Vertex::TrackParticleLinks_t & trkParts = trkAcc( *vtx );
            int nTracks = trkParts.size();
            for (int count=0;count<nTracks;++count)
                sumTracks += std::pow((**trkParts[count]).pt()*.001,2);
        }
        return sumTracks;
    }

    //Find all hard scatter matches. Takes a vertex container and returns a vector full of pairs <vertex, index>, listing all vertices which match HS.
    std::vector<std::pair<const xAOD::Vertex*, size_t> > hardScatterMatches( const xAOD::VertexContainer & vxContainer ) {
        //accessors for decorations
        xAOD::Vertex::Decorator<std::vector<VertexTruthMatchInfo> > matchInfoDecor("TruthEventMatchingInfos");

        //return vector
        std::vector<std::pair<const xAOD::Vertex*, size_t> > result;

        //loop and look
        for( auto vxit : vxContainer ) {
            const std::vector<VertexTruthMatchInfo> & info =  matchInfoDecor( *vxit );
            //info[x].first is apparently an event link. We check that it's a good link to the first truth event.
            for( size_t i=0; i< info.size(); ++i ) {
                if( isHardScatterEvent( info[i].first ) ) {
                    result.push_back( std::make_pair(vxit, i) ); //Check if there is a hard scatter component (of any weight) in the vertex at all. If so, push back (vertex, index), where index is the ranking of HS weight (index 0 = largest weight component).
                    break;
                }
            }

        }
        return result;
    }

    HardScatterType classifyHardScatter( const xAOD::VertexContainer & vxContainer ) {
        //get pairs of (vertices, and their indices) for all hard scatter-matched vertices.
        std::vector<std::pair<const xAOD::Vertex*, size_t> > matches = hardScatterMatches( vxContainer );
        xAOD::Vertex::Decorator<VertexMatchType> matchTypeDecor("VertexMatchType");

        if(  matches.size() == 0 ) {
            return NONE;
        } else if( matches.size() == 1 ) {

            const VertexMatchType & type = matchTypeDecor( *(matches[0].first) );
            //check if the index in the matching info for HS is first, then can assign clean/lowpu based on match/merge
            if( matches[0].second == 0 && type == MATCHED ) { //matches[0].second is the relative contribution of HS. second == 0 means that HS is the largest component. These numbers are calculated via matchInfoDecor.
                return CLEAN;
            } else if ( matches[0].second == 0 && type == MERGED ) {
                return LOWPU;
            } else {
                return HIGHPU;
            }

        } else {
            //now need to check what kind of contribution it has in the other vertices
            int num_main = 0;
            int matchindex = -1;
            //for( auto it : matches ) {
            for (size_t i=0; i<matches.size(); i++) {
                auto it = matches[i];
                if( it.second == 0 ) { // for the current reco vtx, the index of the hard scatter contribution is first
                    num_main++;
                    matchindex = i;
                }
            }
            if(num_main == 0 ) {
                return HIGHPU;
            } else if (num_main == 1 ) {
                const VertexMatchType & type = matchTypeDecor( *(matches[matchindex].first) );
                if( matches[matchindex].second == 0 && type == MATCHED ) {
                    return CLEAN;
                } else if ( matches[matchindex].second == 0 && type == MERGED ) {
                    return LOWPU;
                } else {
                    std::cout<<"This case should be impossible - check truth matching code!"<<std::endl;
                    return HIGHPU;
                }
            } else {
                return HSSPLIT;
            }
        }

        return NONE;
    }

}
