// built-in include guard removal
// just in case the user has a local dependency with the same file name
#if defined _inc_POKER_CHECKER
	#undef _inc_POKER_CHECKER
#endif
// custom include-guard to ensure we don't duplicate
#if defined _POKER_CHECKER_included
	#endinput
#endif
#define _POKER_CHECKER_included


// don't forget to change the above include guard to match the file name!

// Suit enumeration
enum Suit {
    Suit_Hearts,
    Suit_Diamonds,
    Suit_Clubs,
    Suit_Spades
}

// Hand rank enumeration
enum HandRank {
    HandRank_HighCard,
    HandRank_Pair,
    HandRank_TwoPairs,
    HandRank_ThreeOfAKind,
    HandRank_Straight,
    HandRank_Flush,
    HandRank_FullHouse,
    HandRank_FourOfAKind,
    HandRank_StraightFlush,
    HandRank_RoyalFlush
}

// Card creation and manipulation
native Card:CreateCard(value, Suit:suit);
native GetCardValue(Card:card);
native Suit:GetCardSuit(Card:card);

// Hand checking functions
native bool:CheckPair(Card:card1, Card:card2, Card:card3, Card:card4, Card:card5);
native bool:CheckTwoPairs(Card:card1, Card:card2, Card:card3, Card:card4, Card:card5);
native bool:CheckThreeOfAKind(Card:card1, Card:card2, Card:card3, Card:card4, Card:card5);
native bool:CheckStraight(Card:card1, Card:card2, Card:card3, Card:card4, Card:card5);
native bool:CheckFlush(Card:card1, Card:card2, Card:card3, Card:card4, Card:card5);
native bool:CheckFullHouse(Card:card1, Card:card2, Card:card3, Card:card4, Card:card5);
native bool:CheckFourOfAKind(Card:card1, Card:card2, Card:card3, Card:card4, Card:card5);
native bool:CheckStraightFlush(Card:card1, Card:card2, Card:card3, Card:card4, Card:card5);
native bool:CheckRoyalFlush(Card:card1, Card:card2, Card:card3, Card:card4, Card:card5);

// Hand evaluation functions
native HandRank:GetHandRank(Card:card1, Card:card2, Card:card3, Card:card4, Card:card5);
native GetBestHand(const Card:cards[], cardsCount, Card:bestHand[5]);
native CompareHands(Card:hand1_card1, Card:hand1_card2, Card:hand1_card3, Card:hand1_card4, Card:hand1_card5, 
                    Card:hand2_card1, Card:hand2_card2, Card:hand2_card3, Card:hand2_card4, Card:hand2_card5);
native Card:GetHighestCard(Card:card1, Card:card2, Card:card3, Card:card4, Card:card5);

// Utility functions
native HandRankToString(HandRank:rank, string[], len = sizeof(string));
native CardValueToString(cardValue, string[], len = sizeof(string));
native SuitToString(Suit:suit, string[], len = sizeof(string));

// Helper function (implement this in your PAWN script)
stock GetHandRankName(HandRank:rank) {
    new rankName[32];
    HandRankToString(rank, rankName, sizeof(rankName));
    return rankName;
}

// Card values
#define CARD_TWO    2
#define CARD_THREE  3
#define CARD_FOUR   4
#define CARD_FIVE   5
#define CARD_SIX    6
#define CARD_SEVEN  7
#define CARD_EIGHT  8
#define CARD_NINE   9
#define CARD_TEN    10
#define CARD_JACK   11
#define CARD_QUEEN  12
#define CARD_KING   13
#define CARD_ACE    14