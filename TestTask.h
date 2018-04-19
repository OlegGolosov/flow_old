//
// Created by Lukas Kreis on 29.06.17.
//

#ifndef FLOW_QNTestTask_H
#define FLOW_QNTestTask_H

#include <vector>
#include <array>
#include <random>
#include "QnCorrections/QnCorrectionsProfile3DCorrelations.h"
#include "QnCorrections/QnCorrectionsProfileCorrelationComponents.h"
#include "QnCorrections/QnCorrectionsDetectorConfigurationChannels.h"
#include "QnCorrections/QnCorrectionsDetectorConfigurationBase.h"
#include <QnCorrections/QnCorrectionsDetectorConfigurationTracks.h>
#include <QnCorrections/QnCorrectionsQnVectorRecentering.h>
#include <QnCorrections/QnCorrectionsQnVectorTwistAndRescale.h>
#include <QnCorrections/QnCorrectionsCutSetBit.h>
#include <QnCorrections/QnCorrectionsCutWithin.h>
#include <QnCorrections/QnCorrectionsInputGainEqualization.h>
#include <QnCorrections/QnCorrectionsQnVectorAlignment.h>
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TTreeReader.h"

#include "QnCorrections/QnCorrectionsManager.h"
#include "Base/DataContainer.h"
#include "DifferentialCorrection/EventInfo.h"
#include "DifferentialCorrection/CorrectionManager.h"

#include "DataTreeEvent.h"
#include "CentralityManager.h"


#define VAR VarManager

namespace Qn {
/**
 * Qn vector analysis TestTask. It is to be configured by the user.
 * @brief TestTask for analysing qn vectors
 */
 
class TestTask {
 public:
  TestTask() = default;
  TestTask(std::string filelist, std::string incalib, std::string centrality);
  TestTask(std::array<std::shared_ptr<TFile>, 4> files);
  ~TestTask() = default;
  void Run();

 void SetIsSim(bool is=true) { issim_ = is; }
 void SetSetup(std::string setup) { setup_ = setup; }

 std::string GetSetup() const { return setup_; }
 bool GetIsSim() const { return issim_; }


private:
  /**
   * Initializes TestTask;
   */
  virtual void Initialize();
	
  void InitializeQA(std::string detectorName, DetectorType type);
  /**
   * Processes one event;
   */
  virtual void Process();
  /**
   * Finalizes TestTask. Called after processing is done.
   */
  virtual void Finalize();
	
  /**
   * Make TChain from file list
   * @param filename name of file containing paths to root files containing the input trees
   * @return Pointer to the TChain
   */
 virtual std::unique_ptr<TChain> MakeChain(std::string filename, std::string treename);

protected:
  std::unique_ptr<TTree> in_tree_;
  std::shared_ptr<TFile> out_file_;
  std::shared_ptr<TFile> in_calibration_file_;
  std::shared_ptr<TFile> out_calibration_file_;
  std::unique_ptr<TTree> out_tree_;
  std::unique_ptr<TTree> out_tree_raw;
  TFile *qa_file_;
	std::map <std::string, std::vector <TH1*>*> hist1;
	std::map <std::string, std::vector <TH2*>*> hist2;

  DataTreeEvent *event_;
  CentralityManager *centr_;

  Qn::CorrectionManager manager;
  bool write_tree_;
  bool issim_{true};
  std::string setup_{"cbm"};
  double energy_ {40};
};
}
#endif //FLOW_QNTASK_H
