//
// Author: Ionut-Cristian Arsene, 2015/04/05
// email: iarsene@cern.ch
//
// Variable manager
//

// TODO move to DataTree?

#ifndef VARMANAGER_H
#define VARMANAGER_H

#include "DataTreeEvent.h"
#include "DataTreeTrack.h"
#include "DataTreeMCTrack.h"

#include "Getter.h"
#include "PidGetter.h"

#include "cuts/isGoodTrack.h"

namespace Qn {

class VarManager {

  public:

  enum Variables {
    kCentrality = 0,
    kMultiplicity,
    kEveto,
    kNRun,
    kPt,
    kEta,
    kRapidity,
    kPhi,
    kPid,
    kPidProb,
    kCharge,
		kP,
		kPcms,
		kEtacms,
		kdEdx,
		kEfficiency,
    kNVars
  };

  
  static void FillTrackInfo(const DataTreeEvent *event, const DataTreeTrack *track, float *values, Pid::Getter *pid_getter) {
    //const int pid = Cuts::GetTrackPid (track);
		
    int pid = -999;
		double pt, eta, phi, m, m2, y, p, Pcms, Etacms;
		//double beta = sqrt (40. * 40. - 0.938 * 0.938) / (40. + 0.938); // NA49
		//double beta = 0.75537; // CBM 3.3A GeV
		double beta = 0.924884; // CBM 12A GeV
		TLorentzVector momentum = track -> GetMomentum ();
		
		pt = momentum.Pt();
		eta = momentum.Eta();
		phi = momentum.Phi();
		p = momentum.P();
    
    const int tofHitId = track -> GetTOFHitId();
    if (tofHitId >= 0)
    {
      auto tofHit = event->GetTOFHit(tofHitId);
      m2 = tofHit -> GetSquaredMass();
    }

    if (m2 != -999. && pid_getter)
      pid = pid_getter->GetPid(p, m2, 0.9) * track -> GetCharge();
		
		if (pid != 0) // boost to cms
		{
			if (abs (pid) == 2212) m = 0.938;
			else if (abs (pid) == 321) m = 0.494;
			else if (abs (pid) == 211) m = 0.140;
			momentum.SetPtEtaPhiM (pt, eta, phi, m);
			momentum.Boost (0, 0, -beta);
			y = momentum.Rapidity ();
			Pcms = momentum.P ();
			Etacms = momentum.Eta ();
		}
		else {y = -999; Pcms = -999; Etacms = -999;}

    values[kPt] = pt;
    values[kRapidity] = y;
    values[kPhi] = phi;
    values[kPid] = pid;
    values[kCharge] = track -> GetCharge();
    values[kEta] = eta;
    values[kP] = p;
    values[kPcms] = Pcms;
    values[kEtacms] = Etacms;
    values[kdEdx] = track -> GetdEdx(3) * 0.001;
    values[kEfficiency] = 1.;
  }

  static void FillMCTrackInfo(const DataTreeMCTrack &track, float *values) {
		//double beta = 0.75537; // CBM 3.3A GeV
		double beta = 0.924884; // CBM 12A GeV
    float m;
		TLorentzVector momentum;
    int pid = track.GetPdgId();
    if (abs (pid) == 2212) m = 0.938;
    else if (abs (pid) == 321) m = 0.494;
    else if (abs (pid) == 211) m = 0.140;
    momentum.SetPtEtaPhiM(track.GetPt (), track.GetEta (), track.GetPhi (), m);
		momentum.Boost (0, 0, -beta);
    
    values[kPt] = momentum.Pt();
    values[kRapidity] = momentum.Rapidity();
    values[kPhi] = momentum.Phi();
    values[kEta] = momentum.Eta();
    values[kPid] = pid;
    values[kCharge] = track.GetCharge();
  }
  
  static void FillEventInfo(const DataTreeEvent &event, float *values, TString setup, Centrality::Getter *centrality_getter) 
  {
    float m=0;
     const long ntracks = event.GetNVertexTracks();
     DataTreeTrack *track;
     for (u_short itrack = 0; itrack < ntracks; itrack++) {
       if ( std::isnan( track->GetPt() ) ) continue;
       if      (setup == "na61" && ! Cuts::isGoodTrack(*track)) continue;
       else if (setup == "na49"  && ! Cuts::isGoodTrack(*track)) continue;
       else if ((setup == "cbm" || setup == "cbmold" || setup == "cbm52" ) && ! Cuts::isGoodTrackCbm(*track)) continue;
       m++;
     }

    values[kCentrality] = centrality_getter -> GetCentrality(m);
//    values[kCentrality] = event.GetImpactParameter(); // here NA49 centrality is stored
    values[kEveto] = event.GetPSDEnergy ();
    values[kMultiplicity] = m;
    values[kNRun] = event.GetRunId ();
		//double Ebeam = 8.32e3;
		//std::vector <double> eVetoBins ({0., 0.169 * Ebeam, 0.314 * Ebeam, 0.509 * Ebeam, 0.66 * Ebeam, 0.778 * Ebeam, 8.32e3});
		//for (u_short i = 0; i < eVetoBins.size () - 1; i++) 
		//{
		//	if (values[kEveto] > eVetoBins[i] && values[kEveto] < eVetoBins[i + 1]) values[kCentrality] = i + 0.5;
		//}
  }
  
};
}

#endif


