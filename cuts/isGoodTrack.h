#ifndef IS_GOOD_TRACK_H
#define IS_GOOD_TRACK_H


#include "constants.h"
#include "DataTreeTrack.h"

namespace Cuts{

bool isGoodTrack(const DataTreeTrack& track);
bool isGoodTrackCbm(const DataTreeTrack& track);

int GetTrackPid(const DataTreeTrack& track);

}

#endif //IS_GOOD_TRACK_H
