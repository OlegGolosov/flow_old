//
// Created by Lukas Kreis on 29.06.17.
//

#include <iostream>
#include <QnCorrections/QnCorrectionsLog.h>
#include <random>
#include <vector>
#include <THnSparse.h>
#include "TestTask.h"

#include "cuts/isGoodEvent.h"


namespace Qn {

TestTask::TestTask(std::string filelist, std::string incalib, std::string centrality) :
    in_tree_(this->MakeChain(filelist, "DataTree")),
    out_file_(new TFile("qn.root", "RECREATE")),
    in_calibration_file_(new TFile(incalib.data(), "READ")),
    out_calibration_file_(new TFile("calib.root", "RECREATE")),
    out_tree_(nullptr),
    out_tree_raw(nullptr),
    event_(nullptr),
    write_tree_(true) {

  centr_ = new CentralityManager;
  centr_->LoadCentalityDataFile(centrality);

  event_ = new DataTreeEvent();
  in_tree_->SetBranchAddress("DTEvent", &event_);

  out_file_->cd();
  std::unique_ptr<TTree> treeraw(new TTree("datatree", "datatree"));
  std::unique_ptr<TTree> tree(new TTree("tree", "tree"));
  out_tree_ = std::move(tree);
  out_tree_raw = std::move(treeraw);
}

void TestTask::Run() {
  Initialize();
  QnCorrectionsSetTracingLevel(kError);
  std::cout << "Processing..." << std::endl;
  int nEntries = in_tree_->GetEntries();
  int nGoodEvents = 0;
  for (int i = 0; i < nEntries; i++)
  {
//    std::cout << "\rEvent " << i + 1 << " from " << nEntries << "\tGood: " << nGoodEvents;
    in_tree_->GetEntry(i);
    if ( setup_ == "na61" && !Cuts::isGoodEvent (*event_) ) continue;
    if ( setup_ == "na49" && !Cuts::isGoodEvent (*event_, energy_, 0, 0, 0, 1, 0, 1) ) continue;
    nGoodEvents++;
    Process();
  }
  std::cout << "\n" << nGoodEvents << " good events from " << nEntries << std::endl;
  Finalize();
}

void TestTask::Initialize() {
  using Axes = std::vector<Qn::Axis>;

  Axis etaaxis("Eta", 20, 1.4, 5.0);
  Axis yaxis("Rapidity", 15, -0.6, 2.4);
  Axis ptaxis("Pt", { 0., .2, .4, .6, .8, 1., 1.2, 1.4, 1.8, 2.2, 2.6, 3.0 } );
  std::vector <float> multBins ({2.6, 4.4, 6.6, 9.9, 14.5, 20.4, 28.3, 38.1, 50.2, 64.7,
                                81.9, 102.1, 125.0, 152.1, 183.1, 218.5, 259.9, 307.3, 364.2});

  Axis multaxis("Multiplicity", multBins );
  Axes tpcaxes = {ptaxis, etaaxis};

  auto confPsd = [](QnCorrectionsDetectorConfigurationBase *config) {
    config->SetQVectorNormalizationMethod(QnCorrectionsQnVector::QVNORM_QoverM);
    config->AddCorrectionOnQnVector(new QnCorrectionsQnVectorRecentering());
    auto rescale = new QnCorrectionsQnVectorTwistAndRescale();
    rescale->SetApplyTwist(true);
    rescale->SetApplyRescale(true);
    rescale->SetTwistAndRescaleMethod(QnCorrectionsQnVectorTwistAndRescale::TWRESCALE_doubleHarmonic);
    config->AddCorrectionOnQnVector(rescale);
  };

  auto confTracks = [](QnCorrectionsDetectorConfigurationBase *config) {
    config->SetQVectorNormalizationMethod(QnCorrectionsQnVector::QVNORM_QoverM);
    config->AddCorrectionOnQnVector(new QnCorrectionsQnVectorRecentering());
    auto rescale = new QnCorrectionsQnVectorTwistAndRescale();
    rescale->SetApplyTwist(true);
    rescale->SetApplyRescale(true);
    rescale->SetTwistAndRescaleMethod(QnCorrectionsQnVectorTwistAndRescale::TWRESCALE_doubleHarmonic);
    config->AddCorrectionOnQnVector(rescale);
};

  auto confPsi = [](QnCorrectionsDetectorConfigurationBase *config) {
    config->SetQVectorNormalizationMethod(QnCorrectionsQnVector::QVNORM_QoverQlength);
};

  auto confMC = [](QnCorrectionsDetectorConfigurationBase *config) {
    config->SetQVectorNormalizationMethod(QnCorrectionsQnVector::QVNORM_QoverM);
};

  manager.AddVariable("Centrality", VAR::Variables::kCentrality);
  manager.AddVariable("Multiplicity", VAR::Variables::kMultiplicity);
  manager.AddVariable("Pt", VAR::Variables::kPt);
  manager.AddVariable("Eta", VAR::Variables::kEta);
  manager.AddVariable("Rapidity", VAR::Variables::kRapidity);
  manager.AddVariable("Charge", VAR::Variables::kCharge);

  int psd_size[3];
  if (setup_ == "na61" ) psd_size[0] = 16; psd_size[1] = 12; psd_size[2] = 16;
  if (setup_ == "na49" ) psd_size[0] = 4; psd_size[1] = 120; psd_size[2] = 120;
  if (setup_ == "cbm" ) psd_size[0] = 4; psd_size[1] = 12; psd_size[2] = 28;
  if (setup_ == "cbm52" ) psd_size[0] = 12; psd_size[1] = 12; psd_size[2] = 28;

  manager.AddDetector("TPC_pT", DetectorType::Track, {ptaxis});
  manager.AddDetector("TPC_eta", DetectorType::Track, {yaxis});
  manager.AddDetector("TPC_R1", DetectorType::Track);
  manager.AddDetector("TPC_R2", DetectorType::Track);
  manager.AddDetector("PSD1", DetectorType::Channel, psd_size[0]);
  manager.AddDetector("PSD2", DetectorType::Channel, psd_size[1]);
  manager.AddDetector("PSD3", DetectorType::Channel, psd_size[2]);

  if (issim_)
  {
    manager.AddDetector("MC_pT", DetectorType::Track, {ptaxis});
    manager.AddDetector("MC_eta", DetectorType::Track, {yaxis});
    manager.AddDetector("PSI", DetectorType::Track);
  }
  manager.SetCorrectionSteps("PSD1", confPsd);
  manager.SetCorrectionSteps("PSD2", confPsd);
  manager.SetCorrectionSteps("PSD3", confPsd);
  manager.SetCorrectionSteps("TPC_pT", confTracks);
  manager.SetCorrectionSteps("TPC_eta", confTracks);
  manager.SetCorrectionSteps("TPC_R1", confTracks);
  manager.SetCorrectionSteps("TPC_R2", confTracks);

  if (issim_)
  {
    manager.SetCorrectionSteps("PSI", confPsi);
    manager.SetCorrectionSteps("MC_eta", confMC);
    manager.SetCorrectionSteps("MC_pT",  confMC);
  }

  manager.AddCorrectionAxis(multaxis);
  manager.SetEventVariable("Multiplicity");
  manager.AddHist1D("Multiplicity", multBins);

//  manager.AddCorrectionAxis({"Centrality", 10, 0, 100});
//  manager.SetEventVariable("Centrality");
//  manager.AddHist1D("Centrality", 20,0.,100.);


  manager.SaveQVectorsToTree(*out_tree_);
  manager.SaveEventVariablesToTree(*out_tree_);

  manager.Initialize(in_calibration_file_);
}

void TestTask::Process() {
  manager.Reset();

  Differential::Interface::DataFiller filler ( event_ );

//  filler.SetCentrality(centr_);
  filler.SetSetup(setup_);
  filler.SetIsSim(issim_);

  manager.FillDataToFramework(filler);

  VarManager::FillEventInfo(*event_, manager.GetVariableContainer(), setup_, centr_);

  manager.Process();
  out_tree_->Fill();
  out_tree_raw->Fill();
}

void TestTask::Finalize() {
  manager.Finalize();
  out_calibration_file_->cd();
  manager.SaveCorrectionHistograms();
  out_file_->cd();
  if (write_tree_) {
    out_file_->Write();
    std::cout << "Output file written." << std::endl;
  }
}

std::unique_ptr<TChain> TestTask::MakeChain(std::string filename, std::string treename) {
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







}
