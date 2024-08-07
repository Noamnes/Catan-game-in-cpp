#include <iostream>
#include <vector>
#include "catan.hpp"

using namespace std;
using namespace ariel;
using std::endl, std::cin;

int main() {

    // Create three players
    Player player1("Alice");
    Player player2("Bob");
    Player player3("Charlie");

    // Initialize the Catan game with the three players
    Catan catanGame(player1, player2, player3);

    // Distribute the initial resource cards to all players
    catanGame.handFirstCards();

    // Choose the starting player
    catanGame.printStartingPlayer();

    // Player 1 places their initial roads and settlements
    catanGame.placeRoad(*catanGame.checkTurn(), 13);
    catanGame.placeRoad(*catanGame.checkTurn(), 41);
    catanGame.placeSettlement(*catanGame.checkTurn(), 10);
    catanGame.placeSettlement(*catanGame.checkTurn(), 29);

    // Move to the next player
    catanGame.nextPlayer();

    // Player 2 places their initial roads and settlements
    catanGame.placeRoad(*catanGame.checkTurn(), 56);
    catanGame.placeRoad(*catanGame.checkTurn(), 52);
    catanGame.placeSettlement(*catanGame.checkTurn(), 40);
    catanGame.placeSettlement(*catanGame.checkTurn(), 44);

    // Move to the next player
    catanGame.nextPlayer();

    // Player 3 places their initial roads and settlements
    catanGame.placeRoad(*catanGame.checkTurn(), 15);
    catanGame.placeRoad(*catanGame.checkTurn(), 58);
    catanGame.placeSettlement(*catanGame.checkTurn(), 13);
    catanGame.placeSettlement(*catanGame.checkTurn(), 42);

    // Move to the next player
    catanGame.nextPlayer();

    cout << endl << "Initial placements are completed." << endl;
    cout << endl << "Let the game begin!" << endl;

    // Distribute resources from adjacent hexagons to all players based on all possible dice rolls
    for (unsigned int rollResult = 2; rollResult <= 12; rollResult++) {
        catanGame.distributeResources(rollResult);
    }

    // Roll the dice and distribute resources based on the result
    unsigned int diceOutcome = catanGame.rollDices();
    cout << "Rolling the dice... the output is: " << diceOutcome << endl;
    catanGame.distributeResources(diceOutcome);

    // Handle special case if the dice outcome is 7
    if (diceOutcome == 7) {
        catanGame.handleSeven();
    }

    // Repeat dice rolling and resource distribution
    diceOutcome = catanGame.rollDices();
    cout << "Rolling the dice... the output is: " << diceOutcome << endl;
    catanGame.distributeResources(diceOutcome);

    if (diceOutcome == 7) {
        catanGame.handleSeven();
    }

    diceOutcome = catanGame.rollDices();
    cout << "Rolling the dice... the output is: " << diceOutcome << endl;
    catanGame.distributeResources(diceOutcome);

    if (diceOutcome == 7) {
        catanGame.handleSeven();
    }

    // Display the current state of the board
    cout << "Displaying the board\n" << endl;
    catanGame.displayBoard();

    // Show the cards held by each player
    catanGame.showPlayerCards(player1);
    catanGame.showPlayerCards(player2);
    catanGame.showPlayerCards(player3);

    // Show the points of each player
    catanGame.displayPoints();

    return 0;
}
