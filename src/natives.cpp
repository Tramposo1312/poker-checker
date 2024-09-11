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
    std::array<Impl::Card, 5> getHandFromParams(AMX* amx, cell* params) {
        return {
            Impl::Card(params[1]),
            Impl::Card(params[2]),
            Impl::Card(params[3]),
            Impl::Card(params[4]),
            Impl::Card(params[5])
        };
    }
}

namespace Natives {

    cell CreateCard(AMX* amx, cell* params) {
        int value = static_cast<int>(params[1]);
        Impl::Suit suit = static_cast<Impl::Suit>(params[2]);
        return (value << 16) | static_cast<int>(suit);
    }

    cell GetCardValue(AMX* amx, cell* params) {
        return params[1] >> 16;
    }

    cell GetCardSuit(AMX* amx, cell* params) {
        return params[1] & 0xFFFF;
    }

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

    cell CheckStraightFlush(AMX* amx, cell* params) {
        auto hand = getHandFromParams(amx, params);
        return Impl::checkStraightFlush(hand) ? 1 : 0;
    }

    cell CheckRoyalFlush(AMX* amx, cell* params) {
        auto hand = getHandFromParams(amx, params);
        return Impl::checkRoyalFlush(hand) ? 1 : 0;
    }

    cell GetHandRank(AMX* amx, cell* params) {
        auto hand = getHandFromParams(amx, params);
        return static_cast<cell>(Impl::getHandRank(hand));
    }

    cell GetBestHand(AMX* amx, cell* params) {
        int numCards = params[0] / (2 * sizeof(cell)); // Each card is now represented by 2 cells (value and suit)
        std::vector<Impl::Card> cards;
        for (int i = 0; i < numCards; ++i) {
            cards.push_back(Impl::Card{ static_cast<int>(params[2 * i + 1]), static_cast<Impl::Suit>(params[2 * i + 2]) });
        }
        auto bestHand = Impl::getBestHand(cards.data(), numCards);
        cell* addr = nullptr;
        amx_GetAddr(amx, params[2 * numCards + 1], &addr);
        for (int i = 0; i < 5; ++i) {
            addr[2 * i] = bestHand[i].value;
            addr[2 * i + 1] = static_cast<cell>(bestHand[i].suit);
        }
        return 1;
    }

    cell CompareHands(AMX* amx, cell* params) {
        std::array<Impl::Card, 5> hand1 = getHandFromParams(amx, params);
        std::array<Impl::Card, 5> hand2 = {
            Impl::Card(params[6]),
            Impl::Card(params[7]),
            Impl::Card(params[8]),
            Impl::Card(params[9]),
            Impl::Card(params[10])
        };
        return Impl::compareHands(hand1, hand2);
    }

    cell GetHighestCard(AMX* amx, cell* params) {
        auto hand = getHandFromParams(amx, params);
        auto highestCard = Impl::getHighestCard(hand);
        return (highestCard.value << 16) | static_cast<int>(highestCard.suit);
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

    cell SuitToString(AMX* amx, cell* params) {
        Impl::Suit suit = static_cast<Impl::Suit>(params[1]);
        const char* suitString = Impl::suitToString(suit);
        cell* addr = nullptr;
        amx_GetAddr(amx, params[2], &addr);
        amx_SetString(addr, suitString, 0, 0, params[3]);
        return std::strlen(suitString);
    }
}