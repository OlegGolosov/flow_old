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

#include "CentralityManager.h"

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
    kCharge,
		kP,
		kPcms,
		kEtacms,
		kdEdx,
		kEfficiency,
    kNVars
  };

  static void FillTrackInfo(const DataTreeTrack &track, float *values) {
    const int pid = Cuts::GetTrackPid (track);
		
		double pt, eta, phi, m, y, p, Pcms, Etacms;
		double beta = sqrt (40. * 40. - 0.938 * 0.938) / (40. + 0.938);
		TLorentzVector momentum = track.GetMomentum();
		
		pt = momentum.Pt();
		eta = momentum.Eta();
		phi = momentum.Phi();
		m = momentum.M();
		p = momentum.P();
		
		if (pid != 0) // boost to cms
		{
			if (abs (pid) == 2212) m = 0.938;
			else if (abs (pid) == 11) m = 0.000511;
			momentum.SetPtEtaPhiM (pt, eta, phi, m);
			momentum.Boost (0, 0, -beta);
			y = momentum.Rapidity ();
			Pcms = momentum.P ();
			Etacms = momentum.Eta ();
		}
		else {y = -999; Pcms = -999; Etacms = -999;}

// old method
//	const double ybeam = 2.24; // TODO set as global variable
//	if (abs (pid) == 211)
//	{
//		y = track.GetRapidity() - ybeam;
//	}
//
//  else if (abs (pid) == 2212)
//	{
//		const double p = track.GetP();
//		const double pz = track.GetPz();
//		const double e=sqrt( p*p + 0.938*0.938 );
//		y = 0.5*log( (e+pz)/(e-pz) ) - ybeam ;
//	}
//
//	else if (abs (pid) == 11)
//	{
//		const double p = track.GetP();
//		const double pz = track.GetPz();
//		const double e=sqrt( p*p + 0.000511*0.000511 );
//		y = 0.5*log( (e+pz)/(e-pz) ) - ybeam ;
//	}
// end of old method

//     std::cout << track.GetEta() << "     " << y << std::endl;

    values[kPt] = pt;
    values[kRapidity] = y;
    values[kPhi] = phi;
    values[kPid] = pid;
    values[kCharge] = track.GetCharge();
    values[kEta] = eta;
    values[kP] = p;
    values[kPcms] = Pcms;
    values[kEtacms] = Etacms;
    values[kdEdx] = track.GetdEdx(3) * 0.001;
  }

  static void FillMCTrackInfo(const DataTreeMCTrack &track, float *values) {
    values[kPt] = track.GetPt();
    values[kRapidity] = track.GetRapidity();
    values[kPhi] = track.GetPhi();
    values[kPid] = track.GetPdgId();
    values[kCharge] = track.GetCharge();
    values[kEta] = track.GetEta();

  }
  static void FillEventInfo(const DataTreeEvent &event, float *values, std::string setup, CentralityManager *centr) {


    float m=0;
//    m = event.GetPSDEnergy();

     const long ntracks = setup == "na61" ? event.GetNVertexTracks() : event.GetNTracks();
     DataTreeTrack *track = new DataTreeTrack;
     for (u_short itrack = 0; itrack < ntracks; itrack++) {
       track = setup == "na61" ? event.GetVertexTrack(itrack) : event.GetTrack(itrack);
       if ( std::isnan( track->GetPt() ) ) continue;
       if      ( ! Cuts::isGoodTrack(*track) && setup == "na61" ) continue;
       if      ( ! Cuts::isGoodTrack(*track) && setup == "na49" ) continue;
       else if ( ! Cuts::isGoodTrackCbm(*track) && (setup == "cbm" || setup == "cbmold" || setup == "cbm52" ) ) continue;
       m++;
     }

//    values[kCentrality] = centr -> GetCentrality(m);
//    values[kCentrality] = event.GetImpactParameter(); // here NA49 centrality is stored
    values[kEveto] = event.GetPSDEnergy ();
    values[kMultiplicity] = event.GetNVertexTracks ();
    values[kNRun] = event.GetRunId ();
		double Ebeam = 8.32e3;
		std::vector <double> eVetoBins ({0., 0.169 * Ebeam, 0.314 * Ebeam, 0.509 * Ebeam, 0.66 * Ebeam, 0.778 * Ebeam, 9.e3});
		for (u_short i = 0; i < eVetoBins.size () - 1; i++) 
		{
			if (values[kEveto] > eVetoBins[i] && values[kEveto] < eVetoBins[i + 1]) values[kCentrality] = i + 0.5;
		}
}


};
}

#endif


