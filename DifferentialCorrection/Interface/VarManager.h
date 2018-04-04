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
    kPt,
    kEta,
    kRapidity,
    kPhi,
    kPid,
    kCharge,
    kNVars
  };

  static void FillTrackInfo(const DataTreeTrack &track, float *values) {

    const double ybeam = 2.079; // TODO set as global variable

    const int pid = Cuts::GetTrackPid (track);
    double y = -999;

    if (abs (pid) == 211)
    {
        y = track.GetRapidity() - ybeam;
    }

    else if (abs (pid) == 2212)
    {
        const double p = track.GetP();
        const double pz = track.GetPz();
        const double e=sqrt( p*p + 0.938*0.938 );
        y = 0.5*log( (e+pz)/(e-pz) ) - ybeam ;
    }

    else if (abs (pid) == 11)
    {
        const double p = track.GetP();
        const double pz = track.GetPz();
        const double e=sqrt( p*p + 0.000511*0.000511 );
        y = 0.5*log( (e+pz)/(e-pz) ) - ybeam ;
    }

//     std::cout << track.GetEta() << "     " << y << std::endl;

    values[kPt] = track.GetPt();
    values[kRapidity] = y;
    values[kPhi] = track.GetPhi();
    values[kPid] = pid;
    values[kCharge] = track.GetCharge();
    values[kEta] = track.GetEta();
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
       if ( isnan( track->GetPt() ) ) continue;
       if      ( ! Cuts::isGoodTrack(*track) && setup == "na61" ) continue;
       if      ( ! Cuts::isGoodTrack(*track) && setup == "na49" ) continue;
       else if ( ! Cuts::isGoodTrackCbm(*track) && (setup == "cbm" || setup == "cbmold" || setup == "cbm52" ) ) continue;
       m++;
     }

//    values[kCentrality] = centr -> GetCentrality(m);
    values[kCentrality] = event.GetImpactParameter(); // here NA49 centrality is stored
    values[kEveto] = event.GetPSDEnergy ();
    values[kMultiplicity] = event.GetNVertexTracks();
}


};
}

#endif


