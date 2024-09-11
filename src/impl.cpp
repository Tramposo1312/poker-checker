/*
# impl.cpp

As with the header, this is the actual implementation of the plugin's
functionality with no AMX specific code or includes.

Including `common.hpp` for access to `logprintf` is useful for debugging but for
production debug logging, it's best to use a dedicated logging library such as
log-core by maddinat0r.
*/

#include "impl.hpp"
#include <algorithm>
#include <vector>
#include <array>

namespace Impl {

    std::array<Card, 5> sortHand(const std::array<Card, 5>& hand) {
        std::array<Card, 5> sorted = hand;
        std::sort(sorted.begin(), sorted.end(), [](const Card& a, const Card& b) {
            return a.value < b.value;
            });
        return sorted;
    }

    bool checkPair(const std::array<Card, 5>& hand) {
        auto sorted = sortHand(hand);
        for (int i = 0; i < 4; ++i) {
            if (sorted[i].value == sorted[i + 1].value) return true;
        }
        return false;
    }

    bool checkTwoPairs(const std::array<Card, 5>& hand) {
        auto sorted = sortHand(hand);
        int pairs = 0;
        for (int i = 0; i < 4; ++i) {
            if (sorted[i].value == sorted[i + 1].value) {
                ++pairs;
                ++i;
            }
        }
        return pairs == 2;
    }

    bool checkThreeOfAKind(const std::array<Card, 5>& hand) {
        auto sorted = sortHand(hand);
        for (int i = 0; i < 3; ++i) {
            if (sorted[i].value == sorted[i + 1].value && sorted[i].value == sorted[i + 2].value) return true;
        }
        return false;
    }

    bool checkStraight(const std::array<Card, 5>& hand) {
        auto sorted = sortHand(hand);
        for (int i = 0; i < 4; ++i) {
            if (sorted[i + 1].value - sorted[i].value != 1) return false;
        }
        return true;
    }

    bool checkFlush(const std::array<Card, 5>& hand) {
        Suit suit = hand[0].suit;
        for (int i = 1; i < 5; i++) {
            if (hand[i].suit != suit) return false;
        }
        return true;
    }

    bool checkFullHouse(const std::array<Card, 5>& hand) {
        return checkThreeOfAKind(hand) && checkPair(hand);
    }

    bool checkFourOfAKind(const std::array<Card, 5>& hand) {
        auto sorted = sortHand(hand);
        return (sorted[0].value == sorted[3].value) || (sorted[1].value == sorted[4].value);
    }

    bool checkStraightFlush(const std::array<Card, 5>& hand) {
        return checkStraight(hand) && checkFlush(hand);
    }

    bool checkRoyalFlush(const std::array<Card, 5>& hand) {
        if (!checkFlush(hand)) return false;
        auto sorted = sortHand(hand);
        return (sorted[0].value == 10 && sorted[1].value == 11 && sorted[2].value == 12 &&
                sorted[3].value == 13 && sorted[4].value == 14);
    }

    HandRank getHandRank(const std::array<Card, 5>& hand) {
        if (checkRoyalFlush(hand)) return HandRank::RoyalFlush;
        if (checkStraightFlush(hand)) return HandRank::StraightFlush;
        if (checkFourOfAKind(hand)) return HandRank::FourOfAKind;
        if (checkFullHouse(hand)) return HandRank::FullHouse;
        if (checkFlush(hand)) return HandRank::Flush;
        if (checkStraight(hand)) return HandRank::Straight;
        if (checkThreeOfAKind(hand)) return HandRank::ThreeOfAKind;
        if (checkTwoPairs(hand)) return HandRank::TwoPairs;
        if (checkPair(hand)) return HandRank::Pair;
        return HandRank::HighCard;
    }

    std::array<Card, 5> getBestHand(const Card* cards, size_t numCards) {
        std::vector<std::array<Card, 5>> combinations;

        // Generate all 5-card combinations
        for (size_t i = 0; i < numCards - 4; ++i)
            for (size_t j = i + 1; j < numCards - 3; ++j)
                for (size_t k = j + 1; k < numCards - 2; ++k)
                    for (size_t l = k + 1; l < numCards - 1; ++l)
                        for (size_t m = l + 1; m < numCards; ++m)
                            combinations.push_back({ cards[i], cards[j], cards[k], cards[l], cards[m] });

        // Find the best hand
        auto bestHand = combinations[0];
        auto bestRank = getHandRank(bestHand);

        for (const auto& hand : combinations) {
            auto rank = getHandRank(hand);
            if (rank > bestRank || (rank == bestRank && compareHands(hand, bestHand) > 0)) {
                bestHand = hand;
                bestRank = rank;
            }
        }

        return bestHand;
    }

    int compareHands(const std::array<Card, 5>& hand1, const std::array<Card, 5>& hand2) {
        HandRank rank1 = getHandRank(hand1);
        HandRank rank2 = getHandRank(hand2);

        if (rank1 != rank2) {
            return (rank1 > rank2) ? 1 : -1;
        }

        // If ranks are equal, compare high cards
        auto sorted1 = sortHand(hand1);
        auto sorted2 = sortHand(hand2);

        for (int i = 4; i >= 0; --i) {
            if (sorted1[i].value != sorted2[i].value) {
                return (sorted1[i].value > sorted2[i].value) ? 1 : -1;
            }
        }

        return 0; // Hands are equal
    }

    Card getHighestCard(const std::array<Card, 5>& hand) {
        return *std::max_element(hand.begin(), hand.end(), [](const Card& a, const Card& b) {
            return a.value < b.value;
        });
    }

    const char* handRankToString(HandRank rank) {
        switch (rank) {
        case HandRank::HighCard: return "High Card";
        case HandRank::Pair: return "Pair";
        case HandRank::TwoPairs: return "Two Pairs";
        case HandRank::ThreeOfAKind: return "Three of a Kind";
        case HandRank::Straight: return "Straight";
        case HandRank::Flush: return "Flush";
        case HandRank::FullHouse: return "Full House";
        case HandRank::FourOfAKind: return "Four of a Kind";
        case HandRank::StraightFlush: return "Straight Flush";
        case HandRank::RoyalFlush: return "Royal Flush";
        default: return "Unknown";
        }
    }

    const char* cardValueToString(int cardValue) {
        static const char* values[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };
        if (cardValue >= 2 && cardValue <= 14) {
            return values[cardValue - 2];
        }
        return "Invalid";
    }

    const char* suitToString(Suit suit) {
        switch (suit) {
        case Suit::Hearts: return "Hearts";
        case Suit::Diamonds: return "Diamonds";
        case Suit::Clubs: return "Clubs";
        case Suit::Spades: return "Spades";
        default: return "Unknown";
        }
    }
}