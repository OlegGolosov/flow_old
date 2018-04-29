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

#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TProfile2D.h"



namespace Qn {
namespace Differential {
namespace Interface {

class QnCuts
{
  public:
    QnCuts (std::vector<short> pid, double ptMin, double ptMax, double yMin, double yMax, int weight = -999)
    {
      QnCuts::pid = pid;
      QnCuts::ptMin = ptMin;
      QnCuts::ptMax = ptMax;
      QnCuts::yMin = yMin;
      QnCuts::yMax = yMax;
      QnCuts::weight = weight;
    }
		
		void SetEtacms (double etaMin, double etaMax) {QnCuts::etacmsMin = etaMin; QnCuts::etacmsMax = etaMax;}
		void SetPcms (double pMin, double pMax) {QnCuts::pcmsMin = pMin; QnCuts::pcmsMax = pMax;}

    std::vector<short> pid;
    double ptMin;
    double ptMax;
    double yMin;
    double yMax;
		double pcmsMin {-999};
		double pcmsMax {999};
		double etacmsMin {-999};
		double etacmsMax {999};
    int weight;
};

class DataFiller {

 public:
  explicit DataFiller() = default; 
  explicit DataFiller(DataTreeEvent* event, 
											float *values,
											std::map <std::string, std::vector <TH1*>*> &hist1, 
											std::map <std::string, std::vector <TH2*>*> &hist2) : event_(event) 
  {
		DataFiller::hist1 = &hist1;
		DataFiller::hist2 = &hist2;
		DataFiller::values = values;
		
//		int size = DataFiller::hist2 -> at ("TPC_1") -> size ();
		Configure ();
  }

  void Fill(std::map<std::string, Detector> &detectors) /*const*/;

  void Configure ();
  void FillTrackIndex (std::map<std::string, Detector> &detectors, const DataTreeEvent &event, std::string detectorName) /*const*/;
  void FillTrackingDetector(std::map<std::string, Detector> &detectors, const DataTreeEvent &event, std::string detectorName, u_short subevent = 0) const;
  void FillMCTrackingDetector(Qn::Detector &detector, const DataTreeEvent &event,  const bool isPidCut) const;

  void FillPSD(std::map<std::string, Detector> &detectors, const DataTreeEvent &event, std::string detectorName, u_short ipsd) const ;
  void FillPsi(Qn::Detector &detector, const DataTreeEvent &event) const;

  void SetSetup(std::string setup) { setup_ = setup; }
  void SetIsSim(bool is=true) { issim_ = is; }
	void SetEff(TH2D *h) { heff_ = h; }

//   void SetCentrality(CentralityManager *c) { centr_ = c; }

private:

  DataTreeEvent* event_ {nullptr};
  std::string setup_ {"cbm"};
  bool issim_ {true};
  std::map <std::string, Qn::Differential::Interface::QnCuts> qnCuts;
  std::map <std::string, std::vector <u_short>> trackIndeces;
	std::map <std::string, std::vector <TH1*>*> *hist1;
	std::map <std::string, std::vector <TH2*>*> *hist2;
	float *values;
	TH2D *heff_{nullptr};

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
   {1,4},
   {5,124},
   {125,244}};


};

}
}
}
#endif //FLOW_DATAFILLER_HSetQnCuts
