//
// Created by Lukas Kreis on 13.11.17.
//
#include <utility>
#include <TCanvas.h>
#include <TFile.h>
#include <TLegend.h>

#include "SimpleTask.h"
#include "Base/DataContainerHelper.h"

SimpleTask::SimpleTask(std::string filelist, std::string treename) :
    in_tree_(this->MakeChain(std::move(filelist), treename)),
    reader_(new TTreeReader(in_tree_.get())) { }

void SimpleTask::Configure(Qn::CorrelationManager &a) {

  auto scalar = [](const std::vector<Qn::QVector> &a) -> double {
    return a[0].x(2)*a[1].x(2) + a[0].y(2)*a[1].y(2);
  };
  auto XY = [](const std::vector<Qn::QVector> &a) {
    return 2*a[0].x(1)*a[1].y(1);
  };
  auto YX = [](const std::vector<Qn::QVector> &a) {
    return 2*a[0].y(1)*a[1].x(1);
  };
  auto XX = [](const std::vector<Qn::QVector> &a) {
    return 2*a[0].x(1)*a[1].x(1);
  };
  auto YY = [](const std::vector<Qn::QVector> &a) {
    return 2*a[0].y(1)*a[1].y(1);
  };
  auto Y2XY = [](const std::vector<Qn::QVector> &a) {
    return a[0].y(2)*a[1].x(1)* a[2].y(1);
  };
  auto Y2YX = [](const std::vector<Qn::QVector> &a) {
    return a[0].y(2)*a[1].y(1)* a[2].x(1);
  };
  auto X2XX = [](const std::vector<Qn::QVector> &a) {
    return a[0].x(2)*a[1].x(1)* a[2].x(1);
  };
  auto X2YY = [](const std::vector<Qn::QVector> &a) {
    return a[0].x(2)*a[1].y(1)* a[2].y(1);
  };
  auto psiA_psiB = [](const std::vector<Qn::QVector> &a) {
    return atan2 (a[0].y(1), a[0].x(1)) - atan2 (a[1].y(1), a[1].x(1));
  };
  auto psi2A_psi2B = [](const std::vector<Qn::QVector> &a) {
    return atan2 (a[0].y(2), a[0].x(2)) - atan2 (a[1].y(2), a[1].x(2));
  };

  a.AddDataContainer("PSD1");
  a.AddDataContainer("PSD2");
  a.AddDataContainer("PSD3");
  a.AddDataContainer("TPC_eta");
  a.AddDataContainer("TPC_pT");
  a.AddDataContainer("TPC_R1");
  a.AddDataContainer("TPC_R2");

  if (issim_)
  {
    a.AddDataContainer("MC_pT");
    a.AddDataContainer("MC_eta");
    a.AddDataContainer("PSI");
  }

  std::vector <float> multBins ({2.6, 4.4, 6.6, 9.9, 14.5, 20.4, 28.3, 38.1, 50.2, 64.7,
                                81.9, 102.1, 125.0, 152.1, 183.1, 218.5, 259.9, 307.3, 364.2});

//  a.AddEventVariable({"Centrality", {0., 5., 10., 15., 20., 25., 30., 35., 40, 45., 50., 55., 60., 65., 70., 80, 90, 100}});
  a.AddEventVariable({"Multiplicity", multBins});
//  a.AddFunction("TPC", Rebin);

  const std::string sDet[] = { "PSD1", "PSD2", "PSD3", "TPC_eta", "TPC_pT", "TPC_R1", "TPC_R2" };
  const std::string sMc[] = { "MC_pT", "MC_eta"};

  const std::string sTracks[] = { sDet[3], sDet[4], sDet[5], sDet[6] };
  const std::string sPsd[] = { sDet[0], sDet[1], sDet[2]};

  const std::string sPsdPsdName[] = { "PSD1, PSD2", "PSD1, PSD3", "PSD2, PSD3" };
  const std::string sPsdPsd[] = { "PSD1_PSD2", "PSD1_PSD3", "PSD2_PSD3", };
  const std::string sDetSim[] = { "PSD1, PSI", "PSD2, PSI", "PSD3, PSI"};

  if (issim_)
  {
    for (ushort iDet=0; iDet<7; ++iDet)
    {
        a.AddCorrelation( sDet[iDet] + "_PSI_XX", sDet[iDet] + ", PSI", XX);
        a.AddCorrelation( sDet[iDet] + "_PSI_YY", sDet[iDet] + ", PSI", YY);
        a.AddCorrelation( sDet[iDet] + "_PSI_XY", sDet[iDet] + ", PSI", XY);
        a.AddCorrelation( sDet[iDet] + "_PSI_YX", sDet[iDet] + ", PSI", YX);
    }
    for (ushort iDet=0; iDet<2; ++iDet)
    {
        a.AddCorrelation( sMc[iDet] + "_PSI_XX", sMc[iDet] + ", PSI", XX);
        a.AddCorrelation( sMc[iDet] + "_PSI_YY", sMc[iDet] + ", PSI", YY);
        a.AddCorrelation( sMc[iDet] + "_PSI_XY", sMc[iDet] + ", PSI", XY);
        a.AddCorrelation( sMc[iDet] + "_PSI_YX", sMc[iDet] + ", PSI", YX);
    }
 }


  for (ushort iPsd=0; iPsd<3; ++iPsd)
  for (ushort iTrack=0; iTrack<4; ++iTrack)
  {
    a.AddCorrelation( sTracks[iTrack] + "_" + sPsd[iPsd]+ "_XX", sTracks[iTrack] + ", " + sPsd[iPsd], XX);
    a.AddCorrelation( sTracks[iTrack] + "_" + sPsd[iPsd]+ "_YY", sTracks[iTrack] + ", " + sPsd[iPsd], YY);
    a.AddCorrelation( sTracks[iTrack] + "_" + sPsd[iPsd]+ "_XY", sTracks[iTrack] + ", " + sPsd[iPsd], XY);
    a.AddCorrelation( sTracks[iTrack] + "_" + sPsd[iPsd]+ "_YX", sTracks[iTrack] + ", " + sPsd[iPsd], YX);
  }

  for (ushort iDet=0; iDet<3; ++iDet)
  {
    a.AddCorrelation(sPsdPsd[iDet] + "_XX", sPsdPsdName[iDet], XX);
    a.AddCorrelation(sPsdPsd[iDet] + "_YY", sPsdPsdName[iDet], YY);
    a.AddCorrelation(sPsdPsd[iDet] + "_XY", sPsdPsdName[iDet], XY);
    a.AddCorrelation(sPsdPsd[iDet] + "_YX", sPsdPsdName[iDet], YX);

    a.AddCorrelation("TPC_R2_" + sPsdPsd[iDet] + "_X2XX", "TPC_R2, " + sPsdPsdName[iDet], X2XX);
    a.AddCorrelation("TPC_R2_" + sPsdPsd[iDet] + "_X2YY", "TPC_R2, " + sPsdPsdName[iDet], X2YY);
    a.AddCorrelation("TPC_R2_" + sPsdPsd[iDet] + "_Y2XY", "TPC_R2, " + sPsdPsdName[iDet], Y2XY);
    a.AddCorrelation("TPC_R2_" + sPsdPsd[iDet] + "_Y2YX", "TPC_R2, " + sPsdPsdName[iDet], Y2YX);

    a.AddCorrelation("TPC_eta_" + sPsdPsd[iDet] + "_X2XX", "TPC_eta, " + sPsdPsdName[iDet], X2XX);
    a.AddCorrelation("TPC_eta_" + sPsdPsd[iDet] + "_X2YY", "TPC_eta, " + sPsdPsdName[iDet], X2YY);
    a.AddCorrelation("TPC_eta_" + sPsdPsd[iDet] + "_Y2XY", "TPC_eta, " + sPsdPsdName[iDet], Y2XY);
    a.AddCorrelation("TPC_eta_" + sPsdPsd[iDet] + "_Y2YX", "TPC_eta, " + sPsdPsdName[iDet], Y2YX);

    a.AddCorrelation("TPC_pT_" + sPsdPsd[iDet] + "_X2XX", "TPC_pT, " + sPsdPsdName[iDet], X2XX);
    a.AddCorrelation("TPC_pT_" + sPsdPsd[iDet] + "_X2YY", "TPC_pT, " + sPsdPsdName[iDet], X2YY);
    a.AddCorrelation("TPC_pT_" + sPsdPsd[iDet] + "_Y2XY", "TPC_pT, " + sPsdPsdName[iDet], Y2XY);
    a.AddCorrelation("TPC_pT_" + sPsdPsd[iDet] + "_Y2YX", "TPC_pT, " + sPsdPsdName[iDet], Y2YX);
  }

  // RS

//  a.AddCorrelation ("TPC_R2_TPC_R1_psiA_psiB", "TPC_R2, TPC_R1", psiA_psiB);
//  a.AddCorrelation ("TPC_R2_TPC_R1_psiA_psiB", "TPC_R2, TPC_R1", psi2A_psi2B);

  //END RS

}

void SimpleTask::Run() {
  Qn::CorrelationManager a(reader_);
  Configure(a);
  int events = 1;
  reader_->SetEntry(0);
  a.Initialize();
  while (reader_->Next()) {
    events++;
    a.UpdateEvent();
    if (!a.CheckEvent()) continue;
    a.FillCorrelations();
  }
  a.SaveToFile("corr.root");
  std::cout << "number of events: " << events << std::endl;
}

//
//
//  auto multiply = [](Qn::Profile a, Qn::Profile b) {
//    return a*b;
//  };
//
//  auto divide = [](Qn::Profile a, Qn::Profile b) {
//    return a/b;
//  };
//
//  auto sqrt = [](Qn::Profile a) {
//    return a.Sqrt();
//  };
//
//  auto add = [](Qn::Profile a, Qn::Profile b) {
//    return a + b;
//  };
//
//  auto rvatpcvc = tpcva.Apply(vavc, multiply).Apply(tpcvc, divide).Map(sqrt);
//  auto v2tpcva = tpcva.Apply(rvatpcvc, divide);


std::unique_ptr<TChain> SimpleTask::MakeChain(std::string filename, std::string treename) {
  std::unique_ptr<TChain> chain(new TChain(treename.data()));
  chain->AddFile(filename.data());

  std::cout << "Number of entries = " << chain->GetEntries() << std::endl;

//   std::ifstream in;
//   in.open(filename);
//   std::string line;
//   std::cout << "files in TChain:" << "\n";
//   while ((in >> line).good()) {
//     if (!line.empty()) {
//       chain->AddFile(line.data());
//       std::cout << line << std::endl;
//     }
//   }
  return chain;
}

