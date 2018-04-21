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


class qa_file_;
namespace Qn {

TestTask::TestTask(std::string filelist, std::string incalib, std::string centrality) :
    in_tree_(this->MakeChain(filelist, "DataTree")),
    out_file_(new TFile("qn.root", "RECREATE")),
    in_calibration_file_(new TFile(incalib.data(), "READ")),
    out_calibration_file_(new TFile("calib.root", "RECREATE")),
    out_tree_(nullptr),
    out_tree_raw(nullptr),
    event_(nullptr),
    write_tree_(true)
{
  centr_ = new CentralityManager;
  centr_->LoadCentalityDataFile(centrality);

  event_ = new DataTreeEvent();
  in_tree_->SetBranchAddress("DTEvent", &event_);

  out_file_->cd();
  std::unique_ptr<TTree> treeraw(new TTree("datatree", "datatree"));
  std::unique_ptr<TTree> tree(new TTree("tree", "tree"));
  out_tree_ = std::move(tree);
  out_tree_raw = std::move(treeraw);
	qa_file_ = new TFile ("qa.root", "RECREATE");
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
    if ( setup_ == "na49" && !Cuts::isGoodEvent (*event_, energy_, 0, 0, 0, 1, 0, 0) ) continue;
    nGoodEvents++;
    Process();
  }
  std::cout << "\n" << nGoodEvents << " good events from " << nEntries << std::endl;
  Finalize();
}


void TestTask::InitializeQA(std::string detectorName, DetectorType type)
{
	TDirectory *dir = qa_file_ -> mkdir (detectorName.c_str ());
	dir -> cd ();
	std::vector <TH1*> *h1 = new std::vector <TH1*>;
	std::vector <TH2*> *h2 = new std::vector <TH2*>;
	
	if (type == DetectorType::Track)
	{
		h2 -> push_back (new TH2F (Form ("h2ypt_%s", detectorName.c_str ()),  Form ("pt:y (%s);#it{y};p_{T}", detectorName.c_str ()), 500, -1., 3., 500, 0., 2.5));
		h2 -> push_back (new TH2F (Form ("h2phipt_%s", detectorName.c_str ()),  Form ("pt:phi (%s);#phi;p_{T}", detectorName.c_str ()), 500, -3.15, 3.15, 500, 0., 2.5));
		h2 -> push_back (new TH2F (Form ("h2phiy_%s", detectorName.c_str ()),  Form ("phi:y (%s);#phi;#it{y}", detectorName.c_str ()), 500, -3.15, 3.15, 500, -1., 3.));
		h2 -> push_back (new TH2F (Form ("h2dEdx_%s", detectorName.c_str ()),  Form ("dEdx:log(10*p) (%s);log(10*p);dEdx", detectorName.c_str ()), 500, -10., 10., 500, 0., 4.));
		h2 -> push_back (new TH2F (Form ("h2centMult%s", detectorName.c_str ()),  Form ("mult:cent (%s);centrality class;subevent multiplicity", detectorName.c_str ()), 6, 0, 6, 100, 0, 100));
		
	}
	if (type == DetectorType::Channel)
	{
		h2 -> push_back (new TProfile2D (Form ("p2modPosEnergy_%s", detectorName.c_str ()), Form ("module position vs energy (%s);x;y", detectorName.c_str ()), 150, -150, 150, 300, -150, 150));
		h2 -> push_back (new TH2F (Form ("h2centEsum_%s", detectorName.c_str ()), Form ("Energy sum vs centrality (%s);centrality class;#sum E", detectorName.c_str ()), 6, 0, 6, 900, 0, 18000));
		h2 -> push_back (new TH2F (Form ("h2centEveto_%s", detectorName.c_str ()), "Centrality vs Eveto;centrality class;E_{VCAL}", 6, 0, 6, 450, 0, 9000));
		h2 -> push_back (new TH2F (Form ("h2EvetoEsum_%s", detectorName.c_str ()), Form ("Energy sum vs Eveto (%s);E_{VCAL};#sum E", detectorName.c_str ()), 450, 0, 9000, 900, 0, 18000));
	}
	
	hist1.insert(std::make_pair (detectorName, h1));
	hist2.insert(std::make_pair (detectorName, h2));
}

void TestTask::Initialize() {
  using Axes = std::vector<Qn::Axis>;

  Axis yaxis("Rapidity", 17, -1.0, 2.4);
  Axis ptaxis("Pt", { 0., .2, .4, .6, .8, 1., 1.2, 1.4, 1.8, 2.2, 2.6, 3.0 } );

  //40 AGeV
  const float Ebeam = 8.32e3;
  std::vector <float> eVetoBins ({0., 0.169 * Ebeam, 0.314 * Ebeam, 0.509 * Ebeam, 0.66 * Ebeam, 0.778 * Ebeam, 9.e3});
  std::vector <float> multBins5 ({0, 2.6, 4.4, 6.6, 9.9, 14.5, 20.4, 28.3, 38.1, 50.2, 64.7,
                                81.9, 102.1, 125.0, 152.1, 183.1, 218.5, 259.9, 307.3, 364.2, 510});
  std::vector <float> multBins10 ({0, 4.4, 9.9, 20.4, 38.1, 64.7, 102.1, 152.1, 218.5, 307.3, 510});
  std::vector <float> centAxis ({0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0});
	
	
  //40 AGeV

//  //158 AGeV
//  const float Ebeam = 32.86e3;
//  std::vector <float> eVetoBins ({0., 0.251 * Ebeam, 0.399 * Ebeam, 0.576 * Ebeam, 0.709 * Ebeam, 0.797 * Ebeam, 33.e3});
//  //158 AGeV

  Axis multaxis("Multiplicity", multBins10);
  Axis eVetoaxis("Eveto", eVetoBins);
  Axes tpcaxes = {ptaxis, yaxis};

  auto confPsd = [](QnCorrectionsDetectorConfigurationBase *config) {
    config->SetQVectorNormalizationMethod(QnCorrectionsQnVector::QVNORM_QoverM);
    config->AddCorrectionOnQnVector(new QnCorrectionsQnVectorRecentering());
    auto rescale = new QnCorrectionsQnVectorTwistAndRescale();
    rescale->SetApplyTwist(true);
    rescale->SetApplyRescale(true);
    rescale->SetTwistAndRescaleMethod(QnCorrectionsQnVectorTwistAndRescale::TWRESCALE_doubleHarmonic);
//    config->AddCorrectionOnQnVector(rescale);
  };

  auto confTracks = [](QnCorrectionsDetectorConfigurationBase *config) {
    config->SetQVectorNormalizationMethod(QnCorrectionsQnVector::QVNORM_QoverM); // SP
//    config->SetQVectorNormalizationMethod(QnCorrectionsQnVector::QVNORM_QoverQlength); // EP
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
  manager.AddVariable("Eveto", VAR::Variables::kEveto);
  manager.AddVariable("RunNumber", VAR::Variables::kNRun);
  manager.AddVariable("Pt", VAR::Variables::kPt);
  manager.AddVariable("Eta", VAR::Variables::kEta);
  manager.AddVariable("Rapidity", VAR::Variables::kRapidity);
  manager.AddVariable("Charge", VAR::Variables::kCharge);

  int psd_size[3];
  if (setup_ == "na61" ) {psd_size[0] = 16; psd_size[1] = 12; psd_size[2] = 16;}
  if (setup_ == "na49" ) {psd_size[0] = 4; psd_size[1] = 120; psd_size[2] = 120;}
  if (setup_ == "cbm" ) {psd_size[0] = 4; psd_size[1] = 12; psd_size[2] = 28;}
  if (setup_ == "cbm52") {psd_size[0] = 12; psd_size[1] = 12; psd_size[2] = 28;}

  manager.AddDetector("PSD1", DetectorType::Channel, psd_size[0]);
  manager.AddDetector("PSD2", DetectorType::Channel, psd_size[1]);
  manager.AddDetector("PSD3", DetectorType::Channel, psd_size[2]);
  manager.AddDetector("TPC_1", DetectorType::Track);
  manager.AddDetector("TPC_2", DetectorType::Track);
  manager.AddDetector("TPC_3", DetectorType::Track);
  manager.AddDetector("TPC_3", DetectorType::Track);
  manager.AddDetector("TPC_a_1", DetectorType::Track);
  manager.AddDetector("TPC_b_1", DetectorType::Track);
  manager.AddDetector("TPC_a_2", DetectorType::Track);
  manager.AddDetector("TPC_b_2", DetectorType::Track);
  manager.AddDetector("TPC_pt", DetectorType::Track, {ptaxis});
  manager.AddDetector("TPC_y", DetectorType::Track, {yaxis});
  manager.AddDetector("TPC_pt_a_1", DetectorType::Track, {ptaxis});
  manager.AddDetector("TPC_y_a_1", DetectorType::Track, {yaxis});
  manager.AddDetector("TPC_pt_a_2", DetectorType::Track, {ptaxis});
  manager.AddDetector("TPC_y_a_2", DetectorType::Track, {yaxis});
  manager.AddDetector("TPC_pt_b_1", DetectorType::Track, {ptaxis});
  manager.AddDetector("TPC_y_b_1", DetectorType::Track, {yaxis});
  manager.AddDetector("TPC_pt_b_2", DetectorType::Track, {ptaxis});
  manager.AddDetector("TPC_y_b_2", DetectorType::Track, {yaxis});

  if (issim_)
  {
    manager.AddDetector("MC_pT", DetectorType::Track, {ptaxis});
    manager.AddDetector("MC_eta", DetectorType::Track, {yaxis});
    manager.AddDetector("PSI", DetectorType::Track); // check if the third argument is missing
  }
  manager.SetCorrectionSteps("PSD1", confPsd);
  manager.SetCorrectionSteps("PSD2", confPsd);
  manager.SetCorrectionSteps("PSD3", confPsd);
  manager.SetCorrectionSteps("TPC_1", confTracks);
  manager.SetCorrectionSteps("TPC_2", confTracks);
  manager.SetCorrectionSteps("TPC_3", confTracks);
  manager.SetCorrectionSteps("TPC_a_1", confTracks);
  manager.SetCorrectionSteps("TPC_b_1", confTracks);
  manager.SetCorrectionSteps("TPC_a_2", confTracks);
  manager.SetCorrectionSteps("TPC_b_2", confTracks);
  manager.SetCorrectionSteps("TPC_pt", confTracks);
  manager.SetCorrectionSteps("TPC_y", confTracks);
  manager.SetCorrectionSteps("TPC_pt_a_1", confTracks);
  manager.SetCorrectionSteps("TPC_y_a_1", confTracks);
  manager.SetCorrectionSteps("TPC_pt_a_2", confTracks);
  manager.SetCorrectionSteps("TPC_y_a_2", confTracks);
  manager.SetCorrectionSteps("TPC_pt_b_1", confTracks);
  manager.SetCorrectionSteps("TPC_y_b_1", confTracks);
  manager.SetCorrectionSteps("TPC_pt_b_2", confTracks);
  manager.SetCorrectionSteps("TPC_y_b_2", confTracks);
	
  InitializeQA("PSD1", DetectorType::Channel);
  InitializeQA("PSD2", DetectorType::Channel);
  InitializeQA("PSD3", DetectorType::Channel);
  InitializeQA("TPC_1", DetectorType::Track);
  InitializeQA("TPC_2", DetectorType::Track);
  InitializeQA("TPC_3", DetectorType::Track);
  InitializeQA("TPC_a_1", DetectorType::Track);
  InitializeQA("TPC_b_1", DetectorType::Track);
  InitializeQA("TPC_a_2", DetectorType::Track);
  InitializeQA("TPC_b_2", DetectorType::Track);
  InitializeQA("TPC_pt", DetectorType::Track);
  InitializeQA("TPC_y", DetectorType::Track);
  InitializeQA("TPC_pt_a_1", DetectorType::Track);
  InitializeQA("TPC_y_a_1", DetectorType::Track);
  InitializeQA("TPC_pt_a_2", DetectorType::Track);
  InitializeQA("TPC_y_a_2", DetectorType::Track);
  InitializeQA("TPC_pt_b_1", DetectorType::Track);
  InitializeQA("TPC_y_b_1", DetectorType::Track);
  InitializeQA("TPC_pt_b_2", DetectorType::Track);
  InitializeQA("TPC_y_b_2", DetectorType::Track);
	

  if (issim_)
  {
    manager.SetCorrectionSteps("PSI", confPsi);
    manager.SetCorrectionSteps("MC_eta", confMC);
    manager.SetCorrectionSteps("MC_pT",  confMC);
  }

//  manager.AddCorrectionAxis(eVetoaxis);
//  manager.SetEventVariable("Eveto");
//  manager.AddHist1D("Eveto", eVetoBins);

//  manager.AddCorrectionAxis(multaxis);
//  manager.SetEventVariable("Multiplicity");
//  manager.AddHist1D("Multiplicity", multBins10);

//  manager.AddCorrectionAxis({"Centrality", 10, 0, 100});
//  manager.SetEventVariable("Centrality");
//  manager.AddHist1D("Centrality", 20,0.,100.);
	int numberOfRuns = maxRunNumber - minRunNumber + 1;
	maxRunNumber += 1;
  manager.AddCorrectionAxis({"Centrality", 6, 0, 6});
//  manager.AddCorrectionAxis({"RunNumber", numberOfRuns, minRunNumber, maxRunNumber});
  manager.SetEventVariable("Centrality");
  manager.SetEventVariable("RunNumber");
  manager.AddHist1D("Centrality", 6, 0, 6);
//  manager.AddHist1D({"RunNumber", numberOfRuns, minRunNumber, maxRunNumber});

  manager.SaveQVectorsToTree(*out_tree_);
  manager.SaveEventVariablesToTree(*out_tree_);

  manager.Initialize(in_calibration_file_);
}

void TestTask::Process() {
  manager.Reset();

	VarManager::FillEventInfo(*event_, manager.GetVariableContainer(), setup_, centr_);
  Differential::Interface::DataFiller filler ( event_, manager.GetVariableContainer(), hist1, hist2);

//  filler.SetCentrality(centr_);
  filler.SetSetup(setup_);
  filler.SetIsSim(issim_);

  manager.FillDataToFramework(filler);

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
	qa_file_ -> Write ();
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
	minRunNumber = chain -> GetMinimum("fRunId");
	maxRunNumber = chain -> GetMaximum("fRunId");
  std::cout << "Number of entries = " << chain->GetEntries() << std::endl;
  std::cout << "Fist run = " << minRunNumber << std::endl;
  std::cout << "Last run = " << maxRunNumber << std::endl;
	
  return chain;
}

}
