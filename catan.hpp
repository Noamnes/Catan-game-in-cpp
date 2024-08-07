// noam sayada
// noamsayada1@gmail.com

#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include "ResourceCard.hpp"
#include "DevelopmentCard.hpp"
#include "SpecialCard.hpp"
#include "player.hpp"
#include "Edge.hpp"
#include "board.hpp"
#include "CardType.hpp"
#include "Dice.hpp"

using namespace std;
// catan:
//      fields: Player turn; Players; vector<Card*> cards; map<cardIdx, player*> cardOwnership
//      functions: 
//                  io functions: printStartingPlayer, printWinner, displayBoard, showPlayerCards, cardTypeToString, displayPoints, menuForDiceSeven, buildMenu
//                  card management: 
//                                  general-card funcs: findAvailableCard, handleReturnCardsForSeven, handFirstCards, takeCard, returnCard2Deck, playerHasCards, distributeResources, handleSeven, isResourceCard, countPlayerResourceCards
//                                  specific-card funcs: updateLargestArmyCard, playMonopolyCard, takeMonopoly, playYearOfPlentyCard, buyDevCard
//                  turn management: checkTurn, advance turn, diceRole
//                  buying management: placeRoad/settlement/city, setRoadsandSettlements_auto, setRoadsandSettlements
//                  trading: sole func: tradeCards()
                  

namespace ariel {
    class Catan {
    private:
        Player turn;  // The player whose turn it is
        Board board;  // The game board
        Player player1;  // First player
        Player player2;  // Second player
        Player player3;  // Third player
        std::vector<Card*> cards;  // All cards in the game
        Dice dice;  // Dice object for rolling
        std::unordered_map<unsigned int, const Player*> cardOwnership;  // Map of card ownership

        // Find an available card of a given type.
        // type: The type of the card.
        // returns: The index of the available card.
        unsigned int findAvailableCard(CardType type);

        // Handle the return of resource cards when a 7 is rolled.
        // player: The player who needs to return cards.
        void handleReturnCardsForSeven(Player& player);

        const unsigned int cardNotAvailable = 1000; // Indicates card is not available.
        const unsigned int minPointsToWin = 10; // Minimum points required to win.

    public:
        // Construct a new Catan game with three players.
        // p1: The first player.
        // p2: The second player.
        // p3: The third player.
        Catan(const Player& p1, const Player& p2, const Player& p3);

        Catan();

        ~Catan();  // Destructor to clean up dynamically allocated memory

        // this func Starts the game by setting up players and initiating gameplay.
        void runGame();

        // START: IO FUNCTIONS
        // Print the starting player.
        void printStartingPlayer() const;

        // Print the winner of the game.
        void printWinner() const;

        // Display the current state of the board.
        void displayBoard() const;

        // Show the cards held by a player.
        // player: The player whose cards are to be displayed.
        void showPlayerCards(const Player& player) const;

        // Convert a CardType to its string representation.
        // cardType: The type of the card.
        // returns: The string representation of the card type.
        std::string cardTypeToString(CardType cardType) const;

        // Display the points of all players.
        void displayPoints();

        // Show a menu for a player to return cards when a 7 is rolled.
        // player: The player returning cards.
        void menuForDiceSeven(const Player& player);
        
        // Displays the menu for players to choose build actions.
        void buildMenu();
        
        // Shows the current status including player points and resources.
        void showStatus();

        // Welcomes players and initializes the player objects.
        void welcomeAndSetupPlayers();
        // END: IO FUNCTIONS

        // START: CARD MANAGEMENT:

        // START: general-card funcs

        // Distribute the initial resource cards to the players.
        void handFirstCards();

        // Give a card to a player.
        // player: The player to give the card to.
        // type: The type of card to give.
        // returns: True if the card was successfully given, false otherwise.
        bool takeCard(const Player& player, CardType type);

        // Return a card from a player to the bank.
        // player: The player returning the card.
        // type: The type of card to return.
        // amount: The amount of cards to return.
        // returns: True if the card was successfully returned, false otherwise.
        bool returnCard2Deck(const Player& player, CardType type, unsigned int amount);

        // Check if a player has a certain number of cards of a given type.
        // player: The player to check.
        // type: The type of card to check.
        // amount: The amount of cards to check for.
        // returns: True if the player has the required amount of cards, false otherwise.
        bool playerHasCards(const Player& player, CardType type, unsigned int amount) const;

        // Distribute resources based on the dice result.
        // diceResult: The result of the dice roll.
        void distributeResources(unsigned int diceResult);
        
        // Handle the event when a 7 is rolled on the dice.
        void handleSeven();
        
        // Check if a card type is a resource card.
        // type: The type of card.
        // returns: True if the card type is a resource card, false otherwise.
        bool isResourceCard(CardType type) const;

        // Count the number of resource cards held by a player.
        // player: The player whose cards are to be counted.
        // returns: The number of resource cards held by the player.
        unsigned int countPlayerResourceCards(const Player& player) const;

        void initilizeAllDeckCard();
        // END: general-card funcs

        // START: specific-card funcs
        // Manage the Largest Army card.
        void updateLargestArmyCard();

        // Play a Monopoly card.
        void playMonopolyCard();

        // Take all cards of a specific type from all players and give them to the player who played the Monopoly card.
        // player: The player who played the Monopoly card.
        // type: The type of card to take.
        void takeMonopoly(const Player& player, CardType type);

        // Play a Year of Plenty card.
        void playYearOfPlentyCard();
        
        // Allow a player to buy a development card.
        // player: The player buying the development card.
        // returns: True if the card was successfully bought, false otherwise.
        bool buyDevCard(const Player& player);
        // END: specific-card funcs
        
        // END: CARD MANAGEMENT

        // START: TURN MANAGEMENT
        // Get the player whose turn it is.
        // returns: Pointer to the current player.
        Player* checkTurn() { return &turn; }

        // Move to the next player's turn.
        // returns: The next player.
        Player nextPlayer();

        // Roll the dice.
        // returns: The sum of the dice rolls.
        unsigned int rollDices();
        // END: TURN MANAGEMENT
        
        // START: BUYING MANAGEMENT
        // Place a road on the board for a player.
        // player: The player placing the road.
        // edgeIndex: The index of the edge where the road is to be placed.
        // returns: True if the road was successfully placed, false otherwise.
        bool placeRoad(const Player& player, unsigned int edgeIndex);

        // Place a settlement on the board for a player.
        // player: The player placing the settlement.
        // vertexIndex: The index of the vertex where the settlement is to be placed.
        // returns: True if the settlement was successfully placed, false otherwise.
        bool placeSettlement(const Player& player, unsigned int vertexIndex);

        // Place a city on the board for a player.
        // player: The player placing the city.
        // vertexIndex: The index of the vertex where the city is to be placed.
        // returns: True if the city was successfully placed, false otherwise.
        bool placeCity(const Player& player, unsigned int vertexIndex);

        // Automatically sets initial roads and settlements for debugging.
        void setRoadsandSettlements_auto();

        // Sets initial roads and settlements for players.
        void setRoadsandSettlements();
        // END: BUYING MANAGEMENT

        // Add points to a player.
        // player: The player to add points to.
        // points: The number of points to add.
        void addPoints(const Player& player, unsigned int points);

        // Allow a player to trade cards with another player.
        // player: The player initiating the trade.
        void tradeCards(const Player &player);

        // Retrieve the current state of the game board.
        // returns: The current game board.
        Board getBoard();
    };
}
