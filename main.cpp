#include <iostream>
#include <vector>
#include <random>
#include <TSystem.h>
#include <TROOT.h>
#include <array>
#include "Base/DataContainer.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "Correlation/Correlation.h"
#include "SimpleTask.h"
#include "Base/Stats.h"
#include "TestTask.h"
#include <iomanip>
#include <chrono>


int main(int argc, char **argv) {
  auto start = std::chrono::system_clock::now();
//   ROOT::EnableImplicitMT(20);
//    argv [1] = "correct";
//    argv [2] = "/home/ogolosov/Desktop/analysis/NA49_data/fileList.txt";
//    argv [2] = "/home/ogolosov/Desktop/analysis/NA49_data/shortList.txt";
//    argv [3] = "dfdf";
//    argv [3] = "calib.root";
//    argv [4] = "/home/ogolosov/Desktop/analysis/tpc_centr.root";
//    argv [1] = "analysis";
//    argv [2] = "qn_0.root";

  const bool issim = false;
//  const std::string setup = "na61";
  const std::string setup = "na49";
	TString partname = "piminus";	

  if (strcmp(argv[1], "correct")==0) {
//		TH2D *eff = (TH2D*) ( TFile::Open("/home/ogolosov/Desktop/analysis/NA49_data/efficiency/pbpb40_eff.root")->Get(partname + "/hCorrectionMapPtY_Integral") );
		TH2D *eff = (TH2D*) ( TFile::Open("/lustre/nyx/cbm/users/ogolosov/NA49_data/efficiency/pbpb40_eff.root")->Get(partname + "/hEfficiencyPtY_Integral") );
    Qn::TestTask task(argv[2], argv[3], argv[4]);
    task.SetSetup(setup);
		task.SetEff(eff);
    task.SetIsSim(issim);
    task.Run();
  }
  if (strcmp(argv[1], "analysis")==0) {
    SimpleTask st(argv[2], "tree");
    st.SetSetup(setup);
    st.SetIsSim(issim);
    st.Run();
  }
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cout << "elapsed time: " << elapsed_seconds.count() << " s\n";
  return 0;
}
