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
    FillTrackingDetector(detectors, *event_, "TPC_eta", "y");
    FillTrackingDetector(detectors, *event_, "TPC_pT", "pT");
    FillTrackingDetector(detectors, *event_, "TPC_R1", "r1");
    FillTrackingDetector(detectors, *event_, "TPC_R2", "r2");

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

  void DataFiller::FillTrackingDetector(std::map<std::string, Detector> &detectors, const DataTreeEvent &event, std::string detectorName, const std::string subevent) const
  {
    const int flowPid = -211;
    std::vector <short> pid_r1 = {2212, -211, 211};
    std::vector <short> pid_r2 = {2212, -211, 211};

    try { detectors.at(detectorName).GetNChannels();}
    catch (std::out_of_range &)
    {
//    throw std::out_of_range(
    std::cout << detectorName << " was not found in the list of detectors. It needs to be created before it can be filled." << std::endl;//);
    return;
    }

    Qn::Detector& detector = detectors.at (detectorName);
    auto values = new float[VarManager::Variables::kNVars];
    DataTreeTrack *track = nullptr;

    u_short nPids_r1 = pid_r1.size ();
    u_short nPids_r2 = pid_r2.size ();
    short pid;
    float pt, eta, y;
    auto &datacontainer = detector.GetDataContainer();
    auto &axes = datacontainer->GetAxes();
    std::vector<float> trackparams;
    trackparams.reserve(axes.size());

    unsigned long ntracks;
    if (setup_ == "na61" || setup_ == "na49") ntracks = event.GetNVertexTracks();
    else ntracks = event.GetNTracks();

    std::for_each(datacontainer->begin(),
                  datacontainer->end(),
                  [ntracks](std::vector<DataVector> &vector) { vector.reserve(ntracks); });
    bool skipFlag;
    for (u_short itrack = 0; itrack < ntracks; itrack++) {
      skipFlag = true;
      if (setup_ == "na61" || setup_ == "na49") track = event.GetVertexTrack(itrack);
      else track = event.GetTrack(itrack);
      if ( isnan( track->GetPt() ) ) continue;

      if ( ! Cuts::isGoodTrackCbm(*track) && setup_ == "cbm" ) continue;
      if ( ! Cuts::isGoodTrack(*track) && setup_ == "na61" ) continue;
      if ( ! Cuts::isGoodTrack(*track) && setup_ == "na49" ) continue;

      VarManager::FillTrackInfo(*track, values);
      pid = values[VarManager::Variables::kPid];
      pt = values[VarManager::Variables::kPt];
      eta = values[VarManager::Variables::kEta];
      y = values[VarManager::Variables::kRapidity];

//	flowReconstructor.SetPtAveragingRange (1, 0.0, 2.0);
//	flowReconstructor.SetEtaAveragingRange (1, 0.0, 1.8);

// RS
//	flowReconstructor.SetPtSubeventsLimits (1, 0.0, 1.0, 0.0, 1.0);
//	flowReconstructor.SetPtSubeventsLimits (2, 0.0, 1.0, 0.0, 1.0);
//	flowReconstructor.SetEtaSubeventsLimits (1, 0.8, 2.8, 0.8, 2.8);
//    flowReconstructor.SetEtaSubeventsLimits (2, -0.4, 1.8, -0.4, 1.8);

// 3S VETO
//	flowReconstructor.SetPtSubeventsLimits (1, 0.1, 2.0, 0.1, 2.0, 0.0, 2.0);
//	flowReconstructor.SetEtaSubeventsLimits (1, -3.0, -0.2, 0.2, 3.0, -3.0, 3.0);

      if ( subevent == "pT" || subevent == "y" ) if ( pid != flowPid ) continue;
      if (subevent == "pT")
      {
        if ( y < 0. || y > 1.8 ) continue;  // rapidity cut
      }
      else if (subevent == "y")
      {
        if ( pt < 0.05 || pt > 2. ) continue;  // pT cut
      }
      else if (subevent == "r1")
      {
        for (int i = 0; i < nPids_r1; i++) if (pid == pid_r1 [i]) skipFlag = false;
        if (skipFlag) continue;
//        if ( pt < 0. || pt > 1. ) continue;  // pT cut
//        if ( y < .8 || y > 2.8 ) continue;
        if ( pt < .1 || pt > 2. ) continue;  // pT cut
        if ( y < -3. || y > -.2 ) continue;  // rapidity cut
      }
      else if (subevent == "r2")
      {
        for (int i = 0; i < nPids_r2; i++) if (pid == pid_r2 [i]) skipFlag = false;
        if (skipFlag) continue;
//        if ( pt < 0. || pt > 1. ) continue;  // pT cut
//        if ( y < -.4 || y > 1.8 ) continue;  // rapidity cut
        if ( pt < .1 || pt > 2. ) continue;  // pT cut
        if ( y < .2 || y > 3. ) continue;  // rapidity cut
      }

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

  void DataFiller::FillPSD(Qn::Detector &detector, const DataTreeEvent &event, u_short ipsd) const
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

//    for (u_short ich = 0; ich < psdpos->at(ipsd).size(); ich++) {
//
//      auto psd = event.GetPSDModule( psdpos->at(ipsd).at(ich) - 1 );  // modules numbering starts with 1
//
//      const double x = psd->GetPositionComponent(0) - psdxshift;
//      const double y = psd->GetPositionComponent(1);
//      const double weight = psd->GetEnergy();
//
////       std::cout << ipsd << " " << x << " " << y << " " << weight << std::endl;
//
//      if (weight > 0) {
//        datacontainer->CallOnElement([ich, y, x, weight](std::vector<DataVector> &vector) {
//          vector.emplace_back(TMath::ATan2(y, x), weight);
//        });
//      }
//    }

    u_short chMin = psdpos->at(ipsd).at(0);
    u_short chMax = psdpos->at(ipsd).at(1);

    for (u_short ich = chMin; ich < chMax; ich++)
    {
      auto module = event.GetPSDModule( ich - 1 );  // modules numbering starts with 1

      double x = module->GetPositionComponent(0) - psdxshift;
      double y = module->GetPositionComponent(1);
      const double weight = module -> GetEnergy();

      // patch

//      if (ich == 1) {x = -1; y = 1;}
//      if (ich == 2) {x = -1; y = -1;}
//      if (ich == 3) {x = 1; y = -1;}
//      if (ich == 4) {x = 1; y = 1;}

      // end patch

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






