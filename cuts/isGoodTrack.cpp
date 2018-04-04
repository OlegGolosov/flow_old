#include "isGoodTrack.h"


namespace Cuts{

int GetTrackPid(const DataTreeTrack& track)
{
    const int charge = track.GetCharge();
    const float dEdx = 0.001 * track.GetdEdx(EnumTPC::kTPCAll); // na49
    const double p = track.GetP();

    if (dEdx > 0.931 + 0.138 * TMath::Log(p) && dEdx < 1.232 + 0.174 * TMath::Log(p)) {
            if (charge < 0) return -211;
            else return 211;
    }

    if (dEdx < 0.931 + 0.138 * TMath::Log(p) && dEdx > 0.5 && p > 3.0) {
//    if (dEdx < 0.931 + 0.138 * TMath::Log(p) && dEdx > 0.5) {
        if (charge > 0) return 2212;
        if (charge < 0) return -2212;
    }

    if (dEdx < 1.7 && dEdx > 1.5 && TMath::Log(p) > 0.2 && TMath::Log(p) < 2.2) {
        if (charge < 0) return 11;
        if (charge > 0) return -11;
    }


//    const float dEdx_cut = 0.8+TMath::Log(10.*p)*0.14;  //-0.004*(p-10)*(p-10) + 0.005*p + 1.45;
//
//    if ( (charge < 0) && (dEdx < dEdx_cut ) && (dEdx > dEdx_cut-0.27) ) pid = -211;
//    if ( (charge > 0) && (dEdx < dEdx_cut-0.27) && (p>2.5) ) pid = 2212;
//    if ( (charge > 0) && (dEdx < dEdx_cut) && (dEdx > dEdx_cut-0.27) ) pid = 211;

    return 0;
}

bool isGoodTrack(const DataTreeTrack& track)
{
    const double NhitsPot = track.GetNumberOfHitsPotential(EnumTPC::kTPCAll);
    const double NhitsPotVTPC1 = track.GetNumberOfHitsPotential(EnumTPC::kVTPC1);
    const double NhitsPotVTPC2 = track.GetNumberOfHitsPotential(EnumTPC::kVTPC2);
    const double NhitsPotMTPC = track.GetNumberOfHitsPotential(EnumTPC::kMTPC);
    const double DCAx = track.GetDCAComponent(0);
    const double DCAy = track.GetDCAComponent(1);
    const double pt = track.GetPt();
    const double eta = track.GetEta();
    const double dEdx = track.GetdEdx(EnumTPC::kTPCAll);
    const double chi2 = track.GetChi2();
//     const int Ndf = track.GetNDF();
    const double ratio_ = double(NhitsPot) / NhitsPot;
//     const int charge = track.GetCharge();

//     std::cout << "dca = " << dcax << "   " << dcay << std::endl;
//     std::cout << "NhitsTotal = " << NhitsTotal << "   " << NhitsVTPC1 + NhitsVTPC2 << std::endl;
//     std::cout << "pT = " << pT << "   " << eta << std::endl;
//     std::cout << "dEdx = " << dEdx << "   " << ratio << std::endl;

//    if ( DCAx * DCAx / 4. + DCAy * DCAy > 1. )              return false;

    if ( eta < 1.4 || eta > 5.0  ) return false;
    if ( pt < 0.0 || pt > 3.0 ) return false;
    if ( TMath::Abs (DCAx) > 3. || TMath::Abs (DCAy) > .5 ) return false;
    if ( (NhitsPotVTPC1 < 20 && NhitsPotVTPC2 < 20) || NhitsPotMTPC < 30)    return false;
    if ( dEdx <= 0 )                                        return false;
    if ( chi2 < 0. || chi2 > 10 )                           return false;
    if ( ratio_ < 0.55 || ratio_ > 1. )                     return false;
    return true;

}

bool isGoodTrackCbm(const DataTreeTrack& track)
{
    if ( track.GetNumberOfHits(0) < 4 ) return false;
    if ( track.GetChi2()/track.GetNDF() > 3 ) return false;
    if ( track.GetVtxChi2() > 3 ) return false;
    if ( track.GetEta() > 2.5 || track.GetEta() < 1.2 ) return false;
    if ( track.GetPt() > 2 || track.GetPt() < 0.1 ) return false;

    return true;
}
}
