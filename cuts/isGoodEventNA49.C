#ifndef IsGoodEvent_H
#define IsGoodEvent_H 1

#include "isGoodTrackNA49.C"

Double_t fVertexCut[3][2] = { {-0.5, 0.5}, {-0.5, 0.5}, {-581.6, -580.6} };

Bool_t IsGoodVertex(const DataTreeEvent& event);
Int_t GetNGoodTracks(const DataTreeEvent& event);

Bool_t isGoodEvent(const DataTreeEvent& event)
{
    if ( !IsGoodVertex(event) ) return false;
    if ( event.GetNTracks() <= 10 ) return false;
//    if ( GetNGoodTracks(event) < 10 ) return false;

    return true;
}


Int_t GetNGoodTracks(const DataTreeEvent& event)
{
    Int_t Msel{0};
    DataTreeTrack *track;

    for (int i=0; i<event.GetNTracks(); i++)
    {
        track = event.GetTrack(i);
        if ( ! isGoodTrack(*track) ) continue;
        Msel++;
    }
    return Msel;
}

Bool_t IsGoodVertex(const DataTreeEvent& event){

    Double_t VtxChi2 = event.GetVertexQuality(EnumVertexType::kReconstructedVertex);

    if ( VtxChi2 <= 0.5 || VtxChi2 > 1. ) return false;
    Double_t vtx[3];
    for (Int_t iXyz=0; iXyz<3; ++iXyz)
    {
        vtx[iXyz] = event.GetVertexPositionComponent(iXyz, EnumVertexType::kReconstructedVertex);
        if ( vtx[iXyz] < fVertexCut[iXyz][0] || vtx[iXyz] > fVertexCut[iXyz][1] ) return false;
    }
    return true;
}

#endif

