# Poker Checker Plugin for SA:MP

This plugin provides comprehensive functions to evaluate and compare poker hands in SAMP scripts.

## Features

- Check for various poker hands (Pair, Two Pairs, Three of a Kind, Straight, Flush, Full House, Four of a Kind)
- Determine the best hand from a set of cards
- Compare two poker hands
- Get the highest card from a hand
- Convert hand ranks and card values to string representations
- Support for card suits

## Installation

1. Copy the `pokerchecker.dll` (Windows) or `pokerchecker.so` (Linux) to your server's `plugins` folder.
2. Add `pokerchecker` to the `plugins` line in your `server.cfg` file.
3. Copy `POKER_CHECKER.inc` to your `pawno/include` directory.

## Installation with sampctl

Run this command in your project directory:

```bash
sampctl install Tramposo1312/poker-checker
```
After installation, include the plugin in your .pwn file:

```pawn
#include <POKER_CHECKER>
```

## Available Functions

### Card Creation and Manipulation
```pawn
native Card:CreateCard(value, Suit:suit);
native GetCardValue(Card:card);
native Suit:GetCardSuit(Card:card);
```

### Hand-Checking Functions
```pawn
native bool:CheckPair(Card:card1, Card:card2, Card:card3, Card:card4, Card:card5);
native bool:CheckTwoPairs(Card:card1, Card:card2, Card:card3, Card:card4, Card:card5);
native bool:CheckThreeOfAKind(Card:card1, Card:card2, Card:card3, Card:card4, Card:card5);
native bool:CheckStraight(Card:card1, Card:card2, Card:card3, Card:card4, Card:card5);
native bool:CheckFlush(Card:card1, Card:card2, Card:card3, Card:card4, Card:card5);
native bool:CheckFullHouse(Card:card1, Card:card2, Card:card3, Card:card4, Card:card5);
native bool:CheckFourOfAKind(Card:card1, Card:card2, Card:card3, Card:card4, Card:card5);
native bool:CheckStraightFlush(Card:card1, Card:card2, Card:card3, Card:card4, Card:card5);
native bool:CheckRoyalFlush(Card:card1, Card:card2, Card:card3, Card:card4, Card:card5);
```

### Hand Evaluation Functions
```pawn
native HandRank:GetHandRank(Card:card1, Card:card2, Card:card3, Card:card4, Card:card5);
native GetBestHand(const Card:cards[], cardsCount, Card:bestHand[5]);
native CompareHands(Card:hand1_card1, Card:hand1_card2, Card:hand1_card3, Card:hand1_card4, Card:hand1_card5, 
                    Card:hand2_card1, Card:hand2_card2, Card:hand2_card3, Card:hand2_card4, Card:hand2_card5);
native Card:GetHighestCard(Card:card1, Card:card2, Card:card3, Card:card4, Card:card5);
```

### Utility Functions
```pawn
native HandRankToString(HandRank:rank, string[], len = sizeof(string));
native CardValueToString(cardValue, string[], len = sizeof(string));
native SuitToString(Suit:suit, string[], len = sizeof(string));
```

### Constants

The plugin provides constants for card values:

```pawn
#define CARD_TWO    2
#define CARD_THREE  3
...
#define CARD_KING   13
#define CARD_ACE    14

enum Suit {
    Suit_Hearts,
    Suit_Diamonds,
    Suit_Clubs,
    Suit_Spades
}
```
## Example

```pawn
new Card:hand[5];
hand[0] = CreateCard(CARD_ACE, Suit_Hearts);
hand[1] = CreateCard(CARD_KING, Suit_Hearts);
hand[2] = CreateCard(CARD_QUEEN, Suit_Hearts);
hand[3] = CreateCard(CARD_JACK, Suit_Hearts);
hand[4] = CreateCard(CARD_TEN, Suit_Hearts);

new HandRank:rank = GetHandRank(hand[0], hand[1], hand[2], hand[3], hand[4]);
new rankName[32];
HandRankToString(rank, rankName);
printf("Hand Rank: %s", rankName);
```


## Testing

A comprehensive test script (`test_pokerchecker.pwn`) is provided to verify all functions of the plugin.

## Building the Project

To build the Poker Checker plugin from source:

1. **Prerequisites:**
   - Install a C++ compiler (Visual Studio on Windows, GCC on Linux)
   - Install CMake (version 3.10 or later)

2. **Setup:**
   - Clone this repository:
     ```
     git clone https://github.com/Tramposo1312/poker-checker.git
     cd poker-checker
     ```
   - 
3. **Build:**
   - Create a build directory:
     ```
     mkdir build
     cd build
     ```
   - Generate build files with CMake:
     - For Windows: `cmake -G "Visual Studio 17 2022" [or whatever your compiler version is] -A Win32 ..`
     - For Linux: `cmake ..`
   - Build the project:
     - For Windows: `cmake --build . --config Release`
     - For Linux: `make`

4. **Output:**
   - The compiled plugin (`pokerchecker.dll` or `pokerchecker.so`) will be in the `build/Release` directory on Windows or the `build` directory on Linux

## Developing the Plugin

1. **Understand the Structure:**
   - `src/impl.hpp` and `src/impl.cpp`: Core implementation of poker logic
   - `src/natives.hpp` and `src/natives.cpp`: Bridge between PAWN and C++ code
   - `src/main.cpp`: Plugin entry point and native function registration

2. **Working with CMakeLists.txt:**
   - The `CMakeLists.txt` file in the root directory configures the build process
   - Add new source files:
     ```cmake
     add_library(pokerchecker SHARED
         ${EXISTING_SOURCE_FILES}
         src/new_file.cpp
     )
     ```
   - Link additional libraries:
     ```cmake
     target_link_libraries(pokerchecker
         ${EXISTING_LIBRARIES}
         new_library
     )
     ```
   - To add include directories:
     ```cmake
     target_include_directories(pokerchecker PRIVATE
         ${EXISTING_INCLUDE_DIRS}
         path/include/dir
     )
     ```
   - Always regenerate your build files after modifying CMakeLists.txt

3. **Adding New Functions:**
   - Implement the logic in `impl.cpp`
   - Add the function declaration to `impl.hpp`
   - Create a new native function in `natives.cpp` that calls your implementation
   - Add the native function declaration to `natives.hpp`
   - Register the new native in `main.cpp` by adding it to the `native_list` array
   - Update `POKER_CHECKER.inc` with the new native function for PAWN scripts

4. **Testing:**
   - Add new test cases to `test_pokerchecker.pwn`
   - Run the test script on a SAMP server to verify your changes

## Integration with playing-cards Library

To enhance the visual representation of cards in your SAMP poker script, use the [`playing-cards`](https://github.com/DignitySAMP/omp-playing-cards)

This combination allows you to handle both the game logic and the presentation aspects of your poker game efficiently.

By combining these libraries, you can easily create more engaging and visually appealing poker games in your SAMP script, handling everything from game logic to user interface elements.
