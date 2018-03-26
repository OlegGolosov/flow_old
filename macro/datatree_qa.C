#include <iostream>
#include <iomanip>
#include <chrono>
#include <TROOT.h>

#include "datatreeqa/DataTreeQA.h"


int main(int argc, char **argv) {
  auto start = std::chrono::system_clock::now();
//   ROOT::EnableImplicitMT(20);

  bool issim = false;
  bool isna61 = false;
  bool isna49 = false;
  
  if (strcmp(argv[2], "na61")==0)
  {
    isna61 = true;
  }
  else if (strcmp(argv[2], "na49")==0)
  {
    isna49 = true;
  }
  else if (strcmp(argv[2], "na61sim")==0)
  {
    isna61 = true;
    issim = true;
  }
  
  
  std::cout << argv[2] << std::endl;
  std::cout << isna61 << std::endl;
  
  DataTreeQA qa(argv[1]);
  
  qa.SetIsSim(issim);
  qa.SetIsNA61(isna61);
  qa.SetIsNA49(isna49);
  
  qa.RunQA(10000);
  
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cout << "elapsed time: " << elapsed_seconds.count() << " s\n";
  return 0;
}
