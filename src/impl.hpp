#ifndef POKER_CHECKER_IMPL_HPP
#define POKER_CHECKER_IMPL_HPP

#include <array>
#include <vector>

namespace Impl {

    enum class HandRank {
        HighCard,
        Pair,
        TwoPairs,
        ThreeOfAKind,
        Straight,
        Flush,
        FullHouse,
        FourOfAKind,
        StraightFlush,
        RoyalFlush
    };

    bool checkPair(const std::array<int, 5>& hand);
    bool checkTwoPairs(const std::array<int, 5>& hand);
    bool checkThreeOfAKind(const std::array<int, 5>& hand);
    bool checkStraight(const std::array<int, 5>& hand);
    bool checkFlush(const std::array<int, 5>& hand);
    bool checkFullHouse(const std::array<int, 5>& hand);
    bool checkFourOfAKind(const std::array<int, 5>& hand);
    bool checkStraightFlush(const std::array<int, 5>& hand);
    bool checkRoyalFlush(const std::array<int, 5>& hand);

    HandRank getHandRank(const std::array<int, 5>& hand);
    std::array<int, 5> getBestHand(const int* cards, size_t numCards);
    int compareHands(const std::array<int, 5>& hand1, const std::array<int, 5>& hand2);
    int getHighestCard(const std::array<int, 5>& hand);

    const char* handRankToString(HandRank rank);
    const char* cardValueToString(int cardValue);

    // Utility functions
    std::array<int, 5> sortHand(const std::array<int, 5>& hand);

} 

#endif