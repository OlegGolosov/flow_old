//
// Created by Lukas Kreis on 17.01.18.
//

#include "DataFiller.h"

#include "cuts/isGoodEvent.h"
#include "cuts/isGoodTrack.h"


namespace Qn {
namespace Differential {
namespace Interface {


  void DataFiller::Configure ()
  {
    std::vector <short> u_pid = {-211};
    std::vector <short> Q_pid = {2212, -211, 211};
//    Qn::Differential::Interface::QnCuts u_pt (u_pid, -999, 999, 0.0, 1.8, VarManager::Variables::kEfficiency); // default
    Qn::Differential::Interface::QnCuts u_pt (u_pid, -999, 999, 0.0, 1.4, VarManager::Variables::kEfficiency); // low Y configuration
    Qn::Differential::Interface::QnCuts u_y (u_pid, 0.0, 2.0, -999, 999, VarManager::Variables::kEfficiency); // default
//    Qn::Differential::Interface::QnCuts u_y (u_pid, 0.05, 2.0, -999, 999); // victor_cuts
//    Qn::Differential::Interface::QnCuts u_y (u_pid, 0.4, 2.0, -999, 999); // STAR protons
//    Qn::Differential::Interface::QnCuts u_y (u_pid, 0.2, 999, -999, 999); // STAR pions
//		u_y.SetPcms(0.0, 1.6); // STAR pions
//		u_y.SetEtacms(-1., 1.); // STAR protons and pions
    Qn::Differential::Interface::QnCuts Q_fproton ({2212}, 0.0, 2.5, 0.0, 3.0);
    Qn::Differential::Interface::QnCuts Q_fpiplus ({211}, 0.0, 2.5, 0.0, 3.0);
    Qn::Differential::Interface::QnCuts Q_fpiminus ({-211}, 0.0, 2.5, 0.0, 3.0);
    Qn::Differential::Interface::QnCuts Q1 (Q_pid, 0.0, 1.0, 0.8, 2.8, VarManager::Variables::kRapidity);
    Qn::Differential::Interface::QnCuts Q2 (Q_pid, 0.0, 1.0, -0.4, 1.8, VarManager::Variables::kPt);
	
    qnCuts.insert(std::make_pair("TPC_1", Q_fproton));
    qnCuts.insert(std::make_pair("TPC_2", Q_fpiplus));
    qnCuts.insert(std::make_pair("TPC_3", Q_fpiminus));
    qnCuts.insert(std::make_pair("TPC_a_1", Q1));
    qnCuts.insert(std::make_pair("TPC_a_2", Q2));
    qnCuts.insert(std::make_pair("TPC_b_1", Q1));
    qnCuts.insert(std::make_pair("TPC_b_2", Q2));
    qnCuts.insert(std::make_pair("TPC_pt", u_pt));
    qnCuts.insert(std::make_pair("TPC_y", u_y));
    qnCuts.insert(std::make_pair("TPC_pt_a_1", u_pt));
    qnCuts.insert(std::make_pair("TPC_y_a_1", u_y));
    qnCuts.insert(std::make_pair("TPC_pt_a_2", u_pt));
    qnCuts.insert(std::make_pair("TPC_y_a_2", u_y));
    qnCuts.insert(std::make_pair("TPC_pt_b_1", u_pt));
    qnCuts.insert(std::make_pair("TPC_y_b_1", u_y));
    qnCuts.insert(std::make_pair("TPC_pt_b_2", u_pt));
    qnCuts.insert(std::make_pair("TPC_y_b_2", u_y));
  }
	
	
	void DataFiller::Fill(std::map<std::string, Detector> &detectors) //const
	{
		FillTrackIndex (detectors, *event_, "TPC_a_1");
		FillTrackIndex (detectors, *event_, "TPC_a_2");
		std::vector <u_short> index1 = trackIndeces.at("TPC_a_1");
		std::vector <u_short> index2 = trackIndeces.at("TPC_a_2");
		trackIndeces.insert (std::make_pair ("TPC_b_1", index1));
		trackIndeces.insert (std::make_pair ("TPC_b_2", index2));
		trackIndeces.insert (std::make_pair ("TPC_pt_a_1", index1));
		trackIndeces.insert (std::make_pair ("TPC_pt_a_2", index2));
		trackIndeces.insert (std::make_pair ("TPC_y_a_1", index1));
		trackIndeces.insert (std::make_pair ("TPC_y_a_2", index2));
		trackIndeces.insert (std::make_pair ("TPC_pt_b_1", index1));
		trackIndeces.insert (std::make_pair ("TPC_pt_b_2", index2));
		trackIndeces.insert (std::make_pair ("TPC_y_b_1", index1));
		trackIndeces.insert (std::make_pair ("TPC_y_b_2", index2));
		
    FillTrackingDetector(detectors, *event_, "TPC_1");
    FillTrackingDetector(detectors, *event_, "TPC_2");
    FillTrackingDetector(detectors, *event_, "TPC_3");
    FillTrackingDetector(detectors, *event_, "TPC_pt");
    FillTrackingDetector(detectors, *event_, "TPC_y");
    FillTrackingDetector(detectors, *event_, "TPC_a_1", 1);
    FillTrackingDetector(detectors, *event_, "TPC_b_1", 2);
    FillTrackingDetector(detectors, *event_, "TPC_a_2", 1);
    FillTrackingDetector(detectors, *event_, "TPC_b_2", 2);
    FillTrackingDetector(detectors, *event_, "TPC_pt_a_1", 1);
    FillTrackingDetector(detectors, *event_, "TPC_y_a_1", 1);
    FillTrackingDetector(detectors, *event_, "TPC_pt_b_1", 2);
    FillTrackingDetector(detectors, *event_, "TPC_y_b_1", 2);
    FillTrackingDetector(detectors, *event_, "TPC_pt_a_2", 1);
    FillTrackingDetector(detectors, *event_, "TPC_y_a_2", 1);
    FillTrackingDetector(detectors, *event_, "TPC_pt_b_2", 2);
    FillTrackingDetector(detectors, *event_, "TPC_y_b_2", 2);

    FillPSD(detectors, *event_, "PSD1", 0);
    FillPSD(detectors, *event_, "PSD2", 1);
    FillPSD(detectors, *event_, "PSD3", 2);

    if ( issim_ )
    {
        FillPsi(detectors.at("PSI"), *event_);
        FillMCTrackingDetector(detectors.at("MC_pT"), *event_, true);
        FillMCTrackingDetector(detectors.at("MC_eta"), *event_, true);
    }
  }


  void DataFiller::FillTrackIndex (std::map<std::string, Detector> &detectors, const DataTreeEvent &event, std::string detectorName) //const
  {
		try { detectors.at(detectorName).GetNChannels();}
    catch (std::out_of_range &)
    {
      std::string error = detectorName + " was not found in the list of detectors. It needs to be created before it can be filled.\n"; ;
      throw std::out_of_range (error);
      return;
    }
    Qn::Differential::Interface::QnCuts qnCut = qnCuts.at (detectorName);
    auto values = new float [VarManager::Variables::kNVars];
    DataTreeTrack *track = nullptr;
		std::vector <u_short> index;

    u_short ntracks;
    if (setup_ == "na61" || setup_ == "na49") ntracks = event.GetNVertexTracks();
    else ntracks = event.GetNTracks();

    bool skipFlag;
    for (u_short itrack = 0; itrack < ntracks; itrack++) 
		{
      skipFlag = true;
      if (setup_ == "na61" || setup_ == "na49") track = event.GetVertexTrack(itrack);
      else track = event.GetTrack(itrack);
      if ( std::isnan( track->GetPt() ) ) continue;

      if ( ! Cuts::isGoodTrackCbm(*track) && setup_ == "cbm" ) continue;
      if ( ! Cuts::isGoodTrack(*track) && setup_ == "na61" ) continue;
      if ( ! Cuts::isGoodTrack(*track) && setup_ == "na49" ) continue;

      VarManager::FillTrackInfo(*track, values);
      short pid = values[VarManager::Variables::kPid];
      float pt = values[VarManager::Variables::kPt];
      float y = values[VarManager::Variables::kRapidity];
      float etacms = values[VarManager::Variables::kEtacms];
      float pcms = values[VarManager::Variables::kPcms];

      for (u_short i = 0; i < qnCut.pid.size (); i++) if (pid == qnCut.pid.at (i)) skipFlag = false;
      if (skipFlag) continue;
      if (y < qnCut.yMin || y > qnCut.yMax) continue;
      if (pt < qnCut.ptMin || pt > qnCut.ptMax) continue;
      if (etacms < qnCut.etacmsMin || etacms > qnCut.etacmsMax) continue;
      if (pcms < qnCut.pcmsMin || pcms > qnCut.pcmsMax) continue;
			index.push_back (itrack);
		}
	
		std::random_shuffle (index.begin(), index.end());
		trackIndeces.insert (std::make_pair (detectorName, index));
    delete[] values;
  }


	void DataFiller::FillTrackingDetector(std::map<std::string, Detector> &detectors, const DataTreeEvent &event, std::string detectorName, u_short subevent) const
	{
    try { detectors.at(detectorName).GetNChannels();}
    catch (std::out_of_range &)
    {
      std::string error = detectorName + " was not found in the list of detectors. It needs to be created before it can be filled.\n"; ;
      throw std::out_of_range (error);
      return;
    }

    Qn::Detector& detector = detectors.at (detectorName);
    Qn::Differential::Interface::QnCuts qnCut = qnCuts.at (detectorName);
		std::vector <u_short> index;
		if (subevent != 0) index = trackIndeces.at (detectorName);
//    auto values = new float[VarManager::Variables::kNVars];
    DataTreeTrack *track = nullptr;
    short pid, charge, mult = 0;
    float pt, y, phi, p, pcms, etacms, dEdx, eff, weight, cent = values [VarManager::Variables::kCentrality];
    auto &datacontainer = detector.GetDataContainer();
    auto &axes = datacontainer->GetAxes();
    std::vector<float> trackparams;
    trackparams.reserve(axes.size());
		
		std::vector <TH1*> *h1 = hist1 -> at (detectorName);
		std::vector <TH2*> *h2 = hist2 -> at (detectorName);

    u_short ntracks;
    if (setup_ == "na61" || setup_ == "na49") ntracks = event.GetNVertexTracks();
    else ntracks = event.GetNTracks();

    std::for_each(datacontainer->begin(),
                  datacontainer->end(),
                  [ntracks](std::vector<DataVector> &vector) { vector.reserve(ntracks); });

    bool skipFlag;
		u_short indexMin = (index.size () / 2) * (subevent - 1);
		u_short indexMax = indexMin + index.size () / 2;
    for (u_short itrack = 0; itrack < ntracks; itrack++) 
		{
			if (setup_ == "na61" || setup_ == "na49") track = event.GetVertexTrack(itrack);
			else track = event.GetTrack(itrack);
			if ( std::isnan( track->GetPt() ) ) continue;
			
			if ( ! Cuts::isGoodTrackCbm(*track) && setup_ == "cbm" ) continue;
			if ( ! Cuts::isGoodTrack(*track) && setup_ == "na61" ) continue;
			if ( ! Cuts::isGoodTrack(*track) && setup_ == "na49" ) continue;

			VarManager::FillTrackInfo(*track, values);
			pid = values[VarManager::Variables::kPid];
			pt = values[VarManager::Variables::kPt];
			y = values[VarManager::Variables::kRapidity];
			phi = values[VarManager::Variables::kPhi];
			p = values[VarManager::Variables::kP];
			dEdx = values[VarManager::Variables::kdEdx];
			charge = values[VarManager::Variables::kCharge];
      etacms = values[VarManager::Variables::kEtacms];
      pcms = values[VarManager::Variables::kPcms];
			if (heff_ != nullptr)
			{
				eff = heff_->GetBinContent( heff_->FindBin(pt, y) );
				values[VarManager::Variables::kEfficiency] = (eff > 0.05 && eff < 1.) ? 1. / eff : 0.4;
			}
			if (qnCut.weight != -999) weight = values [qnCut.weight];
			else weight = 1.0;

			skipFlag = true;
			for (u_short i = 0; i < qnCut.pid.size (); i++) if (pid == qnCut.pid.at (i)) skipFlag = false;
			if (skipFlag) continue;
			if (y < qnCut.yMin || y > qnCut.yMax) continue;
			if (pt < qnCut.ptMin || pt > qnCut.ptMax) continue;
      if (etacms < qnCut.etacmsMin || etacms > qnCut.etacmsMax) continue;
      if (pcms < qnCut.pcmsMin || pcms > qnCut.pcmsMax) continue;
			
			if (subevent != 0)
			{
				for (u_short i = indexMin; i < indexMax; i++)
				{
					if (itrack == index [i]) 
					{
						skipFlag = true; 
						break;
					}
				}
			}
			if (skipFlag) continue;
			
			mult++;
			h1 -> at (0) -> Fill (weight);
			h2 -> at (0) -> Fill (y, pt, weight);
			h2 -> at (1) -> Fill (phi, pt, weight);
			h2 -> at (2) -> Fill (phi, y, weight);
			h2 -> at (3) -> Fill (log (10 * p) * charge, dEdx, weight);
			h2 -> at (5) -> Fill (etacms, pcms, weight);
			
			
			for (const auto num : detector.GetEnums()) {trackparams.push_back(values[num]);}

			try 
			{
				datacontainer->CallOnElement
				(	
					trackparams, [phi, weight] (std::vector<DataVector> &vector) 
					{
						vector.emplace_back(phi, weight);
					}
//					trackparams, [values, weight] (std::vector<DataVector> &vector) 
//					{
//						vector.emplace_back(values[VarManager::Variables::kPhi], weight);
//					}
//					trackparams, [values] (std::vector<DataVector> &vector) 
//					{
//						vector.emplace_back(values[VarManager::Variables::kPhi]);
//					}
				);
			}
			catch (std::exception & a) {
				trackparams.clear();
				continue;
			}
				trackparams.clear();
    }
		
		h2 -> at (4) -> Fill (cent, mult);
//    delete[] values;
	}

  void DataFiller::FillPSD(std::map<std::string, Detector> &detectors, const DataTreeEvent &event, std::string detectorName, u_short ipsd) const
  {
		try { detectors.at(detectorName).GetNChannels();}
    catch (std::out_of_range &)
    {
      std::string error = detectorName + " was not found in the list of detectors. It needs to be created before it can be filled.\n"; ;
      throw std::out_of_range (error);
      return;
    }

    Qn::Detector& detector = detectors.at (detectorName);
    auto &datacontainer = detector.GetDataContainer();
		std::vector <TH1*> *h1 = hist1 -> at (detectorName);
		std::vector <TH2*> *h2 = hist2 -> at (detectorName);
		float sumW = 0;
		float cent = values [VarManager::Variables::kCentrality];
		float Eveto = values [VarManager::Variables::kEveto];

    float psdxshift = 0.0;
    const std::vector<std::vector<int>> *psdpos;

    if (setup_ == "cbmold") {   psdpos = &cbmoldpsd_;   psdxshift = 11.; } //TODO fix with getter, now for old urqmd files is not stored
    else if (setup_ == "cbm") {   psdpos = &cbmpsd_;   psdxshift = 11.; }
    else if (setup_ == "cbm52") { psdpos = &cbmpsd52_; psdxshift = 11.; }
    else if (setup_ == "na61")  psdpos = &na61psd_;
    else if (setup_ == "na49")  psdpos = &na49veto_;

    if (psdpos->size() < ipsd+1 ) return;

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

    for (u_short ich = chMin; ich <= chMax; ich++)
    {
      auto module = event.GetPSDModule( ich - 1 );  // modules numbering starts with 1

      double x = module->GetPositionComponent(0) - psdxshift;
      double y = module->GetPositionComponent(1);
      const double weight = module->GetEnergy();
			
      // patch

      if (ich == 1) {x = -18; y = -18;}
      if (ich == 2) {x = 18; y = -18;}
      if (ich == 3) {x = 18; y = 18;}
      if (ich == 4) {x = -18; y = 18;}

      // end patch

      if (weight > 0) 
			{
				sumW += weight;
				h2 -> at (0) -> Fill (x, y, weight);
        datacontainer->CallOnElement([ich, y, x, weight](std::vector<DataVector> &vector) {
          if (ich < 5) vector.emplace_back(TMath::ATan2(y, x), weight);
          else vector.emplace_back(TMath::ATan2(y, x) - TMath::Pi() / 24., weight);
        });
      }
    }
		h2 -> at (1) -> Fill (cent, sumW);
		h2 -> at (2) -> Fill (cent, Eveto);
		h2 -> at (3) -> Fill (Eveto, sumW);
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
      if ( std::isnan( track->GetPt() ) ) continue;
//       if ( std::isnan( track->GetEta() ) ) continue;

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






