# Poker Checker Plugin for SA:MP

This plugin provides comprehensive functions to evaluate and compare poker hands in SAMP scripts.

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

## Installation with sampctl

Run the following command in your project directory:

```bash
sampctl install Tramposo1312/poker-checker
```
After installation, include the plugin in your .pwn file:

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

## Building the Project

To build the Poker Checker plugin from source, follow these steps:

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

## Developing the Plugin Further

To extend the functionality of the Poker Checker plugin, consider the following:

1. **Understanding the Structure:**
   - `src/impl.hpp` and `src/impl.cpp`: Core implementation of poker logic
   - `src/natives.hpp` and `src/natives.cpp`: Bridge between PAWN and C++ code
   - `src/main.cpp`: Plugin entry point and native function registration

2. **Working with CMakeLists.txt:**
   - The `CMakeLists.txt` file in the root directory configures the build process
   - To add new source files:
     ```cmake
     add_library(pokerchecker SHARED
         ${EXISTING_SOURCE_FILES}
         src/your_new_file.cpp
     )
     ```
   - To link additional libraries:
     ```cmake
     target_link_libraries(pokerchecker
         ${EXISTING_LIBRARIES}
         your_new_library
     )
     ```
   - To add include directories:
     ```cmake
     target_include_directories(pokerchecker PRIVATE
         ${EXISTING_INCLUDE_DIRS}
         path/to/new/include/dir
     )
     ```
   - Remember to regenerate your build files after modifying CMakeLists.txt

3. **Adding New Functions:**
   - Implement the logic in `impl.cpp`
   - Add the function declaration to `impl.hpp`
   - Create a new native function in `natives.cpp` that calls your implementation
   - Add the native function declaration to `natives.hpp`
   - Register the new native in `main.cpp` by adding it to the `native_list` array
   - Update `POKER_CHECKER.inc` with the new native function for PAWN scripts

4. **Modifying Existing Functions:**
   - Locate the function in `impl.cpp`
   - Make your changes, ensuring you update any related functions
   - If the function signature changes, update it in `impl.hpp` and potentially in `natives.cpp`

5. **Testing:**
   - Add new test cases to `test_pokerchecker.pwn`
   - Run the test script on a SAMP server to verify your changes

## Missing Features

1. **Suit Support**: Adding suit support would allow for more accurate hand evaluations, including:
   - Proper flush detection
   - Straight flush and royal flush detection

2. **Probability Calculations**: Add functions to calculate the probability of improving a hand given the current cards and potential players' cards.

3. **Pot Odds Calculation**: Implement a function to calculate pot odds, which can help in decision-making during gameplay.

4. **Hand Strength Evaluation**: Feat an improved hand strength evaluator that takes into account not just the hand rank, but also the specific cards within that rank.

5. **Player Position Handling**: Add support for handling and evaluating the significance of player positions in a poker game.

6. **Hand History and Analysis**: Add features to record and analyze hand histories, which could be useful for player statistics and game review.

## Integration with playing-cards Library

To enhance the visual and textual representation of cards in your SAMP poker games, consider using the [`playing-cards`](https://github.com/DignitySAMP/omp-playing-cards) library alongside the Poker-Checker Plugin.

The `playing-cards` library complements Poker-Checker Plugin by providing:

1. Easy retrieval of card sprite names for rendering cards on screen
2. Simple functions to get human-readable card names
3. Consistent naming conventions for card sets and values

This combination allows you to handle both the game logic and the presentation aspects of your poker game efficiently.

For installation instructions, usage details, and examples, visit the official repository:

[https://github.com/DignitySAMP/omp-playing-cards](https://github.com/DignitySAMP/omp-playing-cards)

By combining these libraries, you can create more engaging and visually appealing poker games in SAMP, handling everything from game logic to user interface elements with ease.
