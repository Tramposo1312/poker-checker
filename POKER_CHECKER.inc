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

native MyFunction();

// Poker hand checking functions
native bool:CheckPair(card1, card2, card3, card4);
native bool:CheckTwoPairs(card1, card2, card3, card4);
native bool:CheckThreeOfAKind(card1, card2, card3, card4);
native bool:CheckFourOfAKind(card1, card2, card3, card4);

// Card functions
native HandRank:GetBestHand(card1, card2, card3, card4);
native GetHighestCard(card1, card2, card3, card4);
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
    HandRank_FourOfAKind
};