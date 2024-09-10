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

    std::array<int, 5> sortHand(const std::array<int, 5>& hand) {
        std::array<int, 5> sorted = hand;
        std::sort(sorted.begin(), sorted.end());
        return sorted;
    }
    bool checkPair(const std::array<int, 5>& hand) {
        auto sorted = sortHand(hand);
        for (int i = 0; i < 4; ++i) {
            if (sorted[i] == sorted[i + 1]) return true;
        }
        return false;
    }

    bool checkTwoPairs(const std::array<int, 5>& hand) {
        auto sorted = sortHand(hand);
        int pairs = 0;
        for (int i = 0; i < 4; ++i) {
            if (sorted[i] == sorted[i + 1]) {
                ++pairs;
                ++i;
            }
        }
        return pairs == 2;
    }

    bool checkThreeOfAKind(const std::array<int, 5>& hand) {
        auto sorted = sortHand(hand);
        for (int i = 0; i < 3; ++i) {
            if (sorted[i] == sorted[i + 1] && sorted[i] == sorted[i + 2]) return true;
        }
        return false;
    }

    bool checkStraight(const std::array<int, 5>& hand) {
        auto sorted = sortHand(hand);
        for (int i = 0; i < 4; ++i) {
            if (sorted[i + 1] - sorted[i] != 1) return false;
        }
        return true;
    }

    bool checkFlush(const std::array<int, 5>& hand) {
        // Assuming the last digit of each card represents the suit (e.g., 14 for Ace of Hearts, 24 for Ace of Diamonds)
        int suit = hand[0] % 10;
        for (int i = 1; i < 5; ++i) {
            if (hand[i] % 10 != suit) {
                return false;
            }
        }
        return true;
    }

    bool checkFullHouse(const std::array<int, 5>& hand) {
        return checkThreeOfAKind(hand) && checkPair(hand);
    }

    bool checkFourOfAKind(const std::array<int, 5>& hand) {
        auto sorted = sortHand(hand);
        return (sorted[0] == sorted[3]) || (sorted[1] == sorted[4]);
    }

    bool checkStraightFlush(const std::array<int, 5>& hand) {
        // We can't check for straight flush without suit information
        return false;
    }

    bool checkRoyalFlush(const std::array<int, 5>& hand) {
        // We can't check for royal flush without suit information
        return false;
    }

    HandRank getHandRank(const std::array<int, 5>& hand) {
        if (checkFourOfAKind(hand)) return HandRank::FourOfAKind;
        if (checkFullHouse(hand)) return HandRank::FullHouse;
        if (checkFlush(hand)) return HandRank::Flush;
        if (checkStraight(hand)) return HandRank::Straight;
        if (checkThreeOfAKind(hand)) return HandRank::ThreeOfAKind;
        if (checkTwoPairs(hand)) return HandRank::TwoPairs;
        if (checkPair(hand)) return HandRank::Pair;
        return HandRank::HighCard;
    }

    std::array<int, 5> Impl::getBestHand(const int* cards, size_t numCards) {
        std::vector<std::array<int, 5>> combinations;

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

    int compareHands(const std::array<int, 5>& hand1, const std::array<int, 5>& hand2) {
        HandRank rank1 = getHandRank(hand1);
        HandRank rank2 = getHandRank(hand2);

        if (rank1 != rank2) {
            return static_cast<int>(rank1) - static_cast<int>(rank2);
        }

        // If ranks are equal, compare high cards
        auto sorted1 = sortHand(hand1);
        auto sorted2 = sortHand(hand2);

        for (int i = 4; i >= 0; --i) {
            if (sorted1[i] != sorted2[i]) {
                return sorted1[i] - sorted2[i];
            }
        }

        return 0; // Hands are equal
    }

    int getHighestCard(const std::array<int, 5>& hand) {
        return *std::max_element(hand.begin(), hand.end());
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

}