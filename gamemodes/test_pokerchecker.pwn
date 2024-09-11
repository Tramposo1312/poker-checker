#include <a_samp>
#include <POKER_CHECKER>

main()
{
    print("\n--- Starting Poker Checker Tests ---\n");

    // Test card creation and manipulation
    new Card:aceHearts = CreateCard(CARD_ACE, Suit_Hearts);
    new Card:kingSpades = CreateCard(CARD_KING, Suit_Spades);
    printf("Card Value Test: Ace of Hearts value: %d", GetCardValue(aceHearts));
    new suitString[16];
    SuitToString(GetCardSuit(kingSpades), suitString, sizeof(suitString));
    printf("Card Suit Test: King of Spades suit: %s", suitString);

    // Test hand checking functions
    TestHandCheck("Pair", 
        CreateCard(CARD_ACE, Suit_Hearts), CreateCard(CARD_ACE, Suit_Spades), 
        CreateCard(CARD_KING, Suit_Diamonds), CreateCard(CARD_QUEEN, Suit_Clubs), CreateCard(CARD_JACK, Suit_Hearts));
    
    TestHandCheck("Two Pairs", 
        CreateCard(CARD_ACE, Suit_Hearts), CreateCard(CARD_ACE, Suit_Spades), 
        CreateCard(CARD_KING, Suit_Diamonds), CreateCard(CARD_KING, Suit_Clubs), CreateCard(CARD_QUEEN, Suit_Hearts));
    
    TestHandCheck("Three of a Kind", 
        CreateCard(CARD_ACE, Suit_Hearts), CreateCard(CARD_ACE, Suit_Spades), CreateCard(CARD_ACE, Suit_Diamonds), 
        CreateCard(CARD_KING, Suit_Clubs), CreateCard(CARD_QUEEN, Suit_Hearts));
    
    TestHandCheck("Straight", 
        CreateCard(CARD_TEN, Suit_Hearts), CreateCard(CARD_JACK, Suit_Spades), 
        CreateCard(CARD_QUEEN, Suit_Diamonds), CreateCard(CARD_KING, Suit_Clubs), CreateCard(CARD_ACE, Suit_Hearts));
    
    TestHandCheck("Flush", 
        CreateCard(CARD_ACE, Suit_Hearts), CreateCard(CARD_KING, Suit_Hearts), 
        CreateCard(CARD_QUEEN, Suit_Hearts), CreateCard(CARD_JACK, Suit_Hearts), CreateCard(CARD_NINE, Suit_Hearts));
    
    TestHandCheck("Full House", 
        CreateCard(CARD_ACE, Suit_Hearts), CreateCard(CARD_ACE, Suit_Spades), CreateCard(CARD_ACE, Suit_Diamonds), 
        CreateCard(CARD_KING, Suit_Clubs), CreateCard(CARD_KING, Suit_Hearts));
    
    TestHandCheck("Four of a Kind", 
        CreateCard(CARD_ACE, Suit_Hearts), CreateCard(CARD_ACE, Suit_Spades), 
        CreateCard(CARD_ACE, Suit_Diamonds), CreateCard(CARD_ACE, Suit_Clubs), CreateCard(CARD_KING, Suit_Hearts));

    TestHandCheck("Straight Flush", 
        CreateCard(CARD_NINE, Suit_Hearts), CreateCard(CARD_TEN, Suit_Hearts), 
        CreateCard(CARD_JACK, Suit_Hearts), CreateCard(CARD_QUEEN, Suit_Hearts), CreateCard(CARD_KING, Suit_Hearts));

    TestHandCheck("Royal Flush", 
        CreateCard(CARD_TEN, Suit_Hearts), CreateCard(CARD_JACK, Suit_Hearts), 
        CreateCard(CARD_QUEEN, Suit_Hearts), CreateCard(CARD_KING, Suit_Hearts), CreateCard(CARD_ACE, Suit_Hearts));

    // Test GetHandRank
    new HandRank:rank = GetHandRank(
        CreateCard(CARD_ACE, Suit_Hearts), CreateCard(CARD_ACE, Suit_Spades), 
        CreateCard(CARD_ACE, Suit_Diamonds), CreateCard(CARD_ACE, Suit_Clubs), CreateCard(CARD_KING, Suit_Hearts)
    );
    printf("GetHandRank test: %s", GetHandRankName(rank));

    // Test CompareHands
    new compareResult = CompareHands(
        CreateCard(CARD_ACE, Suit_Hearts), CreateCard(CARD_ACE, Suit_Spades), 
        CreateCard(CARD_KING, Suit_Diamonds), CreateCard(CARD_KING, Suit_Clubs), CreateCard(CARD_QUEEN, Suit_Hearts),
        CreateCard(CARD_ACE, Suit_Diamonds), CreateCard(CARD_ACE, Suit_Clubs), 
        CreateCard(CARD_ACE, Suit_Hearts), CreateCard(CARD_KING, Suit_Spades), CreateCard(CARD_QUEEN, Suit_Diamonds)
    );
    printf("Debug: CompareHands result breakdown:");
    printf("Debug: CompareHands result breakdown:");
    printf("Hand1 rank: %s", GetHandRankName(GetHandRank(
        CreateCard(CARD_ACE, Suit_Hearts), CreateCard(CARD_ACE, Suit_Spades), 
        CreateCard(CARD_KING, Suit_Diamonds), CreateCard(CARD_KING, Suit_Clubs), CreateCard(CARD_QUEEN, Suit_Hearts)
    )));
    printf("Hand2 rank: %s", GetHandRankName(GetHandRank(
        CreateCard(CARD_ACE, Suit_Diamonds), CreateCard(CARD_ACE, Suit_Clubs), 
        CreateCard(CARD_ACE, Suit_Hearts), CreateCard(CARD_KING, Suit_Spades), CreateCard(CARD_QUEEN, Suit_Diamonds)
    )));
    printf("Debug: CompareHands result: %d", compareResult);

    // Test CompareHands with equal hands
new equalCompareResult = CompareHands(
    CreateCard(CARD_ACE, Suit_Hearts), CreateCard(CARD_ACE, Suit_Spades), 
    CreateCard(CARD_KING, Suit_Diamonds), CreateCard(CARD_KING, Suit_Clubs), CreateCard(CARD_QUEEN, Suit_Hearts),
    CreateCard(CARD_ACE, Suit_Diamonds), CreateCard(CARD_ACE, Suit_Clubs), 
    CreateCard(CARD_KING, Suit_Hearts), CreateCard(CARD_KING, Suit_Spades), CreateCard(CARD_QUEEN, Suit_Diamonds)
);
printf("CompareHands (equal hands) test: %d (Expected: 0)", equalCompareResult);


    // Test GetHighestCard
    new Card:highestCard = GetHighestCard(
        CreateCard(CARD_TEN, Suit_Hearts), CreateCard(CARD_JACK, Suit_Spades), 
        CreateCard(CARD_QUEEN, Suit_Diamonds), CreateCard(CARD_KING, Suit_Clubs), CreateCard(CARD_ACE, Suit_Hearts)
    );
    printf("GetHighestCard test: Value: %d, Suit: %d (Expected: 14, 0)", GetCardValue(highestCard), _:GetCardSuit(highestCard));

    // Test HandRankToString
    new rankString[32];
    HandRankToString(rank, rankString, sizeof(rankString));
    printf("HandRankToString test: %s", rankString);

    // Test CardValueToString
    new cardString[32];
    CardValueToString(CARD_ACE, cardString, sizeof(cardString));
    printf("CardValueToString test: %s", cardString);

    print("\n--- Poker Checker Tests Completed ---\n");
}

TestHandCheck(const functionName[], Card:card1, Card:card2, Card:card3, Card:card4, Card:card5)
{
    new bool:result;
    
    printf("Testing %s with cards: ", functionName);
    DebugPrintCard(card1);
    DebugPrintCard(card2);
    DebugPrintCard(card3);
    DebugPrintCard(card4);
    DebugPrintCard(card5);
    printf("\n");
    
    if (functionName[0] == 'T' && functionName[1] == 'h')
    {
        printf("Debug: CheckThreeOfAKind input: %d %d %d %d %d", 
            _:card1, _:card2, _:card3, _:card4, _:card5);
        result = CheckThreeOfAKind(card1, card2, card3, card4, card5);
        printf("Debug: CheckThreeOfAKind direct result: %d", _:result);
    }
    else
    {
        switch(functionName[0])
        {
            case 'P': result = CheckPair(card1, card2, card3, card4, card5);
            case 'T': result = CheckTwoPairs(card1, card2, card3, card4, card5);
            case 'S': 
            {
                if(functionName[1] == 't') result = CheckStraight(card1, card2, card3, card4, card5);
                else result = CheckStraightFlush(card1, card2, card3, card4, card5);
            }
            case 'F': 
            {
                if(functionName[1] == 'l') result = CheckFlush(card1, card2, card3, card4, card5);
                else if(functionName[1] == 'u') result = CheckFullHouse(card1, card2, card3, card4, card5);
                else result = CheckFourOfAKind(card1, card2, card3, card4, card5);
            }
            case 'R': result = CheckRoyalFlush(card1, card2, card3, card4, card5);
            default: result = CheckThreeOfAKind(card1, card2, card3, card4, card5);
        }
    }
    
    printf("%s test: %s (Result: %d)", functionName, result ? "Pass" : "Fail", _:result);
}

DebugPrintCard(Card:card)
{
    new valueString[16], suitString[16];
    CardValueToString(GetCardValue(card), valueString, sizeof(valueString));
    SuitToString(GetCardSuit(card), suitString, sizeof(suitString));
    printf("(%s of %s) ", valueString, suitString);
}
