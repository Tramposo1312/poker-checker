#include <a_samp>
#include <POKER_CHECKER>

main() {
    print("\n--- Starting Poker Checker Tests ---\n");

    // Test hand checking functions
    TestHandCheck("Pair", CARD_ACE, CARD_ACE, CARD_KING, CARD_QUEEN, CARD_JACK);
    TestHandCheck("Two Pairs", CARD_ACE, CARD_ACE, CARD_KING, CARD_KING, CARD_QUEEN);
    TestHandCheck("Three of a Kind", CARD_ACE, CARD_ACE, CARD_ACE, CARD_KING, CARD_QUEEN);
    TestHandCheck("Straight", CARD_ACE, CARD_KING, CARD_QUEEN, CARD_JACK, CARD_TEN);
    TestHandCheck("Flush", CARD_ACE, CARD_KING, CARD_QUEEN, CARD_JACK, CARD_NINE);
    TestHandCheck("Full House", CARD_ACE, CARD_ACE, CARD_ACE, CARD_KING, CARD_KING);
    TestHandCheck("Four of a Kind", CARD_ACE, CARD_ACE, CARD_ACE, CARD_ACE, CARD_KING);

    // Test GetHandRank
    new HandRank:rank = GetHandRank(CARD_ACE, CARD_ACE, CARD_ACE, CARD_ACE, CARD_KING);
    printf("GetHandRank test: %s", GetHandRankName(rank));

    // Test GetBestHand
   /* new cards[7] = {CARD_TWO, CARD_THREE, CARD_FOUR, CARD_FIVE, CARD_SIX, CARD_SEVEN, CARD_EIGHT};
    new bestHand[5];
    GetBestHand(cards, sizeof(cards), bestHand);
    printf("GetBestHand test: %d %d %d %d %d", bestHand[0], bestHand[1], bestHand[2], bestHand[3], bestHand[4]);*/

    // Test CompareHands
    new compareResult = CompareHands(
        CARD_ACE, CARD_ACE, CARD_KING, CARD_KING, CARD_QUEEN,  // Two Pairs
        CARD_ACE, CARD_ACE, CARD_ACE, CARD_KING, CARD_QUEEN    // Three of a Kind
    );
    printf("CompareHands test: %d", compareResult);

    // Test GetHighestCard
    new highestCard = GetHighestCard(CARD_TEN, CARD_JACK, CARD_QUEEN, CARD_KING, CARD_ACE);
    printf("GetHighestCard test: %d", highestCard);

    // Test HandRankToString
    new rankString[32];
    HandRankToString(rank, rankString);
    printf("HandRankToString test: %s", rankString);

    // Test CardValueToString
    new cardString[32];
    CardValueToString(CARD_ACE, cardString);
    printf("CardValueToString test: %s", cardString);

    print("\n--- Poker Checker Tests Completed ---\n");
}

TestHandCheck(const functionName[], card1, card2, card3, card4, card5) {
    new bool:result;
    
    switch(functionName[0]) {
        case 'P': result = CheckPair(card1, card2, card3, card4, card5);
        case 'T': result = CheckTwoPairs(card1, card2, card3, card4, card5);
        case 'S': result = CheckStraight(card1, card2, card3, card4, card5);
        case 'F': {
            if(functionName[1] == 'l') result = CheckFlush(card1, card2, card3, card4, card5);
            else if(functionName[1] == 'u') result = CheckFullHouse(card1, card2, card3, card4, card5);
            else result = CheckFourOfAKind(card1, card2, card3, card4, card5);
        }
        default: result = CheckThreeOfAKind(card1, card2, card3, card4, card5);
    }
    
    printf("%s test: %s", functionName, result ? "Pass" : "Fail");
}

GetHandRankName(HandRank:rank) {
    new rankName[32];
    HandRankToString(rank, rankName);
    return rankName;
}