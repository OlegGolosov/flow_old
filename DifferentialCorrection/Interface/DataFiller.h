//
// Created by Lukas Kreis on 17.01.18.
//

#ifndef FLOW_DATAFILLER_H
#define FLOW_DATAFILLER_H

#include "TList.h"
#include "Base/DataContainer.h"
#include "DifferentialCorrection/Detector.h"
#include "DifferentialCorrection/Interface/VarManager.h"
#include "VarManager.h"

#include "DataTreeEvent.h"
#include "CentralityManager.h"

namespace Qn {
namespace Differential {
namespace Interface {

class DataFiller {

 public:
  explicit DataFiller() = default;
  explicit DataFiller(DataTreeEvent* event) : event_(event) {}

 void Fill(std::map<std::string, Detector> &detectors) const;

  void FillTrackingDetector(Qn::Detector &detector, const DataTreeEvent &event, const std::string subevent) const;
  void FillMCTrackingDetector(Qn::Detector &detector, const DataTreeEvent &event,  const bool isPidCut) const;

  void FillPSD(Qn::Detector &detector, const DataTreeEvent &event, const int ipsd) const ;
  void FillPsi(Qn::Detector &detector, const DataTreeEvent &event) const;

  void SetSetup(std::string setup) { setup_ = setup; }
  void SetIsSim(bool is=true) { issim_ = is; }

//   void SetCentrality(CentralityManager *c) { centr_ = c; }

private:

  DataTreeEvent* event_ {nullptr};
  std::string setup_ {"cbm"};
  bool issim_ {true};

//   CentralityManager *centr_;


  const std::vector<std::vector<int>> cbmpsd_ = {
  { 19, 20, 25, 26},
  { 12, 13, 14, 15, 18, 21, 24, 27, 30, 31, 32, 33},
  { 1,2,3,4,5,6,7,8,9,10,11,16,17,22,23,28,29,34,35,36,37,38,39,40,41,42,43,44} };

  const std::vector<std::vector<int>> cbmoldpsd_ = {
  {18, 19, 26, 27},
  {9, 10, 11, 12, 17, 20, 33, 34, 35, 36, 25, 28},
  {1,2,3,4,5,6,7,8,13,14,15,16,21,22,23,24,29,30,31,32,37,38,39,40,41,42,43,44} };

  const std::vector<std::vector<int>> cbmpsd52_ = {
  {1,2,3,4,5,6,7,8,9,10,11,12},
  {24,25,26,27,30,31,34,35,38,39,40,41 },
  {13,14,15,16,17,18,19,20,21,22,23,28,29,32,33,36,37,42,43,44,45,46,47,48,49,50,51,52} };

  const std::vector<std::vector<int>> na61psd_ = {
   {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},
   {17,18,19,20,21,22,23,24,25,26,27,28},
   {29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44} };

  const std::vector<std::vector<int>> na49veto_ = {
   {1,2,3,4},
   {1,2,3,4},
   {1,2,3,4} };


};

}
}
}
#endif //FLOW_DATAFILLER_H
