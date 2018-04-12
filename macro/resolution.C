#include <TMath.h>
#include <TFile.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TProfile.h>
#include <iostream>

#define FACTOR 0.797884561

using namespace std;

Double_t SphericalBesselI (Int_t order, Double_t arg) {
  // compute half-integer modified Bessel functions
  // order >0, for order>5/2, interpolation is used
  // (improve this by using recurrence!!!)

  if (order<0) return 0;
  if (arg<1e-7) return 0;

  switch(order) {
    case 0:  // 1/2
      return FACTOR*sqrt(arg)*TMath::SinH(arg)/arg;
      break;

    case 1:  // 3/2
      return FACTOR*sqrt(arg)*( -TMath::SinH(arg)/(arg*arg) + TMath::CosH(arg)/arg );
      break;

    case 2:  // 5/2
      return FACTOR*sqrt(arg)*( (3./(arg*arg)+1.)*TMath::SinH(arg)/arg - 3.*TMath::CosH(arg)/(arg*arg) );
      break;

    default:
      break;

  }

  return 0.5*(TMath::BesselI(order,arg)+TMath::BesselI(order+1,arg));   // use average of integer-order Bessel
}

Double_t ComputeResolutionOllitraut(Double_t ratio, Int_t n) {
 // compute Ollitrault correction factor

    Double_t chisq = -2.*TMath::Log(2.*ratio);
    Double_t chi = sqrt(chisq);
    cout << chi << "\t\t";

  Int_t n1 = (n-1)/2;
  Int_t n2 = (n+1)/2;
  Double_t sumBessel;
  if (n%2==1) sumBessel = TMath::BesselI(n1,0.5*chisq) + TMath::BesselI(n2,0.5*chisq);  // integer order
  // half-integer order approximated via interpolation of nearest integer-order modified Bessel functions
  // (Exact solution is not implemented in Root!), checked ok vs. Ollitrault's plot in arXiv:nucl-ex/9711003v2
  //  else sumBessel = 0.5*( TMath::BesselI(n1,0.5*chisq) + 2*TMath::BesselI(n2,0.5*chisq) + TMath::BesselI(n2+1,0.5*chisq) ) ;
  else sumBessel = SphericalBesselI(n1,0.5*chisq) + SphericalBesselI(n2,0.5*chisq);  // exact solution for order 1/2, 3/2, 5/2
  Double_t fac = sqrt(TMath::Pi()) / 2. * chi * exp(-0.5*chisq) * sumBessel;
  return fac;
}

void calculate (TH2F *deltaPsi2bins, TString flowPath) {
    float res, chi;
    int nBins = deltaPsi2bins -> GetNbinsX ();
    float xMax = deltaPsi2bins -> GetXaxis () -> GetXmax ();
    float xMin = deltaPsi2bins -> GetXaxis () -> GetXmin ();
    TString setName = deltaPsi2bins -> GetTitle ();

    TH1F *hResolution = new TH1F ("hR_Oli_" + setName, "hR_Oli_" + setName, nBins, xMin, xMax);
    TH1F *hChi = new TH1F ("hChi_" + setName, "hChi_" + setName, nBins, xMin, xMax);
    cout << "Bin\tRatio\t\tChi\t\tResolution\n";
    for (int bin = 1; bin <= nBins; bin++) {
        Double_t ratio = deltaPsi2bins -> GetBinContent (bin, 2) / (deltaPsi2bins -> GetBinContent (bin, 2) + deltaPsi2bins -> GetBinContent (bin, 1));
        cout << bin << "\t" << ratio << "\t";
        chi = sqrt (- 2. * log (2. * ratio));
        hChi -> SetBinContent (bin, chi);
        res = ComputeResolutionOllitraut (ratio, 1);
        cout << res << endl;
        hResolution -> SetBinContent (bin, res);
    }
    hResolution -> SetMarkerStyle (20);
    TCanvas *c1 = new TCanvas ();
    hResolution -> Draw ();
    c1 -> Print (flowPath + "hChi.C");
    hResolution -> Write ();
    TCanvas *c2 = new TCanvas ();
    hChi -> Draw ();
    c2 -> Print (flowPath + "hR_Oli.C");
    hChi -> Write ();
}

void resolution (int harmonic = 1) {
    Float_t pi = TMath::Pi();
    TString corrPath = "build/";
    TString flowPath = "build/";
    TString filename = "qn.root";
    TFile *resFile = new TFile (flowPath + "resolution.root", "recreate");

    TChain *ch = new TChain ("tree");
    ch -> Add (corrPath + filename);

    TCanvas *c1 = new TCanvas ();
		
    ch -> Draw (Form ("acos (cos (1.0 / %i * (atan2 (TPC_a_1.data_.q_.y[][%i], TPC_a_1.data_.q_.x[][%i]) - atan2 (TPC_b_1.data_.q_.y[][%i], TPC_b_1.data_.q_.x[][%i])))) : Centrality >> deltaPhi2bins(6, 0, 6, 2, 0, %f)", harmonic, harmonic, harmonic, harmonic, harmonic, pi), "", "colz");
//    ch -> Draw ("acos (cos (1 * (atan2 (TPC_a_1.data_.q_.y[][1], TPC_a_1.data_.q_.x[][1]) - atan2 (TPC_b_1.data_.q_.y[][1], TPC_b_1.data_.q_.x[][1])))) : Eveto >> deltaPhi2bins(6, 0, 8000, 100, 0, 3.14)", "", "colz");
    TH2F *deltaPhi2bins = (TH2F*) c1 -> GetPrimitive ("deltaPhi2bins");
    deltaPhi2bins -> SetTitle ("deltaPhi2bins");
    c1 -> Print (flowPath + "deltaPsi2bins.C");
    deltaPhi2bins -> Write ();
    calculate (deltaPhi2bins, flowPath);
    resFile -> Close ();
}
