/*
# natives.hpp

Contains all the `PAWN_NATIVE_DECL` for native function declarations.
*/

#ifndef PROJECTNAME_NATIVES_H
#define PROJECTNAME_NATIVES_H

#include <string>

#include <amx/amx2.h>

#include "common.hpp"

namespace Natives {
    cell CheckPair(AMX* amx, cell* params);
    cell CheckTwoPairs(AMX* amx, cell* params);
    cell CheckThreeOfAKind(AMX* amx, cell* params);
    cell CheckStraight(AMX* amx, cell* params);
    cell CheckFullHouse(AMX* amx, cell* params);
    cell CheckFourOfAKind(AMX* amx, cell* params);
    cell CheckFlush(AMX* amx, cell* params);
    cell GetHandRank(AMX* amx, cell* params);
    cell GetBestHand(AMX* amx, cell* params);
    cell CompareHands(AMX* amx, cell* params);
    cell GetHighestCard(AMX* amx, cell* params);
    cell HandRankToString(AMX* amx, cell* params);
    cell CardValueToString(AMX* amx, cell* params);
}

#endif
