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

namespace Qn {
namespace Differential {
namespace Interface {

class DataFiller {

 public:
  explicit DataFiller() = default;
  explicit DataFiller(DataTreeEvent* event) : event_(event) {}
 
 void Fill(std::map<std::string, Detector> &detectors) {
//     FillDetector(detectors.at("DET1"));
    FillPSD(detectors.at("PSD1"), *event_, 0);
    FillPSD(detectors.at("PSD2"), *event_, 1);
    FillPSD(detectors.at("PSD3"), *event_, 2);
  }

  
//   void FillDetector(Qn::Detector &detector) {
//     const std::array<double, 10> X = {{-1.75, 1.75, -1.75, 1.75}};
//     const std::array<double, 10> Y = {{-1.75, -1.75, 1.75, 1.75}};
//     auto &datacontainer = detector.GetDataContainer();
//     auto values = new float[VarManager::Values::kNMax];
//     VarManager::FillEventInfo(values);
//     for (u_short ich = 0; ich < 5; ich++) {
//       double weight = values[ich+VarManager::Values::kSignal];
//       if (weight > 100) {
//         datacontainer->CallOnElement([ich, Y, X, weight](std::vector<DataVector> &vector) {
//           vector.emplace_back(TMath::ATan2(Y[ich], X[ich]), weight);
//         });
//       }
//     }
//   }

    
/*  void FillTrackingDetector(Qn::Detector &detector, const DataTreeEvent &event) 
  {

    auto values = new float[VarManager::Variables::kNVars];
    AliReducedTrackInfo *track = nullptr;
    auto trackList = event.GetTracks();
    TIter next(trackList);
    next.Reset();
    auto &datacontainer = detector.GetDataContainer();
    auto &axes = datacontainer->GetAxes();
    std::vector<float> trackparams;
    trackparams.reserve(axes.size());
    long ntracks = trackList->GetSize();
    std::for_each(datacontainer->begin(),
                  datacontainer->end(),
                  [ntracks](std::vector<DataVector> &vector) { vector.reserve(ntracks); });
    while ((track = (AliReducedTrackInfo *) next())!=nullptr) {

      VAR::FillTrackInfo(track, values);
      
      for (const auto num : detector.GetEnums()) {
        trackparams.push_back(values[num]);
      }
      try {
        datacontainer->CallOnElement(trackparams, [values](std::vector<DataVector> &vector) {
          vector.emplace_back(values[VAR::kPhi]);
        });
      }
      catch (std::exception &) {
        continue;
      }
      trackparams.clear();
    }
    delete[] values;      
      

    auto &datacontainer = detector.GetDataContainer();

    for (u_short ich = 0; ich < event.GetNTracks(); ich++) {
      double weight = 1;
      
      if (weight > 100) {
        datacontainer->CallOnElement([ich, Y, X, weight](std::vector<DataVector> &vector) {
          vector.emplace_back(TMath::ATan2(Y[ich], X[ich]), weight);
        });
      }
    }
  }*/    
    
  void FillPSD(Qn::Detector &detector, const DataTreeEvent &event, int ipsd) {
    auto &datacontainer = detector.GetDataContainer();

    for (u_short ich = 0; ich < cbmpsd_.at(ipsd).size(); ich++) {

      auto psd = event.GetPSDModule( cbmpsd_.at(ipsd).at(ich) - 1 );  

      double x = psd->GetPositionComponent(0);
      double y = psd->GetPositionComponent(1);
      double weight = psd->GetEnergy();
      
      std::cout << "x = " << x << " y = " << y << " weight = " << weight << std::endl; 
      
      if (weight > 0) {
        datacontainer->CallOnElement([ich, y, x, weight](std::vector<DataVector> &vector) {
          vector.emplace_back(TMath::ATan2(y, x), weight);
        });
      }
    }
  }    
    
    
private:

  DataTreeEvent* event_;
  
  const std::vector<std::vector<int>> cbmpsd_ = { 
  { 19, 20, 25, 26},
  { 12, 13, 14, 15, 18, 21, 24, 27, 30, 31, 32, 33},
  { 1,2,3,4,5,6,7,8,9,10,11,16,17,22,23,28,29,34,35,36,37,38,39,40,41,42,43,44} };
  
  const std::vector<std::vector<int>> na61psd_ = { 
   {6,7,10,11,1,2,3,4,5,8,9,12,13,14,15,16},
   {22,23,24,25,28,29,32,33,36,37,38,39},
   {17,18,19,20,21,26,27,30,31,34,35,40,41,42,43,44} };

//     else if (name == "cbm52")
//     {    
//         PsdPos.push_back ( {1,2,3,4,5,6,7,8,9,10,11,12} );
//         PsdPos.push_back ( {24,25,26,27,30,31,34,35,38,39,40,41 } );
//         PsdPos.push_back ( {13,14,15,16,17,18,19,20,21,22,23,28,29,32,33,36,37,42,43,44,45,46,47,48,49,50,51,52} );         
//     }
    
};

}
}
}
#endif //FLOW_DATAFILLER_H
