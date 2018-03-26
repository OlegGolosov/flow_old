#include <iostream>
#include <fstream>
#include <vector>

#include "TClonesArray.h"
#include "TObject.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TProfile.h"
#include "TFile.h"
#include "TChain.h"

#include "DataTreeQA.h"
#include "DataTreeEvent.h"
#include "DataTreeTrack.h"
#include "DataTreeMCTrack.h"
#include "DataTreeTOFHit.h"

#include "cuts/isGoodEvent.h"
#include "cuts/isGoodTrack.h"


void DataTreeQA::Init()
{
    if (fNA49) NominalVertexPos[2] = -581;
    
}

void DataTreeQA::RunQA ( int nEvents )
{
    InitHistograms();
    Init();    
    
    int nevents = nEvents < fChain->GetEntries() ? nEvents : fChain->GetEntries();
    int outputstep = 1000;
    std::cout << "Entries = " << nevents << std::endl;
    
    for (int i=0; i<nevents; i++)
    {
        if ( (i+1) % outputstep == 0) std::cout << i+1 << "/" << nevents << "\r" << std::flush;
        fChain->GetEntry(i);
        FillHistograms();
    }
    WriteHistograms();
}

std::unique_ptr<TChain> DataTreeQA::MakeChain(std::string filename, std::string treename) {
  std::unique_ptr<TChain> chain(new TChain(treename.data()));
  std::ifstream in;
  in.open(filename);
  std::string line;
  std::cout << "Adding files to chain:" << std::endl;
  while ((in >> line).good()) {
    if (!line.empty()) {
      chain->AddFile(line.data());
      std::cout << line << std::endl;
    }
  }
  std::cout << "Number of entries = " << chain->GetEntries() << std::endl;
  return chain;
}


void DataTreeQA::InitHistograms()
{
    int nbins = 1000;
    
    double mom_low[4]  = {0, -2, -3.2, -2};
    double mom_high[4] = {3.5, 8, 3.2, 8};
    double y_low = 0.;
    double y_high = 7.;
    double p_low = 0.;
    double p_high = 10.;
    
    TString name;
    
    for (int iXyz=0; iXyz<3; ++iXyz)
    {
        name = Form("hVertexPos%s", sXyz[iXyz].Data());
        hVertexPos[iXyz] = new TH1D(name, name, nbins, -10+NominalVertexPos[iXyz], 10+NominalVertexPos[iXyz]);
        name = Form("hMCVertexPos%s", sXyz[iXyz].Data());
        hMCVertexPos[iXyz] = new TH1D(name, name, nbins, -2+NominalVertexPos[iXyz], 2+NominalVertexPos[iXyz]);
        name = Form("hMatchVertexPos%s", sXyz[iXyz].Data());
        hMatchVertexPos[iXyz] = new TH2D(name, name, nbins, -2+NominalVertexPos[iXyz], 2+NominalVertexPos[iXyz], nbins, -2+NominalVertexPos[iXyz], 2+NominalVertexPos[iXyz]);
        name = Form("hTrackDCA%s", sXyz[iXyz].Data());        
        hTrackDCA[iXyz] = new TH1D(name, name, nbins, -10, 10);
    }
    
    hVertexQuality = new TH1D("hVertexQuality", "hVertexQuality", 1000, 0, 10);
    
    
    hVertexChi2 = new TH1D("hVertexChi2", "hVertexChi2", 500, 0, 100);
    hTrackDCAXY = new TH2D("hTrackDCAXY", "hTrackDCAXY", nbins, -10, 10, nbins, -10, 10);
    
    hMreco = new TH1D("hMreco","Mreco", 1000, 0, 1000);
    hMsim = new TH1D("hMsim", "Msim", 1500, 0, 1500);
    hE = new TH1D("hE", "E", 500, 0, psdmax);
    hMEcorr = new TH2D("hMEcorr", "M : E", 1000, 0, 1000, 500, 0, psdmax);
    hMMcorr = new TH2D("hMMcorr", "Mreco : Msim", 1000, 0, 1000, 1500, 0, 1500);
    hMBcorr = new TH2D("hMBcorr", "Mreco : B", 1000, 0, 1000, 200, 0, 20);
    hEBcorr = new TH2D("hEBcorr", "Epsd : B", 500, 0, psdmax, 200, 0, 20);
    
    hNdf =     new TH1D("hNdf", "hNdf", 350, 0, 350);
    hCharge =  new TH1D("hCharge", "hCharge", 5, -2, 2);
    hChi2Vertex = new TH1D("hChi2Vertex", "hChi2Vertex", 500, 0, 20);
    hChi2 =    new TH1D("hChi2", "hChi2", 1000, 0, 20);
    for (short iTPC=0; iTPC<4; ++iTPC)
    {
        name = Form("hNhits_%s", sTPC[iTPC].Data());
        hNhits[iTPC] =   new TH1D(name, name, 250, 0, 250);
        name = Form("hNhitsPot_%s", sTPC[iTPC].Data());
        hNhitPot[iTPC] = new TH1D(name, name, 250, 0, 250);
        name = Form("hTrackdEdx_%s", sTPC[iTPC].Data());
        hTrackdEdx[iTPC] = new TH2D(name, name,  nbins, -10, 10, nbins, 0, 10);
        
        
    }
    for (short iMom=0; iMom<4; ++iMom)
    {
        name = Form("hTrack%s", sMomentum[iMom].Data());
        hTrackMomentum[iMom] = new TH1D(name, name, nbins, mom_low[iMom], mom_high[iMom]);
        name = Form("hTrackMatch%s", sMomentum[iMom].Data());
        hTrackMomentumMatch[iMom] = new TH2D(name, name, nbins, mom_low[iMom], mom_high[iMom], nbins, mom_low[iMom], mom_high[iMom]);
    }
    
    hTrackMomentumCorr[0] = new TH2D("hTrackPtEta", "pT : eta",     nbins, mom_low[1], mom_high[1], nbins, mom_low[0], mom_high[0]);
    hTrackMomentumCorr[1] = new TH2D("hTrackPtPhi", "pT : phi",     nbins, mom_low[2], mom_high[2], nbins, mom_low[0], mom_high[0]);
    hTrackMomentumCorr[2] = new TH2D("hTrackEtaPhi", "eta : phi",  nbins, mom_low[2], mom_high[2], nbins, mom_low[1], mom_high[1]);
    hTrackMomentumCorr[3] = new TH2D("hTrackYPt", "pT : Y",  nbins, mom_low[1], mom_high[1], nbins, mom_low[0], mom_high[0]);
    hMCTrackMomentumCorr[0] = new TH2D("hMCTrackPtEta", "MC pT : eta",     nbins, mom_low[1], mom_high[1], nbins, mom_low[0], mom_high[0]);
    hMCTrackMomentumCorr[1] = new TH2D("hMCTrackPtPhi", "MC pT : phi",     nbins, mom_low[2], mom_high[2], nbins, mom_low[0], mom_high[0]);
    hMCTrackMomentumCorr[2] = new TH2D("hMCTrackEtaPhi", "MC eta : phi",  nbins, mom_low[2], mom_high[2], nbins, mom_low[1], mom_high[1]);
    
    for (short iGarm=0; iGarm<2; ++iGarm)
        for (short iPart=0; iPart<8; ++iPart)
        {
            name = Form("hv%d%s_pT", iGarm+1, sParticles[iPart].Data());
            pVn_pT[iGarm][iPart] = new TProfile(name, name, 50, mom_low[0], mom_high[0]);
            name = Form("hv%d%s_Y", iGarm+1, sParticles[iPart].Data());
            pVn_Y[iGarm][iPart] = new TProfile(name, name, 50, y_low, y_high);
        }
        
        for (short iPart=0; iPart<8; ++iPart)
        {
            name = Form("hTrack_%s_pT_Y", sParticles[iPart].Data());
            hTrackPtY[iPart] = new TH2D (name, name, nbins, y_low, y_high, nbins, mom_low[0], mom_high[0]);
            name = Form("hMCTrack_%s_pT_Y", sParticles[iPart].Data());
            hMCTrackPtY[iPart] = new TH2D (name, name, nbins, y_low, y_high, nbins, mom_low[0], mom_high[0]);
        }
        
        hPSDGeometry = new TH2D("hPSDGeometry", "PSD Geometry", 2000, -100, 100, 2000, -100, 100);
        
        hTofM2 = new TH2D("hTofM2", "hTofM2", nbins, -p_high, p_high, nbins, -0.2, 1.3);
        hTofBeta = new TH2D("hTofBeta", "hTofBeta", nbins, -p_high, p_high, nbins, -0.2, 1.3);
        
        for (short iPart=0; iPart<8; ++iPart)
        {   
            name = Form("hTof_%s_M2", sParticles[iPart].Data());
            hTofM2Part[iPart] = new TH2D(name, name, nbins, -p_high, p_high, nbins, -0.2, 1.3);
        }
        
        
}

void DataTreeQA::FillEventInfo()
{
        
    int Mreco = DTEvent -> GetNTracks();
    int Msim = DTEvent -> GetNMCTracks();
    double E = DTEvent -> GetPSDEnergy();
    double B = DTEvent -> GetImpactParameter();
    
    if (fNA61) B *= 10e12;
    double psiRP = DTEvent -> GetRPAngle();
    
    int Msel = 0;
    DataTreeTrack* track;
    
    int nTracks;
    if (fNA61) 
        nTracks = DTEvent->GetNVertexTracks();
    else
        nTracks = DTEvent->GetNTracks();
    
    for (int i=0;i<nTracks; i++)
    {
        
        if (fNA61) 
            track = DTEvent -> GetVertexTrack(i);
        else
            track = DTEvent -> GetTrack(i);
        
        if ( fIsTrackCuts && ! Cuts::isGoodTrack(*track) ) continue;
        Msel++;
    }
    
    for (int iXyz=0; iXyz<3; ++iXyz)
    {
        hVertexPos[iXyz] -> Fill(DTEvent -> GetVertexPositionComponent(iXyz));
        hMCVertexPos[iXyz] -> Fill(DTEvent -> GetMCVertexPositionComponent(iXyz));
        hMatchVertexPos[iXyz] -> Fill(DTEvent -> GetMCVertexPositionComponent(iXyz), DTEvent -> GetVertexPositionComponent(iXyz));
    }
    
    hVertexChi2 -> Fill(DTEvent -> GetVertexQuality());
    hVertexQuality -> Fill( DTEvent->GetVertexQuality(0) );
    
    hMreco -> Fill(Msel);
    hMsim -> Fill(Msim);
    hE -> Fill(E);
    hMEcorr -> Fill(Msel, E);
    hMMcorr -> Fill(Msel, Msim);
    hMBcorr -> Fill(Msel, B);
    hEBcorr -> Fill(E, B);        
}

void DataTreeQA::FillRecoTracks()
{
    DataTreeTrack* track;
    DataTreeMCTrack* mctrack;
    
    int nTracks;
    if (fNA61) 
        nTracks = DTEvent->GetNVertexTracks();
    else
        nTracks = DTEvent->GetNTracks();
    
    for (int i=0;i<nTracks; i++)
    {
        if (fNA61) 
            track = DTEvent -> GetVertexTrack(i);
        else
            track = DTEvent -> GetTrack(i);
        
        if (fIsTrackCuts)
            if ( ! Cuts::isGoodTrack(*track) ) continue;
        
        hNdf      -> Fill (track->GetNDF());  
        hChi2     -> Fill (track->GetChi2() / track->GetNDF());   
        hNhits[0]    -> Fill (track->GetNumberOfHits(EnumTPC::kVTPC1));  
        hNhitPot[0]  -> Fill (track->GetNumberOfHitsPotential(EnumTPC::kVTPC1));
        hNhits[1]    -> Fill (track->GetNumberOfHits(EnumTPC::kVTPC2));  
        hNhitPot[1]  -> Fill (track->GetNumberOfHitsPotential(EnumTPC::kVTPC2));
        hNhits[2]    -> Fill (track->GetNumberOfHits(EnumTPC::kMTPC));  
        hNhitPot[2]  -> Fill (track->GetNumberOfHitsPotential(EnumTPC::kMTPC));
        hNhits[3]    -> Fill (track->GetNumberOfHits(EnumTPC::kTPCAll));  
        hNhitPot[3]  -> Fill (track->GetNumberOfHitsPotential(EnumTPC::kTPCAll) );
        hTrackdEdx[0]   -> Fill ( track->GetCharge() * TMath::Log(track->GetP()*10), track->GetdEdx(EnumTPC::kVTPC1) );
        hTrackdEdx[1]   -> Fill ( track->GetCharge() * TMath::Log(track->GetP()*10), track->GetdEdx(EnumTPC::kVTPC2) );
        hTrackdEdx[2]   -> Fill ( track->GetCharge() * TMath::Log(track->GetP()*10), track->GetdEdx(EnumTPC::kMTPC) );
        hTrackdEdx[3]   -> Fill ( track->GetCharge() * TMath::Log(track->GetP()*10), track->GetdEdx(EnumTPC::kTPCAll) );
        
        for (int iXyz=0; iXyz<3; ++iXyz)
            hTrackDCA[iXyz] -> Fill( track->GetDCAComponent(iXyz) );
        
        hTrackDCAXY -> Fill (track->GetDCAComponent(0), track->GetDCAComponent(1)) ; 
        
        hCharge   -> Fill (track->GetCharge());
        hChi2Vertex  -> Fill (track->GetVtxChi2());
        
        double mom[4] = { track->GetPt(), track->GetEta(), track->GetPhi(), track->GetRapidity() };
        for (int iMom=0; iMom<4; ++iMom)
            hTrackMomentum[iMom] -> Fill( mom[iMom] );
        
        hTrackMomentumCorr[0] -> Fill(mom[1], mom[0]);
        hTrackMomentumCorr[1] -> Fill(mom[2], mom[0]);
        hTrackMomentumCorr[2] -> Fill(mom[2], mom[1]);
        hTrackMomentumCorr[3] -> Fill(mom[3], mom[0]);
        
        int recopid = Cuts::GetTrackPid(*track);
        if (recopid == 211)   hTrackPtY[3] -> Fill(mom[3], mom[0]);
        if (recopid == -211)  hTrackPtY[2] -> Fill(mom[3], mom[0]);
        if (recopid == 2212)  
        {
            double p = track->GetP();
            double pz = track->GetPz();
            double e=sqrt( p*p + 0.938*0.938 );
            hTrackPtY[0] -> Fill( 0.5*log( (e+pz)/(e-pz) ) , mom[0]);
        }
        
        if (!fIsSim) continue;
        int mctrackid = track -> GetMCTrackId();
        if (mctrackid>=0 )
        {
            mctrack = DTEvent -> GetMCTrack(mctrackid);
            double mc_mom[3] = { mctrack->GetPt(), mctrack->GetEta(), mctrack->GetPhi() };
            double mom[3] = { track->GetPt(), track->GetEta(), track->GetPhi() };
            double mc_y = mctrack->GetRapidity();
            mc_y -= Ybeam;
            
            int pdg = mctrack->GetPdgId();
            int i;
            for(i=0; i<8; ++i)
                if (PdgCodes[i] == pdg) break;
                
                if (i != 8)
                {
                    hMCTrackPtY[i] -> Fill(mc_y, mom[0]);
                }
                hTrackMomentumMatch[0] -> Fill(mc_mom[0], mom[0]);
            hTrackMomentumMatch[1] -> Fill(mc_mom[1], mom[1]);
            hTrackMomentumMatch[2] -> Fill(mc_mom[2], mom[2]);
        }
    }
}

void DataTreeQA::FillMCTracks()
{
    double psiRP = DTEvent -> GetRPAngle();
    double  mc_p, mc_y;
    DataTreeMCTrack* mctrack;
    
    
    for (int iMcTrack=0; iMcTrack<DTEvent->GetNMCTracks(); ++iMcTrack)
    {
        mctrack = DTEvent -> GetMCTrack(iMcTrack);
        
        double mc_mom[3] = { mctrack->GetPt(), mctrack->GetEta(), mctrack->GetPhi() };
        mc_y = mctrack->GetRapidity();
        int pdg = mctrack->GetPdgId();
        
        mc_y -= Ybeam;
        
        int i;
        for(i=0; i<8; ++i)
            if (PdgCodes[i] == pdg) break;
            
            if (i != 8)
            {
                hMCTrackPtY[i] -> Fill(mc_y, mc_mom[0]);
                
                for (int iGarm=0; iGarm<2; ++iGarm)
                {
                    pVn_pT[iGarm][i] -> Fill ( mc_mom[0], cos( (iGarm+1)*(mc_mom[2]-psiRP) ) ); 
                    pVn_Y[iGarm][i] -> Fill ( mc_y, cos( (iGarm+1)*(mc_mom[2]-psiRP) ) ); 
                }
            }
            
            hMCTrackMomentumCorr[0] -> Fill(mc_mom[1], mc_mom[0]);
            hMCTrackMomentumCorr[1] -> Fill(mc_mom[2], mc_mom[0]);
            hMCTrackMomentumCorr[2] -> Fill(mc_mom[2], mc_mom[1]);
            
            std::vector <int> recoId = mctrack->GetRecoTrackId();
            if (recoId.size() <= 0) continue;
    }
}


void DataTreeQA::FillTof()
{
    DataTreeTrack* track;
    DataTreeTOFHit *tof;
    for (int i=0;i<DTEvent->GetNTOFHits(); i++)
    {
        tof = DTEvent->GetTOFHit(i);
        
        if (tof->GetRecoTrackId().size() == 0) continue;
        int trackid = tof->GetFirstRecoTrackId();
        if (trackid<0) continue;
        
        track = DTEvent -> GetTrack(trackid);
        double l = track->GetLength();
        double p = track->GetP();
        double time = tof->GetTime();
        int q = track->GetCharge();
        
        double m2 = p*p*(1./((l/time/SpeedOfLight)*(l/time/SpeedOfLight))-1.);
        hTofM2  -> Fill(p*q, m2);
        hTofBeta  -> Fill(p*q, l/time/SpeedOfLight);
    }
}

void DataTreeQA::FillHistograms()
{   
    if (fIsEventCuts)
        if (! Cuts::isGoodEvent(*DTEvent) ) return;
    
    FillEventInfo();
    FillRecoTracks();
//     if (fIsSim)
//         FillMCTracks();
    //     FillTof();
}

void DataTreeQA::WriteHistograms()
{
    
    std::cout << "dghhhhhhhhhhhhh" << std::endl;
    
    TFile *MyFile = new TFile(fOutputFile, "RECREATE"); 
    if ( MyFile->IsOpen() ) std::cout << "File opened successfully" << std::endl; 
    
    MyFile->cd();
    TDirectory *savdir = gDirectory;
    
    TDirectory *reco = savdir->mkdir( "reco_info" );
    TDirectory *sim = savdir->mkdir( "sim_info" );
    TDirectory *recosim = savdir->mkdir( "reco_vs_sim_info" );
    
    reco->cd();
    
    for (int iXyz=0; iXyz<3; ++iXyz)
        hVertexPos[iXyz] -> Write();
    
    hVertexQuality->Write();
    hMreco -> Write();
    hE -> Write();
    hMEcorr -> Write();
    hNdf  -> Write();
    hCharge   -> Write();
    hChi2Vertex -> Write();
    hChi2     -> Write();
    for(int i=0; i<4; ++i)
    {
        hNhits[i]  -> Write();
        hNhitPot[i] -> Write();
        hTrackdEdx[i] -> Write();
    }

    for (int iPart=0; iPart<8; ++iPart)
        hTrackPtY[iPart]  -> Write();
    
    hTofM2  -> Write();
    hTofBeta -> Write();
    
    for (int iMom=0; iMom<4; ++iMom)
    {
        hTrackMomentum[iMom]  -> Write();
        hTrackMomentumCorr[iMom]  -> Write();
    }
    
    for (int iXyz=0; iXyz<3; ++iXyz)
        hTrackDCA[iXyz] -> Write();
    hTrackDCAXY -> Write();
    
    if (!fIsSim) {MyFile->Close();  return; }
    
    sim->cd();
    for (int iXyz=0; iXyz<3; ++iXyz)
        hMCVertexPos[iXyz] -> Write();
    hMsim -> Write();
    for (int iMom=0; iMom<3; ++iMom)
        hMCTrackMomentumCorr[iMom] -> Write();
    for (int iGarm=0; iGarm<2; ++iGarm)
        for (int iPart=0; iPart<8; ++iPart)
        {
            pVn_pT[iGarm][iPart]  -> Write();
            pVn_Y[iGarm][iPart] -> Write();
        }
        
        for (int iPart=0; iPart<8; ++iPart)
            hMCTrackPtY[iPart] -> Write();
        
        recosim->cd();
    for (int iXyz=0; iXyz<3; ++iXyz)
        hMatchVertexPos[iXyz] -> Write();
    hMMcorr -> Write();
    hMBcorr -> Write();
    hEBcorr -> Write();
    for (int iMom=0; iMom<3; ++iMom)
        hTrackMomentumMatch[iMom] -> Write();
    for (int iPart=0; iPart<8; ++iPart)
        hMCTrackPtY[iPart]  -> Write();
    
    
    //     hPSDGeometry -> Write();
    for (int iPart=0; iPart<8; ++iPart)
    {   
        hTofM2Part[iPart] -> Write();
    }
    
    MyFile->Close();     
}
