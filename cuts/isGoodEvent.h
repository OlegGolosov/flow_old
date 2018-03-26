#ifndef IS_GOOD_EVENT_H
#define IS_GOOD_EVENT_H


#include "constants.h"
#include "DataTreeEvent.h"


namespace Cuts{

bool isGoodEventCbm(const DataTreeEvent& event);
bool isGoodEvent(const DataTreeEvent& event,
//                 const double e = 30,
                 const double e = 40,
                 const int bitBPD=0,
                 const int bitWFAbeam=0,
                 const int bitWFAinteract=0,
                 const int bitVTX=1,
                 const int bitT4=0,
                 const int bitS1V1=0);

bool IsGoodBPD(const DataTreeEvent& event);
int WFAcoincidence(const DataTreeEvent& event, const int TriggerId, const int timeWindow);
bool IsGoodVertex(const DataTreeEvent& event, const int kFittedVertexID);
bool IsGoodTrigger(const DataTreeEvent& event, const int TriggerId);
bool IsGoodSimpleTriggers(const DataTreeEvent& event);



// double vtx[3];
}

#endif //IS_GOOD_EVENT_H
