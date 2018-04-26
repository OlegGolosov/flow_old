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
  auto XX = [](const std::vector<Qn::QVector> &a) {
    return 2*a[0].x(1)*a[1].x(1);
  };
  auto YY = [](const std::vector<Qn::QVector> &a) {
    return 2*a[0].y(1)*a[1].y(1);
  };
  auto XY = [](const std::vector<Qn::QVector> &a) {
    return 2*a[0].x(1)*a[1].y(1);
  };
  auto YX = [](const std::vector<Qn::QVector> &a) {
    return 2*a[0].y(1)*a[1].x(1);
  };
  auto XX_EP = [](const std::vector<Qn::QVector> &a) {
    return 2 * cos (atan2 (a[0].y(1), a[0].x(1))) * cos (atan2 (a[1].y(1), a[1].x(1)));
  };
  auto YY_EP = [](const std::vector<Qn::QVector> &a) {
    return 2 * sin (atan2 (a[0].y(1), a[0].x(1))) * sin (atan2 (a[1].y(1), a[1].x(1)));
  };
  auto XY_EP = [](const std::vector<Qn::QVector> &a) {
    return 2 * cos (atan2 (a[0].y(1), a[0].x(1))) * sin (atan2 (a[1].y(1), a[1].x(1)));
  };
  auto YX_EP = [](const std::vector<Qn::QVector> &a) {
    return 2 * sin (atan2 (a[0].y(1), a[0].x(1))) * cos (atan2 (a[1].y(1), a[1].x(1)));
  };
  auto X2X2_EP = [](const std::vector<Qn::QVector> &a) {
    return 2 * cos (atan2 (a[0].y(2), a[0].x(2))) * cos (atan2 (a[1].y(2), a[1].x(2)));
  };
  auto Y2Y2_EP = [](const std::vector<Qn::QVector> &a) {
    return 2 * sin (atan2 (a[0].y(2), a[0].x(2))) * sin (atan2 (a[1].y(2), a[1].x(2)));
  };
  auto X2Y2_EP = [](const std::vector<Qn::QVector> &a) {
    return 2 * cos (atan2 (a[0].y(2), a[0].x(2))) * sin (atan2 (a[1].y(2), a[1].x(2)));
  };
  auto Y2X2_EP = [](const std::vector<Qn::QVector> &a) {
    return 2 * sin (atan2 (a[0].y(2), a[0].x(2))) * cos (atan2 (a[1].y(2), a[1].x(2)));
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
//  auto psi1A_psi1B = [](const std::vector<Qn::QVector> &a) {
//    return acos (cos (atan2 (a[0].y(1), a[0].x(1)) - atan2 (a[1].y(1), a[1].x(1))));
//  };
//  auto psi2A_psi2B = [](const std::vector<Qn::QVector> &a) {
//    return acos (cos (0.5 * (atan2 (a[0].y(2), a[0].x(2)) - atan2 (a[1].y(2), a[1].x(2)))));
//  };

  a.AddDataContainer("PSD1");
  a.AddDataContainer("PSD2");
  a.AddDataContainer("PSD3");
  a.AddDataContainer("TPC_1");
  a.AddDataContainer("TPC_2");
  a.AddDataContainer("TPC_3");
	a.AddDataContainer("TPC_y");
  a.AddDataContainer("TPC_pt");
	
	//RS
  a.AddDataContainer("TPC_a_1");
  a.AddDataContainer("TPC_b_1");
  a.AddDataContainer("TPC_a_2");
  a.AddDataContainer("TPC_b_2");
  a.AddDataContainer("TPC_y_a_1");
  a.AddDataContainer("TPC_pt_a_1");
  a.AddDataContainer("TPC_y_b_1");
  a.AddDataContainer("TPC_pt_b_1");
  a.AddDataContainer("TPC_y_a_2");
  a.AddDataContainer("TPC_pt_a_2");
  a.AddDataContainer("TPC_y_b_2");
  a.AddDataContainer("TPC_pt_b_2");

  if (issim_)
  {
    a.AddDataContainer("MC_pT");
    a.AddDataContainer("MC_eta");
    a.AddDataContainer("PSI");
  }


  //40 AGeV
  const float Ebeam = 8.32e3;
  std::vector <float> deltaPsi2bins ({0., 0.5 * TMath::Pi(), TMath::Pi()});
  std::vector <float> deltaPsi10bins ({0., 0.314, 0.628, 0.942, 1.256, 1.57, 1.884, 2.198, 2.512, 2.826, 3.14});
	
  std::vector <float> eVetoBins ({0., 0.169 * Ebeam, 0.314 * Ebeam, 0.509 * Ebeam, 0.66 * Ebeam, 0.778 * Ebeam, 9.e3});
  std::vector <float> multBins5 ({0, 2.6, 4.4, 6.6, 9.9, 14.5, 20.4, 28.3, 38.1, 50.2, 64.7,
                                81.9, 102.1, 125.0, 152.1, 183.1, 218.5, 259.9, 307.3, 364.2, 510});
  std::vector <float> multBins10 ({0, 4.4, 9.9, 20.4, 38.1, 64.7, 102.1, 152.1, 218.5, 307.3, 510});
  //40 AGeV

//  //158 AGeV
//  const float Ebeam = 32.86e3;
//  std::vector <float> eVetoBins ({0., 0.251 * Ebeam, 0.399 * Ebeam, 0.576 * Ebeam, 0.709 * Ebeam, 0.797 * Ebeam, 33.e3});
//  //158 AGeV

//  a.AddEventVariable({"Centrality", {0., 5., 10., 15., 20., 25., 30., 35., 40, 45., 50., 55., 60., 65., 70., 80, 90, 100}});

//  a.AddEventVariable({"Eveto", eVetoBins});
  a.AddEventVariable({"Centrality", {0, 1, 2, 3, 4, 5, 6}});
	
//  a.AddEventVariable({"Multiplicity", multBins10});
//  a.AddFunction("TPC", Rebin);

  const std::string sDet[] = { "PSD1", "PSD2", "PSD3", "TPC_pt", "TPC_y", "TPC_a_1", "TPC_b_1", "TPC_1", "TPC_2", "TPC_3"};
  const std::string sMc[] = { "MC_pT", "MC_eta"};

  const std::string sTracks[] = { sDet[3], sDet[4], sDet[5], sDet[6], sDet[7], sDet[8], sDet[9] };
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

// RS 2 harmonics
  a.AddCorrelation( "TPC_a_1_TPC_b_1_XX", "TPC_a_1, TPC_b_1", XX_EP);
  a.AddCorrelation( "TPC_a_1_TPC_b_1_YY", "TPC_a_1, TPC_b_1", YY_EP);
  a.AddCorrelation( "TPC_a_1_TPC_b_1_XY", "TPC_a_1, TPC_b_1", XY_EP);
  a.AddCorrelation( "TPC_a_1_TPC_b_1_YX", "TPC_a_1, TPC_b_1", YX_EP);
//  a.AddCorrelation( "TPC_psi1A_psi1B", "TPC_a_1, TPC_b_1", psi1A_psi1B);
  a.AddCorrelation( "TPC_pt_a_1_TPC_b_1_XX", "TPC_pt_a_1, TPC_b_1", XX_EP);
  a.AddCorrelation( "TPC_pt_a_1_TPC_b_1_YY", "TPC_pt_a_1, TPC_b_1", YY_EP);
  a.AddCorrelation( "TPC_pt_a_1_TPC_b_1_XY", "TPC_pt_a_1, TPC_b_1", XY_EP);
  a.AddCorrelation( "TPC_pt_a_1_TPC_b_1_YX", "TPC_pt_a_1, TPC_b_1", YX_EP);
  a.AddCorrelation( "TPC_y_a_1_TPC_b_1_XX", "TPC_y_a_1, TPC_b_1", XX_EP);
  a.AddCorrelation( "TPC_y_a_1_TPC_b_1_YY", "TPC_y_a_1, TPC_b_1", YY_EP);
  a.AddCorrelation( "TPC_y_a_1_TPC_b_1_XY", "TPC_y_a_1, TPC_b_1", XY_EP);
  a.AddCorrelation( "TPC_y_a_1_TPC_b_1_YX", "TPC_y_a_1, TPC_b_1", YX_EP);
  a.AddCorrelation( "TPC_pt_b_1_TPC_a_1_XX", "TPC_pt_b_1, TPC_a_1", XX_EP);
  a.AddCorrelation( "TPC_pt_b_1_TPC_a_1_YY", "TPC_pt_b_1, TPC_a_1", YY_EP);
  a.AddCorrelation( "TPC_pt_b_1_TPC_a_1_XY", "TPC_pt_b_1, TPC_a_1", XY_EP);
  a.AddCorrelation( "TPC_pt_b_1_TPC_a_1_YX", "TPC_pt_b_1, TPC_a_1", YX_EP);
  a.AddCorrelation( "TPC_y_b_1_TPC_a_1_XX", "TPC_y_b_1, TPC_a_1", XX_EP);
  a.AddCorrelation( "TPC_y_b_1_TPC_a_1_YY", "TPC_y_b_1, TPC_a_1", YY_EP);
  a.AddCorrelation( "TPC_y_b_1_TPC_a_1_XY", "TPC_y_b_1, TPC_a_1", XY_EP);
  a.AddCorrelation( "TPC_y_b_1_TPC_a_1_YX", "TPC_y_b_1, TPC_a_1", YX_EP);
	
  a.AddCorrelation( "TPC_a_2_TPC_b_2_XX", "TPC_a_2, TPC_b_2", X2X2_EP);
  a.AddCorrelation( "TPC_a_2_TPC_b_2_YY", "TPC_a_2, TPC_b_2", Y2Y2_EP);
  a.AddCorrelation( "TPC_a_2_TPC_b_2_XY", "TPC_a_2, TPC_b_2", X2Y2_EP);
  a.AddCorrelation( "TPC_a_2_TPC_b_2_YX", "TPC_a_2, TPC_b_2", Y2X2_EP);
//  a.AddCorrelation( "TPC_psi2A_psi2B", "TPC_a_2, TPC_b_2", psi2A_psi2B);
  a.AddCorrelation( "TPC_pt_a_2_TPC_b_2_XX", "TPC_pt_a_2, TPC_b_2", X2X2_EP);
  a.AddCorrelation( "TPC_pt_a_2_TPC_b_2_YY", "TPC_pt_a_2, TPC_b_2", Y2Y2_EP);
  a.AddCorrelation( "TPC_pt_a_2_TPC_b_2_XY", "TPC_pt_a_2, TPC_b_2", X2Y2_EP);
  a.AddCorrelation( "TPC_pt_a_2_TPC_b_2_YX", "TPC_pt_a_2, TPC_b_2", Y2X2_EP);
  a.AddCorrelation( "TPC_y_a_2_TPC_b_2_XX", "TPC_y_a_2, TPC_b_2", X2X2_EP);
  a.AddCorrelation( "TPC_y_a_2_TPC_b_2_YY", "TPC_y_a_2, TPC_b_2", Y2Y2_EP);
  a.AddCorrelation( "TPC_y_a_2_TPC_b_2_XY", "TPC_y_a_2, TPC_b_2", X2Y2_EP);
  a.AddCorrelation( "TPC_y_a_2_TPC_b_2_YX", "TPC_y_a_2, TPC_b_2", Y2X2_EP);
  a.AddCorrelation( "TPC_pt_b_2_TPC_a_2_XX", "TPC_pt_b_2, TPC_a_2", X2X2_EP);
  a.AddCorrelation( "TPC_pt_b_2_TPC_a_2_YY", "TPC_pt_b_2, TPC_a_2", Y2Y2_EP);
  a.AddCorrelation( "TPC_pt_b_2_TPC_a_2_XY", "TPC_pt_b_2, TPC_a_2", X2Y2_EP);
  a.AddCorrelation( "TPC_pt_b_2_TPC_a_2_YX", "TPC_pt_b_2, TPC_a_2", Y2X2_EP);
  a.AddCorrelation( "TPC_y_b_2_TPC_a_2_XX", "TPC_y_b_2, TPC_a_2", X2X2_EP);
  a.AddCorrelation( "TPC_y_b_2_TPC_a_2_YY", "TPC_y_b_2, TPC_a_2", Y2Y2_EP);
  a.AddCorrelation( "TPC_y_b_2_TPC_a_2_XY", "TPC_y_b_2, TPC_a_2", X2Y2_EP);
  a.AddCorrelation( "TPC_y_b_2_TPC_a_2_YX", "TPC_y_b_2, TPC_a_2", Y2X2_EP);
	
// end RS 2 harmonics



  for (ushort iPsd=0; iPsd<3; ++iPsd)
  for (ushort iTrack=0; iTrack<7; ++iTrack)
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
		
    a.AddCorrelation(sPsdPsd[iDet] + "_XX", sPsdPsdName[iDet], XX_EP);
    a.AddCorrelation(sPsdPsd[iDet] + "_YY", sPsdPsdName[iDet], YY_EP);
    a.AddCorrelation(sPsdPsd[iDet] + "_XY", sPsdPsdName[iDet], XY_EP);
    a.AddCorrelation(sPsdPsd[iDet] + "_YX", sPsdPsdName[iDet], YX_EP);

    a.AddCorrelation("TPC_1_" + sPsdPsd[iDet] + "_X2XX", "TPC_1, " + sPsdPsdName[iDet], X2XX);
    a.AddCorrelation("TPC_1_" + sPsdPsd[iDet] + "_X2YY", "TPC_1, " + sPsdPsdName[iDet], X2YY);
    a.AddCorrelation("TPC_1_" + sPsdPsd[iDet] + "_Y2XY", "TPC_1, " + sPsdPsdName[iDet], Y2XY);
    a.AddCorrelation("TPC_1_" + sPsdPsd[iDet] + "_Y2YX", "TPC_1, " + sPsdPsdName[iDet], Y2YX);
		
    a.AddCorrelation("TPC_2_" + sPsdPsd[iDet] + "_X2XX", "TPC_2, " + sPsdPsdName[iDet], X2XX);
    a.AddCorrelation("TPC_2_" + sPsdPsd[iDet] + "_X2YY", "TPC_2, " + sPsdPsdName[iDet], X2YY);
    a.AddCorrelation("TPC_2_" + sPsdPsd[iDet] + "_Y2XY", "TPC_2, " + sPsdPsdName[iDet], Y2XY);
    a.AddCorrelation("TPC_2_" + sPsdPsd[iDet] + "_Y2YX", "TPC_2, " + sPsdPsdName[iDet], Y2YX);
		
    a.AddCorrelation("TPC_3_" + sPsdPsd[iDet] + "_X2XX", "TPC_3, " + sPsdPsdName[iDet], X2XX);
    a.AddCorrelation("TPC_3_" + sPsdPsd[iDet] + "_X2YY", "TPC_3, " + sPsdPsdName[iDet], X2YY);
    a.AddCorrelation("TPC_3_" + sPsdPsd[iDet] + "_Y2XY", "TPC_3, " + sPsdPsdName[iDet], Y2XY);
    a.AddCorrelation("TPC_3_" + sPsdPsd[iDet] + "_Y2YX", "TPC_3, " + sPsdPsdName[iDet], Y2YX);

    a.AddCorrelation("TPC_y_" + sPsdPsd[iDet] + "_X2XX", "TPC_y, " + sPsdPsdName[iDet], X2XX);
    a.AddCorrelation("TPC_y_" + sPsdPsd[iDet] + "_X2YY", "TPC_y, " + sPsdPsdName[iDet], X2YY);
    a.AddCorrelation("TPC_y_" + sPsdPsd[iDet] + "_Y2XY", "TPC_y, " + sPsdPsdName[iDet], Y2XY);
    a.AddCorrelation("TPC_y_" + sPsdPsd[iDet] + "_Y2YX", "TPC_y, " + sPsdPsdName[iDet], Y2YX);

    a.AddCorrelation("TPC_pt_" + sPsdPsd[iDet] + "_X2XX", "TPC_pt, " + sPsdPsdName[iDet], X2XX);
    a.AddCorrelation("TPC_pt_" + sPsdPsd[iDet] + "_X2YY", "TPC_pt, " + sPsdPsdName[iDet], X2YY);
    a.AddCorrelation("TPC_pt_" + sPsdPsd[iDet] + "_Y2XY", "TPC_pt, " + sPsdPsdName[iDet], Y2XY);
    a.AddCorrelation("TPC_pt_" + sPsdPsd[iDet] + "_Y2YX", "TPC_pt, " + sPsdPsdName[iDet], Y2YX);
  }
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

