//
// Author: Ionut-Cristian Arsene, 2015/04/05
// email: iarsene@cern.ch
//
// Variable manager
//

// TODO move to DataTree?

#include "DataTreeEvent.h"

#ifndef VARMANAGER_H
#define VARMANAGER_H

namespace Qn {

class VarManager {

 public:

  enum Values {
    kCentrality = 0,
    kMult,
    kPsdEnergy,
    kNMax = kPsdEnergy + 1
  };

  enum Variables {
//     kSignal = 0,
//     kCentrality = kSignal + 4,
//     kNMax = kCentrality + 1
  };


  static void FillEventInfo(const DataTreeEvent &event, float *values) {
    float centrality = 10;
    
    if ( event.GetNTracks() < 9 ) centrality = 90;
    else if ( event.GetNTracks() < 36 ) centrality = 70;
    else if ( event.GetNTracks() < 95 ) centrality = 50;
    else if ( event.GetNTracks() < 197 ) centrality = 30;
    
    values[kCentrality] = centrality;
    values[kPsdEnergy] = event.GetPSDEnergy();
    values[kMult] = event.GetNTracks();
  }
};
}

#endif
