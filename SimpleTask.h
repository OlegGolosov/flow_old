//
// Created by Lukas Kreis on 13.11.17.
//

#ifndef FLOW_SIMPLETASK_H
#define FLOW_SIMPLETASK_H

#include <TChain.h>
#include <TTreeReader.h>
#include "Base/DataContainer.h"
#include "Correlation/Correlation.h"
#include "Correlation/CorrelationManager.h"


class SimpleTask {
 public:
  SimpleTask() = default;
  SimpleTask(std::string filelist, std::string treename);

  void Configure(Qn::CorrelationManager &manager);
  void Run();

 void SetIsSim(bool is=true) { issim_ = is; }
 void SetSetup(std::string setup) { setup_ = setup; }
  
 std::string GetSetup() const { return setup_; }
 bool GetIsSim() const { return issim_; }

  
 private:
  std::unique_ptr<TTree> in_tree_;
  std::shared_ptr<TTreeReader> reader_;

  std::string setup_{"cbm"};
  bool issim_{true};
  /**
   * Make TChain from file list
   * @param filename name of file containing paths to root files containing the input trees
   * @return Pointer to the TChain
   */
  std::unique_ptr<TChain> MakeChain(std::string filename, std::string treename);
};

#endif //FLOW_SIMPLETASK_H
