<!-- * Author: Noam Saida -->
<!-- ID: 212631071 -->
<!-- * Email: noamsayada1@gmail.com -->

# Catan Board Game Project

---

## Table of Contents
- [Overview](#overview)
- [Board Visuals](#board-visuals)
- [Project Layout](#project-layout)
- [Card System](#card-system)
- [Building and Running](#building-and-running)
- [Test Procedures](#test-procedures)

## Overview
This project is a coded version of the famous board game "Catan". Players gather resources, construct roads and settlements, and strive to accumulate winning points to win. The project is composed of classes for players, cards, the game board, and game logic that oversees turns and resource allocation.

## Board Visuals

The following images provide a visual representation of the board layout, along with the numbering system for hexagons, vertices, and edges.

### Board Layout Image
![Board Layout](Board%20Images/board.png)

### Hexagon, Edge, and Vertex Indices
![Hexagon, Edge, and Vertex Indices](Board%20Images/Board%20Indices.png)

## Project Layout
The project includes the following files and directories:

- **Header Files:**
    - `Card.hpp`: Base class for all card types.
    - `CardType.hpp`: Enumerates the different card types.
    - `DevelopmentCard.hpp`: Inherits from the Card class, for development cards.
    - `Dice.hpp`: Class to simulate dice rolls.
    - `Hexagon.hpp`: Class to represent a hexagon on the board.
    - `Vertex.hpp`: Class to represent a vertex on the board.
    - `Edge.hpp`: Class to represent a edge on the board.
    - `Player.hpp`: Class representing a game player.
    - `ResourceCard.hpp`: Derived class for resource cards.
    - `SpecialCard.hpp`: Derived class for special cards.

- **Source Files:**
    - `Card.cpp`: Implementation of the Card class.
    - `DevelopmentCard.cpp`: Implementation of the DevelopmentCard class.
    - `Dice.cpp`: Implementation of dice-related functionality.
    - `Hexagon.cpp`: Implementation of the Hexagon class.
    - `Vertex.cpp`: Implementation of the Vertex class.
    - `Edge.cpp`: Implementation of the Edge class.
    - `Player.cpp`: Implementation of the Player class.
    - `ResourceCard.cpp`: Implementation of the ResourceCard class.
    - `SpecialCard.cpp`: Implementation of the SpecialCard class.

- **Game Logic:**
    - `board.hpp` and `board.cpp`: Manage the game board.
    - `catan.hpp` and `catan.cpp`: Manage overall game logic.

- **Main and Test Files:**
    - `runGameMain.cpp`: Main entry point for running the game.
    - `Tests.cpp`: Contains various test cases
    - `run_tests.py`: Runs the game and test it's whole operation and managment with input&output.

- **Makefile**: 
    - Automates the build and run process.

## Card System
The card system is structured hierarchically for effective management of different card types.

- **Card (Base Class):**
    - The `Card` class acts as an abstract base for all cards, featuring a virtual destructor for proper cleanup and a pure virtual function that must be overridden by subclasses.
    - **Methods:**
        - `virtual ~Card() = default;`: Virtual destructor for cleanup.
        - `virtual CardType getType() const = 0;`: Pure virtual method to retrieve the card type.

- **ResourceCard (Inherits from Card):**
    - Represents resource cards (Lumber, Brick, Wool, Grain, Ore).
    - **Attributes:**
        - `CardType type`: Indicates the specific resource card type.
    - **Methods:**
        - `ResourceCard(CardType type);`: Constructor initializing the resource card type.
        - `CardType getType() const override;`: Retrieves the resource card type.

- **DevelopmentCard (Inherits from Card):**
    - Represents development cards (Knight, Victory Point, Road Building, Year of Plenty, Monopoly).
    - **Attributes:**
        - `CardType type`: Indicates the specific development card type.
    - **Methods:**
        - `DevelopmentCard(CardType type);`: Constructor initializing the development card type.
        - `CardType getType() const override;`: Retrieves the development card type.
    - **Derived Classes:**
        - `KnightCard`: Represents a Knight card.
        - `VictoryPointCard`: Represents a Victory Point card.
        - `RoadBuildingCard`: Represents a Road Building card.
        - `YearOfPlentyCard`: Represents a Year of Plenty card.
        - `MonopolyCard`: Represents a Monopoly card.

- **SpecialCard (Inherits from Card):**
    - Represents special cards like Largest Army.
    - **Attributes:**
        - `CardType type`: Indicates the specific special card type.
    - **Methods:**
        - `SpecialCard(CardType type);`: Constructor initializing the special card type.
        - `CardType getType() const override;`: Retrieves the special card type.
    - **Derived Classes:**
        - `LargestArmyCard`: Represents the Largest Army card.

## Building and Running

Utilize the included Makefile to build and execute the project.

### Running the Game

To compile and run the game:
```sh
make catan
./catan
```
### Cleaning Up To remove build artifacts:

```sh
make clean
```
The make clean command deletes all compiled object files and executables from the project.

## Test Procedures

### Unit Tests
- The `make test` command compiles the test executable.
- To execute the compiled test, use the `./test` command.

### System Tests
- The command `python run_tests.py` will use the catan excutable to run the system tests of the project. the results are printed to the terminal.