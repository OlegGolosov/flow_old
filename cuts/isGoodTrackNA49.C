#ifndef IsGoodTrack_H
#define IsGoodTrack_H 1

Bool_t isGoodTrack(const DataTreeTrack& track)
{
    const Double_t dcax = track.GetDCAComponent(0);
    const Double_t dcay = track.GetDCAComponent(1);
    
    const Int_t NhitsVTPC1 = track.GetNumberOfHits(EnumTPC::kVTPC1);
    const Int_t NhitsVTPC2 = track.GetNumberOfHits(EnumTPC::kVTPC2);
    const Int_t NhitsMTPC  = track.GetNumberOfHits(EnumTPC::kMTPC);
    const Int_t Nhits = track.GetNumberOfHits(EnumTPC::kTPCAll);

    const Int_t NhitsPotVTPC1 = track.GetNumberOfHitsPotential(EnumTPC::kVTPC1);
    const Int_t NhitsPotVTPC2 = track.GetNumberOfHitsPotential(EnumTPC::kVTPC2);
    const Int_t NhitsPotMTPC  = track.GetNumberOfHitsPotential(EnumTPC::kMTPC);
    const Int_t NhitsPot = track.GetNumberOfHitsPotential(EnumTPC::kTPCAll);
    
//     std::cout 
//               << " NhitsVTPC1 = " <<  NhitsVTPC1
//               << " NhitsVTPC2 = " <<  NhitsVTPC2
//               << " NhitsMTPC = " <<  NhitsMTPC
//               << " Nhits = " <<  Nhits
//               << " NhitsPot = " <<  NhitsPot
//               << " dcax = " <<  dcax
//               << " dcay = " <<  dcay
//               << " pT = " <<  track.GetPt()
//               << " eta = " <<  track.GetEta()
//               << " chi2 = " <<  track.GetChi2()
//               << std::endl;
    
    if ( NhitsPot <= 0 ) return false;
    if ( Double_t(Nhits) / NhitsPot <= 0.55 || Double_t(Nhits) / NhitsPot > 1 ) return false;
    if ( track.GetChi2() > 10 || track.GetChi2() < 0 ) return false;
    if ( NhitsPotVTPC1 + NhitsPotVTPC2 < 20 && NhitsPotMTPC < 30) return false;
    if ( TMath::Abs(dcax) > 3.0 || TMath::Abs(dcay) > 0.5) return false;
    if (track.GetPt() > 2.5) return false;
    if (track.GetEta() < 1.4 || track.GetEta() > 5.0) return false;

//     std::cout << "Good track" << std::endl;
    return true;
    
}

#endif
