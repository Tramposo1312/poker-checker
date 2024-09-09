# Poker Checker Plugin for SA:MP

This plugin provides functions to evaluate poker hands in SA:MP scripts.

## Features

- Check for various poker hands (Pair, Two Pairs, Three of a Kind, Four of a Kind)
- Determine the best hand from a set of cards
- Find the highest card in a hand
- Convert card values to string representations

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
native bool:CheckPair(card1, card2, card3, card4);
native bool:CheckTwoPairs(card1, card2, card3, card4);
native bool:CheckThreeOfAKind(card1, card2, card3, card4);
native bool:CheckFourOfAKind(card1, card2, card3, card4);
```

Example:
```pawn
new bool:hasPair = CheckPair(5, 5, 7, 9);
printf("Has Pair: %s", hasPair ? "Yes" : "No");
```

#### Get Best Hand

```pawn
native HandRank:GetBestHand(card1, card2, card3, card4);
```

Example:
```pawn
new HandRank:bestHand = GetBestHand(5, 5, 5, 9);
printf("Best Hand: %s", GetHandRankName(bestHand));
```

#### Get Highest Card

```pawn
native GetHighestCard(card1, card2, card3, card4);
```

Example:
```pawn
new highestCard = GetHighestCard(5, 10, 7, 9);
printf("Highest Card: %d", highestCard);
```

#### Convert Card Value to String

```pawn
native CardValueToString(cardValue, string[], len = sizeof(string));
```

Example:
```pawn
new cardString[32];
CardValueToString(14, cardString, sizeof(cardString));
printf("Card: %s", cardString); // Output: "Card: Ace"
```

### Hand Rank Enumeration

```pawn
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
```

## Example Script

Here's a complete example demonstrating all features:

```pawn
#include <a_samp>
#include <POKER_CHECKER>

main() {
    // Check for a pair
    new bool:hasPair = CheckPair(5, 5, 7, 9);
    printf("Has Pair: %s", hasPair ? "Yes" : "No");

    // Get best hand
    new HandRank:bestHand = GetBestHand(5, 5, 5, 9);
    printf("Best Hand: %d", _:bestHand);

    // Get highest card
    new highestCard = GetHighestCard(5, 10, 7, 9);
    printf("Highest Card: %d", highestCard);

    // Convert card value to string
    new cardString[32];
    CardValueToString(14, cardString, sizeof(cardString));
    printf("Card: %s", cardString);
}
```

## Notes

- Card values range from 2 to 14, where 11 = Jack, 12 = Queen, 13 = King, and 14 = Ace.
- This plugin does not currently handle card suits.

## Future Enhancements

- Add support for card suits
- Implement Straight and Flush detection
- Add hand comparison functionality

## Support

For issues, feature requests, or contributions, please [open an issue](https://github.com/yourusername/pokerchecker/issues) on the GitHub repository.