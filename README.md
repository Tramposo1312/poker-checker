# Poker Checker Plugin for SA:MP

This plugin provides comprehensive functions to evaluate and compare poker hands in SA:MP scripts.

## Features

- Check for various poker hands (Pair, Two Pairs, Three of a Kind, Straight, Flush, Full House, Four of a Kind)
- Determine the best hand from a set of cards
- Compare two poker hands
- Get the highest card from a hand
- Convert hand ranks and card values to string representations

## Installation

1. Copy the `pokerchecker.dll` (Windows) or `pokerchecker.so` (Linux) to your server's `plugins` folder.
2. Add `pokerchecker` to the `plugins` line in your `server.cfg` file.
3. Copy `POKER_CHECKER.inc` to your `pawno/include` directory.

## Usage

Include the poker checker in your PAWN script:

```pawn
#include <POKER_CHECKER>
```

### Available Functions

#### Check for Specific Hands

```pawn
native bool:CheckPair(card1, card2, card3, card4, card5);
native bool:CheckTwoPairs(card1, card2, card3, card4, card5);
native bool:CheckThreeOfAKind(card1, card2, card3, card4, card5);
native bool:CheckStraight(card1, card2, card3, card4, card5);
native bool:CheckFlush(card1, card2, card3, card4, card5);
native bool:CheckFullHouse(card1, card2, card3, card4, card5);
native bool:CheckFourOfAKind(card1, card2, card3, card4, card5);
```

#### Hand Evaluation

```pawn
native HandRank:GetHandRank(card1, card2, card3, card4, card5);
native GetBestHand(const cards[], cardsCount, bestHand[5]);
native CompareHands(hand1_card1, hand1_card2, hand1_card3, hand1_card4, hand1_card5, 
                    hand2_card1, hand2_card2, hand2_card3, hand2_card4, hand2_card5);
native GetHighestCard(card1, card2, card3, card4, card5);
```

#### Utility Functions

```pawn
native HandRankToString(HandRank:rank, string[], len = sizeof(string));
native CardValueToString(cardValue, string[], len = sizeof(string));
```

### Constants

The plugin provides constants for card values:

```pawn
#define CARD_TWO    2
#define CARD_THREE  3
...
#define CARD_KING   13
#define CARD_ACE    14
```

## Example

```pawn
new bool:isPair = CheckPair(CARD_ACE, CARD_ACE, CARD_KING, CARD_QUEEN, CARD_JACK);
printf("Is Pair: %s", isPair ? "Yes" : "No");

new HandRank:rank = GetHandRank(CARD_ACE, CARD_KING, CARD_QUEEN, CARD_JACK, CARD_TEN);
new rankName[32];
HandRankToString(rank, rankName);
printf("Hand Rank: %s", rankName);
```

## Testing

A comprehensive test script (`test_pokerchecker.pwn`) is provided to verify all functions of the plugin.
