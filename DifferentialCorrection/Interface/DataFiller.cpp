//
// Created by Lukas Kreis on 17.01.18.
//

#include "DataFiller.h"

#include "cuts/isGoodEvent.h"
#include "cuts/isGoodTrack.h"


namespace Qn {
namespace Differential {
namespace Interface {


 void DataFiller::Fill(std::map<std::string, Detector> &detectors) const
 {
    FillTrackingDetector(detectors.at("STS_pT"), *event_, "pT");
    FillTrackingDetector(detectors.at("STS_eta"), *event_, "y");
    FillTrackingDetector(detectors.at("STS_R1"), *event_, "r1");
    FillTrackingDetector(detectors.at("STS_R2"), *event_, "r2");

    try { detectors.at("PSD1").GetNChannels(); }
    catch (std::out_of_range &)
    {
//    throw std::out_of_range(
    std::cout << "PSD1 was not found in the list of detectors. It needs to be created before it can be filled." << std::endl;//);
    }

    try { detectors.at("PSD2").GetNChannels(); }
    catch (std::out_of_range &)
    {
//    throw std::out_of_range(
    std::cout << "PSD2 was not found in the list of detectors. It needs to be created before it can be filled." << std::endl;//);
    }

    try { detectors.at("PSD3").GetNChannels(); }
    catch (std::out_of_range &)
    {
//    throw std::out_of_range(
    std::cout << "PSD3 was not found in the list of detectors. It needs to be created before it can be filled." << std::endl;//);
    }



    FillPSD(detectors.at("PSD1"), *event_, 0);
    FillPSD(detectors.at("PSD2"), *event_, 1);
    FillPSD(detectors.at("PSD3"), *event_, 2);

    if ( issim_ )
    {
        FillPsi(detectors.at("PSI"), *event_);
        FillMCTrackingDetector(detectors.at("MC_pT"), *event_, true);
        FillMCTrackingDetector(detectors.at("MC_eta"), *event_, true);
    }
  }

  void DataFiller::FillTrackingDetector(Qn::Detector &detector, const DataTreeEvent &event, const std::string subevent) const
  {
    auto values = new float[VarManager::Variables::kNVars];
    DataTreeTrack *track = nullptr;

    const int pid = 2212;

    auto &datacontainer = detector.GetDataContainer();
    auto &axes = datacontainer->GetAxes();
    std::vector<float> trackparams;
    trackparams.reserve(axes.size());

    const long ntracks = setup_ == "na61" ? event.GetNVertexTracks() : event.GetNTracks();
    std::for_each(datacontainer->begin(),
                  datacontainer->end(),
                  [ntracks](std::vector<DataVector> &vector) { vector.reserve(ntracks); });

    for (u_short itrack = 0; itrack < ntracks; itrack++) {

      track = setup_ == "na61" ? event.GetVertexTrack(itrack) : event.GetTrack(itrack);
      if ( isnan( track->GetPt() ) ) continue;

      if ( ! Cuts::isGoodTrackCbm(*track) && setup_ == "cbm" ) continue;
      if ( ! Cuts::isGoodTrack(*track) && setup_ == "na61" ) continue;
      if ( ! Cuts::isGoodTrack(*track) && setup_ == "na49" ) continue;

      VarManager::FillTrackInfo(*track, values);

      if ( subevent == "pT" || subevent == "y" ) if ( values[VarManager::Variables::kPid] != pid ) continue;
      if (subevent == "pT")
      {
        if ( values[VarManager::Variables::kRapidity] < 0. || values[VarManager::Variables::kRapidity] > 1.8 ) continue;  // rapidity cut
      }
      else if (subevent == "y")
      {
        if ( values[VarManager::Variables::kPt] < 0.05 || values[VarManager::Variables::kPt] > 2. ) continue;  // pT cut
      }
/*      else if (subevent == "r1")
      {
        if ( values[VarManager::Variables::kPt] < 0.05 || values[VarManager::Variables::kPt] > 2. ) continue;  // pT cut
      }
      else if (subevent == "r2")
      {
        if ( values[VarManager::Variables::kPt] < 0.05 || values[VarManager::Variables::kPt] > 2. ) continue;  // pT cut
      } */


      for (const auto num : detector.GetEnums()) {
        trackparams.push_back(values[num]);
      }

      try {
        datacontainer->CallOnElement(trackparams, [values](std::vector<DataVector> &vector) {
          vector.emplace_back(values[VarManager::Variables::kPhi]);
        });
      }
      catch (std::exception & a) {
        trackparams.clear();
        continue;
      }
      trackparams.clear();
    }
    delete[] values;
  }

  void DataFiller::FillPSD(Qn::Detector &detector, const DataTreeEvent &event, const int ipsd) const
  {
    auto &datacontainer = detector.GetDataContainer();

    float psdxshift = 0.0;
    const std::vector<std::vector<int>>* psdpos;

    if (setup_ == "cbmold") {   psdpos = &cbmoldpsd_;   psdxshift = 11.; } //TODO fix with getter, now for old urqmd files is not stored
    else if (setup_ == "cbm") {   psdpos = &cbmpsd_;   psdxshift = 11.; }
    else if (setup_ == "cbm52") { psdpos = &cbmpsd52_; psdxshift = 11.; }
    else if (setup_ == "na61")  psdpos = &na61psd_;
    else if (setup_ == "na49")  psdpos = &na49veto_;

    if ( psdpos->size() < ipsd+1 ) return;

    for (u_short ich = 0; ich < psdpos->at(ipsd).size(); ich++) {

      auto psd = event.GetPSDModule( psdpos->at(ipsd).at(ich) - 1 );  // modules numbering starts with 1

      const double x = psd->GetPositionComponent(0) - psdxshift;
      const double y = psd->GetPositionComponent(1);
      const double weight = psd->GetEnergy();

//       std::cout << ipsd << " " << x << " " << y << " " << weight << std::endl;

      if (weight > 0) {
        datacontainer->CallOnElement([ich, y, x, weight](std::vector<DataVector> &vector) {
          vector.emplace_back(TMath::ATan2(y, x), weight);
        });
      }
    }
  }

  void DataFiller::FillPsi(Qn::Detector &detector, const DataTreeEvent &event) const
  {
    auto &datacontainer = detector.GetDataContainer();

    const double psi = event.GetRPAngle();

    datacontainer->CallOnElement([psi](std::vector<DataVector> &vector) {
          vector.emplace_back(psi, 1);  });
  }

void DataFiller::FillMCTrackingDetector(Qn::Detector &detector, const DataTreeEvent &event, const bool isPidCut) const
{
    auto values = new float[VarManager::Variables::kNVars];
    DataTreeMCTrack *track = nullptr;

    auto &datacontainer = detector.GetDataContainer();
    auto &axes = datacontainer->GetAxes();
    std::vector<float> trackparams;
    trackparams.reserve(axes.size());

    const long ntracks = event.GetNMCTracks();
    std::for_each(datacontainer->begin(),
                  datacontainer->end(),
                  [ntracks](std::vector<DataVector> &vector) { vector.reserve(ntracks); });

//     VarManager::FillEventInfo(event, values);

    for (u_short itrack = 0; itrack < ntracks; itrack++) {

      track = event.GetMCTrack(itrack);
      if ( isnan( track->GetPt() ) ) continue;
//       if ( isnan( track->GetEta() ) ) continue;

//       if ( track->GetEta() > 2.5 || track->GetEta() < 1.2 ) continue;
//       if ( track->GetPt() > 2 || track->GetPt() < 0.1 ) continue;

      VarManager::FillMCTrackInfo(*track, values);

      for (const auto num : detector.GetEnums()) {
        trackparams.push_back(values[num]);
      }
      try {
        datacontainer->CallOnElement(trackparams, [values](std::vector<DataVector> &vector) {
          vector.emplace_back(values[VarManager::Variables::kPhi]);
        });
      }
      catch (std::exception &) {
        continue;
      }
      trackparams.clear();
    }

    delete[] values;
  }




}
}
}






