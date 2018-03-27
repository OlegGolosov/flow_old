#include "isGoodEvent.h"

namespace Cuts{

int fittedVertexID = EnumVertexType::kReconstructedVertex;

Float_t energy;

const double bpd1_cut_13[2][2] =  { {-0.5, 0.3}, {-0.7, 1.1} };  // { {x_low, x_high}, ... }
const double bpd2_cut_13[2][2] =  { {-0.7, -0.1}, {-0.4, 0.3} };  // { {x_low, x_high}, ... }
const double bpd3_cut_13[2][2] =  { {-1.05, 0.35}, {-0.55, 0.05} };  // { {x_low, x_high}, ... }

const double bpd1_cut_30[2][2] = { { -0.4, 0.0}, {-0.6,  0.8} };
const double bpd2_cut_30[2][2] = { { -0.2, 0.1}, {-0.3,  0.3} };
const double bpd3_cut_30[2][2] = { { -0.34, 0.22}, {-0.35,  0.05} };

const double vertex_cut_10[3][2] = { {-1, 1.}, {-1, 1}, {-1, 1.} };
const double vertex_cut_13[3][2] = { {-1.1, 0.0}, {-0.8, 0.4}, {-594., -590.} };
const double vertex_cut_30[3][2] = { {-0.35, 0.3}, {-0.37, 0.08}, {-594., -590.} };
const double vertex_cut_40[3][2] = { {-0.5, 0.5}, {-0.5, 0.5}, {-581.6, -580.6} };
const double vertex_cut_158[3][2] = { {-0.5, 0.5}, {-0.5, 0.5}, {-581.6, -580.6} };

bool isGoodEventCbm(const DataTreeEvent& event)
{
    if ( event.GetVertexQuality(0) < 0.5 || event.GetVertexQuality(0) > 1.5 ) return false;
    for (int iXyz=0; iXyz<3; ++iXyz)
    {
        const double vtx = event.GetVertexPositionComponent(iXyz, 0);
        if ( vtx < vertex_cut_10[iXyz][0] || vtx > vertex_cut_10[iXyz][1] ) return false;
    }

    return true;
}

int GetNGoodTracks(const DataTreeEvent &event) {
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

bool isGoodEvent(const DataTreeEvent& event,
                 const double e,
                 const int bitBPD,
                 const int bitWFAbeam,
                 const int bitWFAinteract,
                 const int bitVTX,
                 const int bitT4,
                 const int bitS1V1)
{

    energy = e;
//    if ( event.GetPSDEnergy() < 100 )  return false;
//    if ( bitBPD            && !IsGoodBPD(event)                                                   ) return false;
//    if ( bitWFAbeam        &&  WFAcoincidence(event, EnumWFA::kS1_1, EnumWFATimeWindow::kT1)!=1 ) return false;
//    if ( bitWFAinteract    &&  WFAcoincidence(event, EnumWFA::kT4,   EnumWFATimeWindow::kT4)!=1 ) return false;
    if ( bitVTX            && !IsGoodVertex(event, fittedVertexID)) return false;
//    if ( bitT4 == 1        && !IsGoodTrigger(event, EnumTrigger::kT4)                             ) return false;
//    if ( bitT4 == 2        && !IsGoodTrigger(event, EnumTrigger::kT4) && !IsGoodTrigger(event, EnumTrigger::kT2) ) return false;
//    if ( bitS1V1           && !IsGoodSimpleTriggers(event)                                        ) return false;
    if (event.GetNTracks () < 10) return false;
    if (GetNGoodTracks (event) < 10) return false;
//     std::cout << "               GoodEvent" << std::endl;

    return true;
}

bool IsGoodBPD(const DataTreeEvent& event){
//     BPD cuts
    double bpd[3][2];
    for (int iBpd=0; iBpd<3; ++iBpd)
        for (int iXy=0; iXy<2; ++iXy)
            bpd[iBpd][iXy] = event.GetBPD(iBpd)->GetPositionComponent(iXy);


    if (energy == 30)
    {
        for (int iXy=0; iXy<2; ++iXy)
        {
            if ( bpd[0][iXy] < bpd1_cut_30[iXy][0] || bpd[0][iXy] > bpd1_cut_30[iXy][1] )  return false;
            if ( bpd[0][iXy] < bpd1_cut_30[iXy][0] || bpd[0][iXy] > bpd1_cut_30[iXy][1] )  return false;

            if ( bpd[1][iXy] < bpd2_cut_30[iXy][0] || bpd[1][iXy] > bpd2_cut_30[iXy][1] )  return false;
            if ( bpd[1][iXy] < bpd2_cut_30[iXy][0] || bpd[1][iXy] > bpd2_cut_30[iXy][1] )  return false;

            if ( bpd[2][iXy] < bpd3_cut_30[iXy][0] || bpd[2][iXy] > bpd3_cut_30[iXy][1] )  return false;
            if ( bpd[2][iXy] < bpd3_cut_30[iXy][0] || bpd[2][iXy] > bpd3_cut_30[iXy][1] )  return false;
        }
    }
    else if (energy == 13)
    {
        for (int iXy=0; iXy<2; ++iXy)
        {
            if ( bpd[0][iXy] < bpd1_cut_13[iXy][0] || bpd[0][iXy] > bpd1_cut_13[iXy][1] )  return false;
            if ( bpd[0][iXy] < bpd1_cut_13[iXy][0] || bpd[0][iXy] > bpd1_cut_13[iXy][1] )  return false;

            if ( bpd[1][iXy] < bpd2_cut_13[iXy][0] || bpd[1][iXy] > bpd2_cut_13[iXy][1] )  return false;
            if ( bpd[1][iXy] < bpd2_cut_13[iXy][0] || bpd[1][iXy] > bpd2_cut_13[iXy][1] )  return false;

            if ( bpd[2][iXy] < bpd3_cut_13[iXy][0] || bpd[2][iXy] > bpd3_cut_13[iXy][1] )  return false;
            if ( bpd[2][iXy] < bpd3_cut_13[iXy][0] || bpd[2][iXy] > bpd3_cut_13[iXy][1] )  return false;
        }
    }
    return true;
}
//WFA cuts
int WFAcoincidence(const DataTreeEvent& event, const int TriggerId, const int timeWindow){

    int WFAcounter{0};

    const auto wfa = event.GetWFA(TriggerId) -> GetTimesWFA();
    for (auto iwfa : wfa)
    {
        if (abs(iwfa) < timeWindow)
            WFAcounter++;
    }

    return WFAcounter;
}


bool IsGoodVertex(const DataTreeEvent& event, const int kFittedVertexID){
    if ( event.GetVertexQuality(kFittedVertexID) < 0.5 || event.GetVertexQuality(kFittedVertexID) > 1. ) return false;
    for (int iXyz=0; iXyz<3; ++iXyz)
    {
        double vtx = event.GetVertexPositionComponent(iXyz, kFittedVertexID);
        if (energy == 13)
            if ( vtx < vertex_cut_13[iXyz][0] || vtx > vertex_cut_13[iXyz][1] ) return false;
        if (energy == 30)
            if ( vtx < vertex_cut_30[iXyz][0] || vtx > vertex_cut_30[iXyz][1] ) return false;
        if (energy == 40)
            if ( vtx < vertex_cut_40[iXyz][0] || vtx > vertex_cut_40[iXyz][1] ) return false;
        if (energy == 158)
            if ( vtx < vertex_cut_158[iXyz][0] || vtx > vertex_cut_158[iXyz][1] ) return false;
    }
    return true;
}

bool IsGoodTrigger(const DataTreeEvent& event, const int TriggerId){
    return event.GetTrigger(TriggerId)->GetIsFired() ;
}


bool IsGoodSimpleTriggers(const DataTreeEvent& event){

    Float_t s1 = event.GetTrigger(EnumTrigger::kS1)->GetSignal();
    Float_t s2 = event.GetTrigger(EnumTrigger::kS2)->GetSignal();

    if (energy == 30)
    {
        if ( 1.322*s1 +s2 > 410) return false;
        if ( s1 > 175 || s1 < 115 ) return false;
        if ( s2 < 160 ) return false;
    }
    else if (energy == 13)
    {
        if ( 1.258*s1 +s2 > 390) return false;
        if ( s1 > 175 || s1 < 115 ) return false;
        if ( s2 < 150 ) return false;
    }
    return true;
}

}
