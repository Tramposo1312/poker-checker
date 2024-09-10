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


// Hand checking functions
native bool:CheckPair(card1, card2, card3, card4, card5);
native bool:CheckTwoPairs(card1, card2, card3, card4, card5);
native bool:CheckThreeOfAKind(card1, card2, card3, card4, card5);
native bool:CheckStraight(card1, card2, card3, card4, card5);
native bool:CheckFlush(card1, card2, card3, card4, card5);
native bool:CheckFullHouse(card1, card2, card3, card4, card5);
native bool:CheckFourOfAKind(card1, card2, card3, card4, card5);

// Hand evaluation functions
native HandRank:GetHandRank(card1, card2, card3, card4, card5);
native GetBestHand(const cards[], cardsCount, bestHand[5]);
native CompareHands(hand1_card1, hand1_card2, hand1_card3, hand1_card4, hand1_card5, 
                    hand2_card1, hand2_card2, hand2_card3, hand2_card4, hand2_card5);
native GetHighestCard(card1, card2, card3, card4, card5);

// Utility functions
native HandRankToString(HandRank:rank, string[], len = sizeof(string));
native CardValueToString(cardValue, string[], len = sizeof(string));

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
};

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