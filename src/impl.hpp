#ifndef POKER_CHECKER_IMPL_HPP
#define POKER_CHECKER_IMPL_HPP

#include <array>
#include <vector>

namespace Impl {

    enum class Suit {
        Hearts,
        Diamonds,
        Clubs,
        Spades
    };

    struct Card {
        int value;
        Suit suit;

        Card(int v, Suit s) : value(v), suit(s) {}
        Card(int packed) : value(packed >> 16), suit(static_cast<Suit>(packed & 0xFFFF)) {}
    };

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

    bool checkPair(const std::array<Card, 5>& hand);
    bool checkTwoPairs(const std::array<Card, 5>& hand);
    bool checkThreeOfAKind(const std::array<Card, 5>& hand);
    bool checkStraight(const std::array<Card, 5>& hand);
    bool checkFlush(const std::array<Card, 5>& hand);
    bool checkFullHouse(const std::array<Card, 5>& hand);
    bool checkFourOfAKind(const std::array<Card, 5>& hand);
    bool checkStraightFlush(const std::array<Card, 5>& hand);
    bool checkRoyalFlush(const std::array<Card, 5>& hand);

    HandRank getHandRank(const std::array<Card, 5>& hand);
    std::array<Card, 5> getBestHand(const Card* cards, size_t numCards);
    int compareHands(const std::array<Card, 5>& hand1, const std::array<Card, 5>& hand2);
    Card getHighestCard(const std::array<Card, 5>& hand);

    const char* handRankToString(HandRank rank);
    const char* cardValueToString(int cardValue);
    const char* suitToString(Suit suit);

    std::array<Card, 5> sortHand(const std::array<Card, 5>& hand);
}

#endif