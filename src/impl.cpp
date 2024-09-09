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

    bool checkPair(int card1, int card2, int card3, int card4) {
        std::vector<int> cards = { card1, card2, card3, card4 };

        // Sort the cards
        std::sort(cards.begin(), cards.end());

        // Check for a pair
        for (int i = 0; i < 3; i++) {
            if (cards[i] == cards[i + 1]) {
                return true;
            }
        }

        return false;
    }


    bool checkTwoPairs(int card1, int card2, int card3, int card4) {
        std::array<int, 4> cards = { card1, card2, card3, card4 };
        std::sort(cards.begin(), cards.end());
        return (cards[0] == cards[1] && cards[2] == cards[3]) ||
            (cards[0] == cards[1] && cards[1] != cards[2] && cards[2] == cards[3]);
    }

    bool checkThreeOfAKind(int card1, int card2, int card3, int card4) {
        std::array<int, 4> cards = { card1, card2, card3, card4 };
        std::sort(cards.begin(), cards.end());
        return (cards[0] == cards[1] && cards[1] == cards[2]) ||
            (cards[1] == cards[2] && cards[2] == cards[3]);
    }

    bool checkFourOfAKind(int card1, int card2, int card3, int card4) {
        return (card1 == card2 && card2 == card3 && card3 == card4);
    }

    Impl::HandRank Impl::getBestHand(int card1, int card2, int card3, int card4) {
        if (checkFourOfAKind(card1, card2, card3, card4)) return FourOfAKind;
        if (checkThreeOfAKind(card1, card2, card3, card4)) return ThreeOfAKind;
        if (checkTwoPairs(card1, card2, card3, card4)) return TwoPairs;
        if (checkPair(card1, card2, card3, card4)) return Pair;
        return HighCard;
    }

    const char* Impl::cardValueToString(int cardValue) {
        static const char* faceCards[] = { "Jack", "Queen", "King", "Ace" };
        static char buffer[8];

        if (cardValue >= 2 && cardValue <= 10) {
            snprintf(buffer, sizeof(buffer), "%d", cardValue);
            return buffer;
        }
        else if (cardValue >= 11 && cardValue <= 14) {
            return faceCards[cardValue - 11];
        }
        else {
            return "Invalid";
        }
    }

    int Impl::getHighestCard(int card1, int card2, int card3, int card4) {
        return std::max({ card1, card2, card3, card4 });
    }

}