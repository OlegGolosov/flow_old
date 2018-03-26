#ifndef DataTreeQA_H
#define DataTreeQA_H 1

#include <vector>
#include <iostream>

#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TChain.h"

#include "DataTreeEvent.h"


class DataTreeQA
{
    
public:
  
    DataTreeQA(std::string treename) : 
        fChain (MakeChain(treename) ),
        DTEvent (nullptr)
    {
        DTEvent = new DataTreeEvent;
        fChain->SetBranchAddress("DTEvent", &DTEvent);
//         std::cout << DTEvent->GetPSDEnergy() << std::endl;
        
    };
    
    void Init();
    
    void InitHistograms();
    void FillEventInfo();
    void FillRecoTracks();
    void FillMCTracks();
    void FillTof();
    void FillHistograms();
    void WriteHistograms();    
    void RunQA( int nEvents = 100 );
 
    void SetIsSim(bool is=true) { fIsSim = is; }
    void SetIsNA61(bool is=true) { fNA61 = is; }
    void SetIsNA49(bool is=true) { fNA49 = is; }
    
    std::unique_ptr<TChain> MakeChain(std::string filename, std::string treename = "DataTree");

    
private:    
    
    TString fInputFilelist;
    TString fOutputFile{"qa.root"};
    std::unique_ptr<TChain> fChain;
    DataTreeEvent *DTEvent;

    float vertex_cut_10[3][2] = { {-1, 1.}, {-1, 1}, {-1, 1.} };

    //float Ybeam = 1.531;  //TODO implement with formula
    float Ybeam = 2.22;  //TODO implement with formula
    bool fNA61 = true;
    bool fNA49 = false;
    bool fIsSim = false;
    bool fIsEventCuts = true;
    bool fIsTrackCuts = true;

    float NominalVertexPos[3] = {0,0,-592.};
    float psdmax=8000;
        
    const TString sXyz[3] = {"X", "Y", "Z"};
    const TString sCharge[2] = {"Pos", "Neg"};
    const TString sParticles[8] = {"p", "p_bar","pi_pos","pi_neg","K_pos","K_neg","Lambda","Lambda_bar"};
    const int PdgCodes[8] = {     2212, -2212,    211,     -211,    321,    -321,   3122,      -3122   };
    const TString sMomentum[4] = {"Pt", "Eta", "Phi", "Y"};
    const TString sTPC[4] = {"VTPC1", "VTPC2", "MTPC", "allTPC"};

    TH1D* hVertexPos[3];
    TH1D* hVertexQuality;
    TH1D* hMCVertexPos[3];
    TH2D* hMatchVertexPos[3];

    TH1D* hVertexChi2;

    TH1D* hMreco;
    TH1D* hMsim;
    TH1D* hE;
    TH2D* hMEcorr;
    TH2D* hMMcorr;
    TH2D* hMBcorr;
    TH2D* hEBcorr;

    //Tracks parameters
    TH1D* hNdf;
    TH1D* hCharge;
    TH1D* hChi2Vertex;
    TH1D* hChi2;
    TH1D* hNhits[4];
    TH1D* hNhitPot[4];
    TH1D* hNhitRatio[4];
    TH1D* hTrackDCA[3];
    TH2D* hTrackDCAXY;

    TH1D* hTrackMomentum[4];
    TH2D* hTrackMomentumCorr[4];
    TH2D* hMCTrackMomentumCorr[4];
    TH2D* hTrackMomentumMatch[4];

    TH2D* hTrackdEdx[4];
    TH2D* hTrackPtY[8];
    TH2D* hMCTrackPtY[8];

    //PSD
    TH2D* hPSDGeometry;
    //TOF
    TH2D* hTofM2;
    TH2D* hTofBeta;
    TH2D* hTofM2Part[8];
    // Flow
    TProfile* pVn_pT[2][8];
    TProfile* pVn_Y[2][8];



    
};

#endif




