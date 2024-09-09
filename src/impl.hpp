/*
# impl.hpp

From here on, it's just regular C++ code, no AMX/Pawn/SA:MP stuff. This header
is for declaring implementation functions for the plugin's core functionality.
*/

#ifndef PROJECTNAME_IMPL_H
#define PROJECTNAME_IMPL_H

namespace Impl {
    bool checkPair(int card1, int card2, int card3, int card4);
    bool checkTwoPairs(int card1, int card2, int card3, int card4);
    bool checkThreeOfAKind(int card1, int card2, int card3, int card4);
    bool checkFourOfAKind(int card1, int card2, int card3, int card4);

    enum HandRank {
        HighCard,
        Pair,
        TwoPairs,
        ThreeOfAKind,
        Straight,
        Flush,
        FullHouse,
        FourOfAKind
    };

    HandRank getBestHand(int card1, int card2, int card3, int card4);

    const char* cardValueToString(int cardValue);

    int getHighestCard(int card1, int card2, int card3, int card4);


};

#endif