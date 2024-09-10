/*
# natives.cpp

This source file contains the bridge between natives and implementations. I
prefer to keep the actual implementation separate. The implementation contains
no instances of `cell` or `AMX*` and is purely C++ and external library code.
The code here acts as the translation between AMX data types and native types.
*/

#include "natives.hpp"
#include "impl.hpp"
#include <array>
#include <cstring>

namespace {
    std::array<int, 5> getHandFromParams(AMX* amx, cell* params) {
        return {
            static_cast<int>(params[1]),
            static_cast<int>(params[2]),
            static_cast<int>(params[3]),
            static_cast<int>(params[4]),
            static_cast<int>(params[5])
        };
    }
}

namespace Natives {

    cell CheckPair(AMX* amx, cell* params) {
        auto hand = getHandFromParams(amx, params);
        return Impl::checkPair(hand) ? 1 : 0;
    }

    cell CheckTwoPairs(AMX* amx, cell* params) {
        auto hand = getHandFromParams(amx, params);
        return Impl::checkTwoPairs(hand) ? 1 : 0;
    }

    cell CheckThreeOfAKind(AMX* amx, cell* params) {
        auto hand = getHandFromParams(amx, params);
        return Impl::checkThreeOfAKind(hand) ? 1 : 0;
    }

    cell CheckStraight(AMX* amx, cell* params) {
        auto hand = getHandFromParams(amx, params);
        return Impl::checkStraight(hand) ? 1 : 0;
    }

    cell CheckFlush(AMX* amx, cell* params) {
        auto hand = getHandFromParams(amx, params);
        return Impl::checkFlush(hand) ? 1 : 0;
    }

    cell CheckFullHouse(AMX* amx, cell* params) {
        auto hand = getHandFromParams(amx, params);
        return Impl::checkFullHouse(hand) ? 1 : 0;
    }

    cell CheckFourOfAKind(AMX* amx, cell* params) {
        auto hand = getHandFromParams(amx, params);
        return Impl::checkFourOfAKind(hand) ? 1 : 0;
    }

    cell GetHandRank(AMX* amx, cell* params) {
        auto hand = getHandFromParams(amx, params);
        return static_cast<cell>(Impl::getHandRank(hand));
    }

    cell Natives::GetBestHand(AMX* amx, cell* params) {
        int numCards = params[0] / sizeof(cell);
        std::array<int, 5> bestHand = Impl::getBestHand(&params[1], numCards);
        cell* addr = nullptr;
        amx_GetAddr(amx, params[numCards + 1], &addr);
        for (int i = 0; i < 5; ++i) {
            addr[i] = bestHand[i];
        }
        return 1;
    }

    cell CompareHands(AMX* amx, cell* params) {
        auto hand1 = getHandFromParams(amx, params);
        std::array<int, 5> hand2 = {
            static_cast<int>(params[6]),
            static_cast<int>(params[7]),
            static_cast<int>(params[8]),
            static_cast<int>(params[9]),
            static_cast<int>(params[10])
        };
        return Impl::compareHands(hand1, hand2);
    }

    cell GetHighestCard(AMX* amx, cell* params) {
        auto hand = getHandFromParams(amx, params);
        return Impl::getHighestCard(hand);
    }

    cell HandRankToString(AMX* amx, cell* params) {
        Impl::HandRank rank = static_cast<Impl::HandRank>(params[1]);
        const char* rankString = Impl::handRankToString(rank);
        cell* addr = nullptr;
        amx_GetAddr(amx, params[2], &addr);
        amx_SetString(addr, rankString, 0, 0, params[3]);
        return std::strlen(rankString);
    }

    cell CardValueToString(AMX* amx, cell* params) {
        int cardValue = static_cast<int>(params[1]);
        const char* cardString = Impl::cardValueToString(cardValue);
        cell* addr = nullptr;
        amx_GetAddr(amx, params[2], &addr);
        amx_SetString(addr, cardString, 0, 0, params[3]);
        return std::strlen(cardString);
    }

}