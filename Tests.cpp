#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "catan.hpp"
#include "board.hpp"
#include "player.hpp"
#include "CardType.hpp"
#include "ResourceCard.hpp"
#include "DevelopmentCard.hpp"
#include "SpecialCard.hpp"
#include "Dice.hpp"

#include <set>
#include <sstream>
#include <iostream>

using namespace ariel;

// very simple Player tests. no logic is tested.
TEST_CASE("Player tests") {
    Player player1("Alice");
    Player player2("Bob");

    CHECK(player1.getName() == "Alice");
    CHECK(player2.getName() == "Bob");

    player1.addPoints(3);
    player2.addPoints(5);
    CHECK(player1.getPoints() == 3);
    CHECK(player2.getPoints() == 5);

    player1.reducePoints(1);
    CHECK(player1.getPoints() == 2);

    player2.addKnights(2);
    CHECK(player2.getKnights() == 2);
}

// very simple Card types tests. no logic is tested.
TEST_CASE("CardType tests") {
    ResourceCard lumber(CardType::Lumber);
    DevelopmentCard knight(CardType::Knight);
    SpecialCard largestArmy(CardType::LargestArmy);

    CHECK(lumber.getType() == CardType::Lumber);
    CHECK(knight.getType() == CardType::Knight);
    CHECK(largestArmy.getType() == CardType::LargestArmy);
}

// very simple dice tests.
TEST_CASE("Dice tests") {
    Dice dice;
    std::set<unsigned int> numbersRolled;

    for (int i = 0; i < 200; ++i) {
        unsigned int result = dice.roll();
        // chech if the restult is within the 1-6 range
        CHECK(result >= 1);
        CHECK(result <= 6);
        numbersRolled.insert(result);
    }

    // for 200 rolls of a fair dice, all numbers should be present:
    for (unsigned int num = 1; num <= 6; ++num) {
        CHECK(numbersRolled.count(num) > 0); // is present?
    }
}

// need to go through!
TEST_CASE("Vertex tests") {
    Player player1("Alice");
    Vertex vertex(1);

    CHECK(vertex.getIndex() == 1);
    CHECK(vertex.getStructure() == None);
    CHECK(vertex.getOwner() == nullptr);

    vertex.setStructure(Settlement, player1);
    CHECK(vertex.getStructure() == Settlement);

    Hexagon hex(CardType::Lumber, 5, 0, 0);
    vertex.addAdjacentHexagon(0, 0);
    CHECK(vertex.isAdjacentTo(hex));
}
// need to go through!
TEST_CASE("Edge tests") {
    Player player1("Alice");
    Edge edge(1, 0, 1);

    CHECK(edge.getIndex() == 1);
    auto vertexPair = edge.getVertices();
    CHECK(vertexPair.first == 0);
    CHECK(vertexPair.second == 1);

    CHECK(edge.getOwner() == nullptr);
    CHECK(edge.setOwner(&player1));
    CHECK(edge.getOwner() == &player1);
    CHECK_FALSE(edge.setOwner(&player1));
}
// need to go through!
TEST_CASE("Largest Army Card Management") {
    Player player1("Alice");
    Player player2("Bob");
    Player player3("Charlie");

    Catan game(player1, player2, player3);

    game.takeCard(player1, CardType::Knight);
    game.takeCard(player1, CardType::Knight);
    game.takeCard(player1, CardType::Knight);

    game.updateLargestArmyCard();
    CHECK(game.playerHasCards(player1, CardType::LargestArmy, 1));

    game.takeCard(player2, CardType::Knight);
    game.takeCard(player2, CardType::Knight);
    game.takeCard(player2, CardType::Knight);
    game.takeCard(player2, CardType::Knight);

    game.updateLargestArmyCard();
    CHECK_FALSE(game.playerHasCards(player1, CardType::LargestArmy, 1));
    CHECK(game.playerHasCards(player2, CardType::LargestArmy, 1));
}

// checks: the basic behivior of the board class.
TEST_CASE("Board initialization") {
    Board board;
    
    // check the expected shape and structure of the board:
    CHECK(board.getHexagons().size() == 19);
    CHECK(board.getVertexs().size() == 54);
    CHECK(board.getEdge2Vertexs().size() == 72);

    // check that the hexagons are initialized with the right types and numbers:
    auto hex = board.getHexagon(0, 0);
    CHECK(hex.getType() == HexagonTypes[0]);
    CHECK(hex.getNumber() == HexagonNumbers[0]);

    // checks throwing exceptions in case of out of bounds access:
    CHECK_THROWS_AS(board.getHexagon(10, 10), std::invalid_argument);
    CHECK_THROWS_AS(board.getVertex(100), std::invalid_argument);
    CHECK_THROWS_AS(board.getEdge(100), std::invalid_argument);
}

TEST_CASE("Catan tests") {
    Player player1("Alice");
    Player player2("Bob");
    Player player3("Charlie");

    cout << endl;
    Catan catan(player1, player2, player3);// create a copy of the players!

    CHECK(catan.checkTurn()->getName() == "Alice");

    catan.handFirstCards(); //changes cardOwnership using TakeCard()
    CHECK(catan.playerHasCards(player1, CardType::Lumber, 4));
    CHECK(catan.playerHasCards(player1, CardType::Brick, 4));
    CHECK(catan.playerHasCards(player1, CardType::Wool, 2));
    CHECK(catan.playerHasCards(player1, CardType::Grain, 2));

    CHECK_FALSE(catan.playerHasCards(player1, CardType::Lumber, 5));
    CHECK_FALSE(catan.playerHasCards(player1, CardType::Brick, 5));
    CHECK_FALSE(catan.playerHasCards(player1, CardType::Wool, 3));
    CHECK_FALSE(catan.playerHasCards(player1, CardType::Grain, 3));

    // should return true cause player 1 has the required resources and the board is empty for building a road.
    CHECK(catan.placeRoad(player1, 13)); 
    // should return false cause player 1 already built a road on this edge.
    CHECK_FALSE(catan.placeRoad(player1, 13));
    // should return true cause player 1 has the required resources and the board is empty except for edge 13
    CHECK(catan.placeSettlement(player1, 10));
     // should return false cause player 1 already built a settlement on this vertex.
    CHECK_FALSE(catan.placeSettlement(player1, 10));

    unsigned int roll = catan.rollDices();
    CHECK(roll >= 2);
    CHECK(roll <= 12);

    CHECK_NOTHROW(catan.distributeResources(roll));
    CHECK_NOTHROW(catan.displayPoints());
}

TEST_CASE("Settlement and City placement tests") {
    Player player1("Alice");
    Player player2("Bob");
    Player player3("Charlie");

    Catan catan(player1, player2, player3);

    catan.handFirstCards();

    catan.placeRoad(player1, 13);
    catan.placeRoad(player1, 41);
    catan.placeSettlement(player1, 10);
    catan.placeSettlement(player1, 29);

    catan.nextPlayer();
    catan.placeRoad(player2, 56);
    catan.placeRoad(player2, 52);
    catan.placeSettlement(player2, 40);
    catan.placeSettlement(player2, 44);

    catan.nextPlayer();
    catan.placeRoad(player3, 15);
    catan.placeRoad(player3, 58);
    catan.placeSettlement(player3, 13);
    catan.placeSettlement(player3, 42);

    catan.nextPlayer();

    catan.takeCard(player1, CardType::Ore);
    catan.takeCard(player1, CardType::Ore);
    catan.takeCard(player1, CardType::Ore);
    catan.takeCard(player1, CardType::Grain);
    catan.takeCard(player1, CardType::Grain);

    catan.takeCard(player2, CardType::Ore);
    catan.takeCard(player2, CardType::Ore);
    catan.takeCard(player2, CardType::Ore);
    catan.takeCard(player2, CardType::Grain);
    catan.takeCard(player2, CardType::Grain);

    catan.takeCard(player3, CardType::Ore);
    catan.takeCard(player3, CardType::Ore);
    catan.takeCard(player3, CardType::Ore);
    catan.takeCard(player3, CardType::Grain);
    catan.takeCard(player3, CardType::Grain);

    CHECK_FALSE(catan.placeCity(player1, 20));
    CHECK_FALSE(catan.placeCity(player1, 40));
    CHECK(catan.placeCity(player1, 10));

    auto& vertex = catan.getBoard().getVertex(10);
    CHECK(vertex.getStructure() == City);
    CHECK(vertex.getOwner()->getName() == player1.getName());
}
