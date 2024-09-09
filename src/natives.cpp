/*
# natives.cpp

This source file contains the bridge between natives and implementations. I
prefer to keep the actual implementation separate. The implementation contains
no instances of `cell` or `AMX*` and is purely C++ and external library code.
The code here acts as the translation between AMX data types and native types.
*/

#include "natives.hpp"
#include "impl.hpp"
#include "common.hpp"



cell Natives::MyFunction(AMX* amx, cell* params) {
    logprintf("Hello world!");
    return 0;
}
cell Natives::CheckPair(AMX* amx, cell* params) {
    // We expect 5 parameters (command + 4 card values)
    if (params[0] != 4 * sizeof(cell)) {
        logprintf("Error: Expected 4 card values");
        return 0;
    }

    // Extract card values
    int card1 = static_cast<int>(params[1]);
    int card2 = static_cast<int>(params[2]);
    int card3 = static_cast<int>(params[3]);
    int card4 = static_cast<int>(params[4]);

    // Call the implementation function
    bool isPair = Impl::checkPair(card1, card2, card3, card4);

    logprintf("Checked for pair: %s", isPair ? "true" : "false");

    return isPair ? 1 : 0;
}

cell Natives::CheckTwoPairs(AMX* amx, cell* params) {
    if (params[0] != 4 * sizeof(cell)) {
        logprintf("Error: Expected 4 card values");
        return 0;
    }
    int card1 = static_cast<int>(params[1]);
    int card2 = static_cast<int>(params[2]);
    int card3 = static_cast<int>(params[3]);
    int card4 = static_cast<int>(params[4]);
    bool hasTwoPairs = Impl::checkTwoPairs(card1, card2, card3, card4);
    logprintf("Checked for two pairs: %s", hasTwoPairs ? "true" : "false");
    return hasTwoPairs ? 1 : 0;
}

cell Natives::CheckThreeOfAKind(AMX* amx, cell* params) {
    if (params[0] != 4 * sizeof(cell)) {
        logprintf("Error: Expected 4 card values");
        return 0;
    }
    int card1 = static_cast<int>(params[1]);
    int card2 = static_cast<int>(params[2]);
    int card3 = static_cast<int>(params[3]);
    int card4 = static_cast<int>(params[4]);
    bool hasThreeOfAKind = Impl::checkThreeOfAKind(card1, card2, card3, card4);
    logprintf("Checked for three of a kind: %s", hasThreeOfAKind ? "true" : "false");
    return hasThreeOfAKind ? 1 : 0;
}

cell Natives::CheckFourOfAKind(AMX* amx, cell* params) {
    if (params[0] != 4 * sizeof(cell)) {
        logprintf("Error: Expected 4 card values");
        return 0;
    }
    int card1 = static_cast<int>(params[1]);
    int card2 = static_cast<int>(params[2]);
    int card3 = static_cast<int>(params[3]);
    int card4 = static_cast<int>(params[4]);
    bool hasFourOfAKind = Impl::checkFourOfAKind(card1, card2, card3, card4);
    logprintf("Checked for four of a kind: %s", hasFourOfAKind ? "true" : "false");
    return hasFourOfAKind ? 1 : 0;
}

cell Natives::GetBestHand(AMX* amx, cell* params) {
    if (params[0] != 4 * sizeof(cell)) {
        logprintf("Error: GetBestHand expected 4 card values");
        return 0;
    }
    int card1 = static_cast<int>(params[1]);
    int card2 = static_cast<int>(params[2]);
    int card3 = static_cast<int>(params[3]);
    int card4 = static_cast<int>(params[4]);

    Impl::HandRank bestHand = Impl::getBestHand(card1, card2, card3, card4);
    logprintf("Best hand determined: %d", static_cast<int>(bestHand));
    return static_cast<cell>(bestHand);
}

cell Natives::GetHighestCard(AMX* amx, cell* params) {
    if (params[0] != 4 * sizeof(cell)) {
        logprintf("Error: GetHighestCard expected 4 card values");
        return 0;
    }
    int card1 = static_cast<int>(params[1]);
    int card2 = static_cast<int>(params[2]);
    int card3 = static_cast<int>(params[3]);
    int card4 = static_cast<int>(params[4]);

    int highestCard = Impl::getHighestCard(card1, card2, card3, card4);
    logprintf("Highest card determined: %d", highestCard);
    return static_cast<cell>(highestCard);
}

cell Natives::CardValueToString(AMX* amx, cell* params) {
    if (params[0] != 3 * sizeof(cell)) {
        logprintf("Error: CardValueToString expected 3 parameters");
        return 0;
    }
    int cardValue = static_cast<int>(params[1]);

    const char* cardString = Impl::cardValueToString(cardValue);

    cell* addr = NULL;
    amx_GetAddr(amx, params[2], &addr);
    amx_SetString(addr, cardString, 0, 0, params[3]);

    logprintf("Debug: CardValueToString input: %d, output: %s", cardValue, cardString);

    return strlen(cardString);
}