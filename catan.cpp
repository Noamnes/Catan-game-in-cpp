/** noam sayada
 *  noamsayada1@gmail.com
 */

#include "catan.hpp"
#include "Vertex.hpp"
#include "Hexagon.hpp"
#include "CardType.hpp"
#include <numeric>

using namespace std;

namespace ariel {

// Constructor
Catan::Catan(const Player &p1, const Player &p2, const Player &p3) : turn(p1), player1(p1), player2(p2), // create a deep copy of the players
                                                                     player3(p3), dice() {
    initilizeAllDeckCard();
}

Catan::Catan() : dice(){
    initilizeAllDeckCard(); // initilize deck of cards
    welcomeAndSetupPlayers(); // get players names
    turn = player1; // set the turn to palyer1
    handFirstCards(); // Hand out initial cards to players
    printStartingPlayer(); // Print the starting player
}

void Catan::initilizeAllDeckCard(){
    for (unsigned int i = 0; i < 19; ++i) {
        cards.push_back(new ResourceCard(CardType::Lumber));
    }
    for (unsigned int i = 0; i < 19; ++i) {
        cards.push_back(new ResourceCard(CardType::Brick));
    }
    for (unsigned int i = 0; i < 19; ++i) {
        cards.push_back(new ResourceCard(CardType::Wool));
    }
    for (unsigned int i = 0; i < 19; ++i) {
        cards.push_back(new ResourceCard(CardType::Grain));
    }
    for (unsigned int i = 0; i < 19; ++i) {
        cards.push_back(new ResourceCard(CardType::Ore));
    }

    for (unsigned int i = 0; i < 14; ++i) {
        cards.push_back(new KnightCard());
    }
    for (unsigned int i = 0; i < 5; ++i) {
        cards.push_back(new VictoryPointCard());
    }
    for (unsigned int i = 0; i < 2; ++i) {
        cards.push_back(new RoadBuildingCard());
    }
    for (unsigned int i = 0; i < 2; ++i) {
        cards.push_back(new YearOfPlentyCard());
    }
    for (unsigned int i = 0; i < 2; ++i) {
        cards.push_back(new MonopolyCard());
    }

    cards.push_back(new LargestArmyCard());
}

// Destructor
Catan::~Catan() {
    for (Card *card: cards) {
        delete card;
    }
}

void Catan::runGame() {
    unsigned int resultOfDice;
    bool diceRolled = false;

    // Distribute resources from adjacent hexagons to all players
    for (unsigned int i = 2; i <= 12; i++) {
        distributeResources(i);
    }

    // Main game loop
    while (true) {
        std::cout << std::endl;
        std::cout << checkTurn()->getName() << ", it's your turn." << std::endl << std::endl;
        std::cout << "Choose action: " << std::endl;
        std::cout << "1. Roll Dice" << std::endl;
        std::cout << "2. Build" << std::endl;
        std::cout << "3. Trade" << std::endl;
        std::cout << "4. Buy Development Card" << std::endl;
        std::cout << "5. Show status" << std::endl;
        std::cout << "6. End Turn" << std::endl;
        std::cout << "7. End the Game" << std::endl;

        int choice;
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                if (!diceRolled) {
                    diceRolled = true;
                    resultOfDice = rollDices(); // Roll the dice
                    std::cout << std::endl << "Rolling dice... The result is: " << resultOfDice << std::endl;
                    distributeResources(resultOfDice); // Distribute resources based on the dice result
                } else {
                    std::cout << std::endl << "You have already rolled the dice this turn." << std::endl;
                }
                if (resultOfDice == 7) {
                    handleSeven(); // Handle special case when 7 is rolled
                }
                break;
            case 2:
                buildMenu(); // Show build options
                break;
            case 3:
                tradeCards(*checkTurn()); // Manage trading of cards
                break;
            case 4:
                buyDevCard(*checkTurn()); // Buy development card
                break;
            case 5:
                showStatus(); // Show the current status of the game
                break;
            case 6:
                nextPlayer(); // Move to the next player
                diceRolled = false;
                break;
            case 7:
                std::cout << "Exiting the game" << std::endl;
                exit(EXIT_SUCCESS); // Exit the game
                break;
            case EOF:
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }

        // Check if EOF is reached
        if (std::cin.eof()) {
            std::cout << "EOF reached. Exiting the game." << std::endl;
            break;
        }
    }
}

void Catan::printStartingPlayer() const {
    cout << endl << "The starting player is: " << turn.getName() << "!" << endl;
}

Player Catan::nextPlayer() {
    if (turn.getPoints() >= minPointsToWin) {
        cout << endl << turn.getName() << " is the winner with " << turn.getPoints() << " victory points!!!" << endl;
        cout << endl << "GAME OVER!" << endl;
        exit(EXIT_SUCCESS);
    }

    if (turn.getName() == player1.getName()) {
        turn = player2;
        return player2;
    } else if (turn.getName() == player2.getName()) {
        turn = player3;
        return player3;
    } else {
        turn = player1;
        return player1;
    }
}

unsigned int Catan::rollDices() {
    return dice.roll() + dice.roll(); // TODO: uncomment this line to run the game properly, without tests.
    // return 12; // uncomment this line to run the tests.
}

void Catan::handFirstCards() {
    Player players[] = {player1, player2, player3}; // creates a copy of the catan's players.

    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int j = 0; j < 4; ++j) {
            takeCard(players[i], CardType::Lumber);
            takeCard(players[i], CardType::Brick);
        }
        for (unsigned int j = 0; j < 2; ++j) {
            takeCard(players[i], CardType::Wool);
            takeCard(players[i], CardType::Grain);
        }
    }

    cout << "Each player has received the initial resource cards: 4 Lumber, 4 Bricks, 2 Wool, and 2 Grain." << endl;
    cout << "Before the game begins, each player shall build two roads and two settlements using these cards." << endl;
}

bool Catan::takeCard(const Player &player, CardType type) {
    unsigned int cardNumber = findAvailableCard(type);

    if (cardNumber != cardNotAvailable) {
        Player *players[] = {&player1, &player2, &player3};

        for (auto *currentPlayer: players) {
            // chaking unique identifier other then mem address! 
            // cause the adress could be always different (as in "handFirstCards" function)
            if (player.getName() == currentPlayer->getName()) { 
                cardOwnership[cardNumber] = currentPlayer;

                if (type == CardType::Knight) {
                    currentPlayer->addKnights(1);
                }

                return true;
            }
        }
    }

    cout << "Card of type " << cardTypeToString(type) << " is not available." << endl;
    return false;
}

bool Catan::returnCard2Deck(const Player &player, CardType type, unsigned int amount) {
    unsigned int counter = 0;
    std::vector<unsigned int> cardsToErase;

    for (const auto &entry: cardOwnership) {
        unsigned int card = entry.first;
        if ((cards[card]->getType() == type) && (entry.second->getName() == player.getName())) {
            cardsToErase.push_back(card);
            counter++;
        }
        if (counter == amount) {
            if (!cardsToErase.empty()) {
                for (unsigned int card: cardsToErase) {
                    cardOwnership.erase(card);
                }
            }
            return true;
        }
    }
    cout << "No card of type " << cardTypeToString(type) << " owned by " << player.getName() << " found." << endl;
    return false;
}

unsigned int Catan::findAvailableCard(CardType type) {
    for (unsigned int i = 0; i < cards.size(); i++) {
        if (cards[i]->getType() == type && cardOwnership.find(i) == cardOwnership.end()) {
            return i;
        }
    }
    return cardNotAvailable;
}

bool Catan::playerHasCards(const Player &player, CardType type, unsigned int amount) const {
    unsigned int count = 0;

    for (const auto &entry: cardOwnership) {
        if (entry.second->getName() == player.getName() && cards[entry.first]->getType() == type) {
            count++;
            if (count >= amount) {
                return true;
            }
        }
    }
    return false;
}

bool Catan::placeRoad(const Player &player, unsigned int edgeIndex) {
    if (edgeIndex >= board.getEdge2VertexsSize()) {
        std::cout << "Edge index is out of bound." << std::endl;
        return false;
    }

    if (board.getEdge(edgeIndex).getOwner() != nullptr) {
        std::cout << "This edge is already occupied." << std::endl;
        return false;
    }

    if (!playerHasCards(player, CardType::Lumber, 1) || !playerHasCards(player, CardType::Brick, 1)) {
        std::cout << "You don't have the required resources (1 Lumber and 1 Brick) to build a road." << std::endl;
        return false;
    }

    returnCard2Deck(player, CardType::Lumber, 1);
    returnCard2Deck(player, CardType::Brick, 1);

    std::vector<Player *> players = {&player1, &player2, &player3};

    for (Player *p: players) {
        if (player.getName() == p->getName()) {
            board.getEdge(edgeIndex).setOwner(p);
            break;
        }
    }

    std::cout << player.getName() << ", your road has been placed on edge " << edgeIndex << "." << std::endl;
    return true;
}

bool Catan::placeSettlement(const Player &player, unsigned int vertexIndex) {
    if (vertexIndex >= board.getVertex2HexagonsSize()) {
        std::cout << "Vertex index is out of bound." << std::endl;
        return false;
    }

    if (board.getVertex(vertexIndex).getOwner() != nullptr) {
        std::cout << "Vertex " << vertexIndex << " is already occupied." << std::endl;
        return false;
    }

    for (const auto &edge: board.getEdge2Vertexs()) {
        if ((edge.first == vertexIndex && board.getVertex(edge.second).getOwner() != nullptr) ||
            (edge.second == vertexIndex && board.getVertex(edge.first).getOwner() != nullptr)) {
            std::cout
                    << "Illegal place to place settlement. Too close to another settlement/city. Please try again."
                    << std::endl;
            return false;
        }
    }

    bool hasAdjacentRoad = false;
    for (unsigned int i = 0; i < board.getEdge2VertexsSize(); i++) {
        auto vertexs = board.getEdge(i).getVertices();
        if ((board.getEdge(i).getOwner() != nullptr) &&
            (board.getEdge(i).getOwner()->getName() == player.getName()) &&
            ((vertexs.first == vertexIndex) || (vertexs.second == vertexIndex))) {
            hasAdjacentRoad = true;
            break;
        }
    }
    if (!hasAdjacentRoad) {
        std::cout
                << "Illegal place to place settlement. You must have at least one road adjacent to the vertex. Please try again." << std::endl;
                return false;
            }

            if (!playerHasCards(player, CardType::Lumber, 1) ||
                !playerHasCards(player, CardType::Brick, 1) ||
                !playerHasCards(player, CardType::Wool, 1) ||
                !playerHasCards(player, CardType::Grain, 1)) {
                std::cout << player.getName()
                          << ", you do not have the required resources (1 Lumber, 1 Brick, 1 Wool, and 1 Grain) to build a settlement."
                          << std::endl;
                return false;
            }

            returnCard2Deck(player, CardType::Lumber, 1);
            returnCard2Deck(player, CardType::Brick, 1);
            returnCard2Deck(player, CardType::Wool, 1);
            returnCard2Deck(player, CardType::Grain, 1);

            std::vector<Player *> players = {&player1, &player2, &player3};

            for (Player *p: players) {
                if (player.getName() == p->getName()) {
                    board.getVertex(vertexIndex).setStructure(Structure::Settlement, *p);
                    break;
                }
            }

            std::cout << player.getName() << ", your settlement has been placed on vertex " << vertexIndex << "." << std::endl;
            addPoints(player, 1);
            return true;
}

bool Catan::placeCity(const Player &player, unsigned int vertexIndex) {
    if (vertexIndex >= board.getVertex2HexagonsSize()) {
        std::cout << "Vertex index is out of bound." << std::endl;
        return false;
    }

    if ((board.getVertex(vertexIndex).getOwner() != nullptr) &&
        (board.getVertex(vertexIndex).getOwner()->getName() != player.getName())) {
        std::cout << "This vertex is not owned by " << player.getName() << std::endl;
        return false;
    }

    if (board.getVertex(vertexIndex).getStructure() != Structure::Settlement) {
        std::cout << "Can't upgrade to city because there isn't a Settlement on the vertex." << std::endl;
        return false;
    }

    if (!playerHasCards(player, CardType::Ore, 3) || !playerHasCards(player, CardType::Grain, 2)) {
        std::cout << "You do not have the required resources (3 Ore and 2 Grain) to build a city." << std::endl;
        return false;
    }

    returnCard2Deck(player, CardType::Ore, 3);
    returnCard2Deck(player, CardType::Grain, 2);

    std::vector<Player *> players = {&player1, &player2, &player3};

    for (Player *p: players) {
        if (player.getName() == p->getName()) {
            board.getVertex(vertexIndex).setStructure(Structure::City, *p);
            break;
        }
    }

    std::cout << player.getName() << ", your city has been placed." << std::endl;
    addPoints(player, 1);
    return true;
}

void Catan::setRoadsandSettlements_auto() {
    // Automatically place roads and settlements for debugging
    placeRoad(*checkTurn(), 13);
    placeRoad(*checkTurn(), 41);
    placeSettlement(*checkTurn(), 10);
    placeSettlement(*checkTurn(), 29);

    nextPlayer();

    placeRoad(*checkTurn(), 56);
    placeRoad(*checkTurn(), 52);
    placeSettlement(*checkTurn(), 40);
    placeSettlement(*checkTurn(), 44);

    nextPlayer();

    placeRoad(*checkTurn(), 15);
    placeRoad(*checkTurn(), 58);
    placeSettlement(*checkTurn(), 13);
    placeSettlement(*checkTurn(), 42);
    nextPlayer();
    std::cout << std::endl << "Initial placements are completed." << std::endl;
    std::cout << std::endl << "Let the game begin!" << std::endl;
}

void Catan::setRoadsandSettlements() {
    unsigned int index;
    bool buildSuccess;
    int counter;

    for (unsigned int i = 0; i < 3; i++) {
        counter = 0;
        while (counter < 2) {
            std::cout << std::endl << checkTurn()->getName() << ", please choose an index for your road: ";
            std::cin >> index;
            buildSuccess = placeRoad(*checkTurn(), index); // Place road

            if (buildSuccess) {
                counter++;
            }
        }
        counter = 0;

        while (counter < 2) {
            std::cout << std::endl << checkTurn()->getName() << ", please choose an index for your settlement: ";
            std::cin >> index;
            buildSuccess = placeSettlement(*checkTurn(), index); // Place settlement

            if (buildSuccess) {
                counter++;
            }
        }
        nextPlayer(); // Move to the next player
    }
    std::cout << std::endl << "Initial placements are completed." << std::endl;
    std::cout << std::endl << "Let the game begin!" << std::endl;
}

void Catan::displayBoard() const {
    board.showVertexs();
    board.showRoads();
}

void Catan::showPlayerCards(const Player &player) const {
    std::unordered_map<CardType, int> cardCounts;
    unsigned int totalCards = 0;

    for (const auto &entry: cardOwnership) {
        if (entry.second->getName() == player.getName()) {
            CardType cardType = cards.at(entry.first)->getType();
            cardCounts[cardType]++;
            totalCards++;
        }
    }

    if (totalCards > 0) {
        std::cout << std::endl << player.getName() << " has the following cards:" << std::endl;
        for (const auto &count: cardCounts) {
            std::cout << cardTypeToString(count.first) << ": " << count.second << std::endl;
        }
    } else {
        std::cout << std::endl << player.getName() << " has no cards." << std::endl;
    }
}

std::string Catan::cardTypeToString(CardType cardType) const {
    switch (cardType) {
        case CardType::Lumber:
            return "Lumber";
        case CardType::Brick:
            return "Brick";
        case CardType::Wool:
            return "Wool";
        case CardType::Grain:
            return "Grain";
        case CardType::Ore:
            return "Ore";
        case CardType::Knight:
            return "Knight";
        case CardType::VictoryPoint:
            return "Victory Point";
        case CardType::RoadBuilding:
            return "Road Building";
        case CardType::YearOfPlenty:
            return "Year of Plenty";
        case CardType::Monopoly:
            return "Monopoly";
        case CardType::LargestArmy:
            return "Largest Army";
        default:
            return "Unknown";
    }
}

void Catan::displayPoints() {
    std::cout << std::endl << "Scoreboard:" << std::endl;

    std::vector<Player *> players = {&player1, &player2, &player3};

    for (Player *p: players) {
        std::cout << p->getName() << " has " << p->getPoints() << " points" << std::endl;
    }
}

void Catan::addPoints(const Player &player, unsigned int points) {
    std::vector<Player *> players = {&player1, &player2, &player3};

    for (Player *p: players) {
        if (player.getName() == p->getName()) {
            p->addPoints(points);
            break;
        }
    }
}

void Catan::distributeResources(unsigned int diceResult) {
    CardType hexCard;

    std::vector<Hexagon> matchingHexagons;
    for (const auto &hex: board.getHexagons()) {
        if (hex.getNumber() == diceResult) {
            matchingHexagons.push_back(hex);
        }
    }

    for (const auto &vertex: board.getVertexs()) {
        bool adjacentToMatchingHexagon = false;

        for (const auto &hex: matchingHexagons) {
            if (vertex.isAdjacentTo(hex)) {
                adjacentToMatchingHexagon = true;
                hexCard = hex.getType();
                break;
            }
        }

        if (adjacentToMatchingHexagon) {
            Structure structure = vertex.getStructure();
            Player *owner = vertex.getOwner();
            if (owner != nullptr) {
                if (structure == Structure::Settlement) {
                    takeCard(*owner, hexCard);
                } else if (structure == Structure::City) {
                    takeCard(*owner, hexCard);
                    takeCard(*owner, hexCard);
                }
            }
        }
    }
}

bool Catan::buyDevCard(const Player &player) {
    if (!playerHasCards(player, CardType::Ore, 1) ||
        !playerHasCards(player, CardType::Grain, 1) ||
        !playerHasCards(player, CardType::Wool, 1)) {
        std::cout
                << "You do not have the required resources (1 Ore, 1 Grain, and 1 Wool) to buy a development card."
                << std::endl;
        return false;
    }

    std::vector<unsigned int> devCardTypeCounter(5, 0);
    for (unsigned int i = 0; i < cards.size(); i++) {
        if (cardOwnership.find(i) == cardOwnership.end()) {
            switch (cards[i]->getType()) {
                case CardType::Knight:
                    devCardTypeCounter[0]++;
                    break;
                case CardType::VictoryPoint:
                    devCardTypeCounter[1]++;
                    break;
                case CardType::RoadBuilding:
                    devCardTypeCounter[2]++;
                    break;
                case CardType::YearOfPlenty:
                    devCardTypeCounter[3]++;
                    break;
                case CardType::Monopoly:
                    devCardTypeCounter[4]++;
                    break;
                default:
                    break;
            }
        }
    }

    unsigned int sumOfDevCards = static_cast<unsigned int>(std::accumulate(devCardTypeCounter.begin(),
                                                                            devCardTypeCounter.end(), 0));
    if (sumOfDevCards == 0) {
        std::cout << "\nThere are no further development cards in the pack." << std::endl;
        return false;
    }

    returnCard2Deck(player, CardType::Ore, 1);
    returnCard2Deck(player, CardType::Grain, 1);
    returnCard2Deck(player, CardType::Wool, 1);

    int randNum = rand() % static_cast<int>(sumOfDevCards) + 1;
    unsigned int index = 0;
    unsigned int cumulativeSum = 0;
    for (unsigned int i = 0; i < devCardTypeCounter.size(); ++i) {
        cumulativeSum += devCardTypeCounter[i];
        if (randNum <= cumulativeSum) {
            index = i;
            break;
        }
    }

    switch (index) {
        case 0:
            takeCard(player, CardType::Knight);
            updateLargestArmyCard();
            cout<< player.getName() << " have received a Knight card." << endl;
            break;
        case 1:
            takeCard(player, CardType::VictoryPoint);
            addPoints(player, 1);
            cout<< player.getName() << " have received a Victory Point card." << endl;
            break;
        case 2:
            takeCard(player, CardType::RoadBuilding);
            takeCard(player, CardType::Brick);
            takeCard(player, CardType::Brick);
            takeCard(player, CardType::Lumber);
            takeCard(player, CardType::Lumber);
            cout<< player.getName() << " have received a Road Building card." << endl;
            break;
        case 3:
            takeCard(player, CardType::YearOfPlenty);
            playYearOfPlentyCard();
            playYearOfPlentyCard();
            cout<< player.getName() << " have received a Year of Plenty card." << endl;
            break;
        case 4:
            takeCard(player, CardType::Monopoly);
            cout<< player.getName() << " have received a Monopoly card." << endl;
            playMonopolyCard();
            break;
        default:
            break;
    }
    nextPlayer();
    return true;
}

void Catan::updateLargestArmyCard() {
    Player *playerWithMostKnights = nullptr;
    const unsigned int minimumKnightsForLargestArmy = 3;
    unsigned int maxKnights = minimumKnightsForLargestArmy;

    Player *players[] = {&player1, &player2, &player3};
    for (Player *player: players) {
        if (player->getKnights() >= maxKnights) {
            maxKnights = player->getKnights();
            playerWithMostKnights = player;
        }
    }

    for (Player *player: players) {
        if (playerHasCards(*player, CardType::LargestArmy, 1)) {
            returnCard2Deck(*player, CardType::LargestArmy, 1);
            player->reducePoints(2);
        }
    }

    if (playerWithMostKnights != nullptr) {
        takeCard(*playerWithMostKnights, CardType::LargestArmy);
        playerWithMostKnights->addPoints(2);
    }
}

void Catan::playMonopolyCard() {
    while (true) {
        std::cout << std::endl;
        std::cout << turn.getName() << ", please choose a resource for your monopoly." << std::endl;
        std::cout << "1. Lumber" << std::endl;
        std::cout << "2. Brick" << std::endl;
        std::cout << "3. Wool" << std::endl;
        std::cout << "4. Grain" << std::endl;
        std::cout << "5. Ore" << std::endl;
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                takeMonopoly(turn, CardType::Lumber);
                break;
            case 2:
                takeMonopoly(turn, CardType::Brick);
                break;
            case 3:
                takeMonopoly(turn, CardType::Wool);
                break;
            case 4:
                takeMonopoly(turn, CardType::Grain);
                break;
            case 5:
                takeMonopoly(turn, CardType::Ore);
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
        if (choice <= 5) {
            break;
        }
    }
}

void Catan::takeMonopoly(const Player &player, CardType type) {
    for (auto &entry: cardOwnership) {
        unsigned int cardId = entry.first;
        auto card = cards[cardId];
        if (card->getType() == type) {
            entry.second = &player;
        }
    }
    returnCard2Deck(player, CardType::Monopoly, 1);
}

void Catan::playYearOfPlentyCard() {
    while (true) {
        std::cout << std::endl;
        std::cout << turn.getName() << ", please choose a resource for your Year of Plenty.\n" << std::endl;
        std::cout << "1. Lumber" << std::endl;
        std::cout << "2. Brick" << std::endl;
        std::cout << "3. Wool" << std::endl;
        std::cout << "4. Grain" << std::endl;
        std::cout << "5. Ore" << std::endl;
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                takeCard(turn, CardType::Lumber);
                break;
            case 2:
                takeCard(turn, CardType::Brick);
                break;
            case 3:
                takeCard(turn, CardType::Wool);
                break;
            case 4:
                takeCard(turn, CardType::Grain);
                break;
            case 5:
                takeCard(turn, CardType::Ore);
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
        if (choice <= 5) {
            break;
        }
    }
}

unsigned int Catan::countPlayerResourceCards(const Player &player) const {
    unsigned int totalCards = 0;
    for (const auto &entry: cardOwnership) {
        CardType cardType = cards.at(entry.first)->getType();
        if (entry.second->getName() == player.getName() && isResourceCard(cardType)) {
            totalCards++;
        }
    }
    return totalCards;
}

bool Catan::isResourceCard(CardType type) const {
    return (type == CardType::Lumber || type == CardType::Brick || type == CardType::Grain ||
            type == CardType::Wool || type == CardType::Ore);
}

void Catan::handleReturnCardsForSeven(Player &player) {
    unsigned int numOfResourceCards = countPlayerResourceCards(player);
    if (numOfResourceCards > 7) {
        unsigned int numOfCardsToReturn = numOfResourceCards / 2;
        for (unsigned int i = 0; i < numOfCardsToReturn; i++) {
            menuForDiceSeven(player);
        }
    }
}

void Catan::handleSeven() {
    std::vector<Player *> players = {&player1, &player2, &player3};

    for (Player *p: players) {
        handleReturnCardsForSeven(*p);
    }

    std::cout << "\nDice 7 handling has been completed.\n" << std::endl;
}

void Catan::menuForDiceSeven(const Player &player) {
    bool returnSuccess;
    while (true) {
        std::cout << std::endl;
        std::cout << player.getName() << ", please choose a resource to return to the bank.\n" << std::endl;
        std::cout << "1. Lumber" << std::endl;
        std::cout << "2. Brick" << std::endl;
        std::cout << "3. Wool" << std::endl;
        std::cout << "4. Grain" << std::endl;
        std::cout << "5. Ore" << std::endl;
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                returnSuccess = returnCard2Deck(player, CardType::Lumber, 1);
                break;
            case 2:
                returnSuccess = returnCard2Deck(player, CardType::Brick, 1);
                break;
            case 3:
                returnSuccess = returnCard2Deck(player, CardType::Wool, 1);
                break;
            case 4:
                returnSuccess = returnCard2Deck(player, CardType::Grain, 1);
                break;
            case 5:
                returnSuccess = returnCard2Deck(player, CardType::Ore, 1);
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
        if (choice <= 5 && returnSuccess) {
            break;
        }
    }
}

void Catan::buildMenu(){
    std::cout << std::endl << "Build Options: " << std::endl;
    std::cout << "1. Road" << std::endl;
    std::cout << "2. Settlement" << std::endl;
    std::cout << "3. City" << std::endl;
    int buildChoice;
    std::cin >> buildChoice;
    
    unsigned int index;
    switch (buildChoice) {
        case 1:
            std::cout << std::endl << "Enter edge index to place road: ";
            std::cin >> index;
            std::cout << std::endl;
            placeRoad(*checkTurn(), index); // Place a road
            break;
        case 2:
            std::cout << std::endl << "Enter vertex index to place settlement: ";
            std::cin >> index;
            std::cout << std::endl;
            placeSettlement(*checkTurn(), index); // Place a settlement
            break;
        case 3:
            std::cout << std::endl << "Enter vertex index to place city: ";
            std::cin >> index;
            std::cout << std::endl;
            placeCity(*checkTurn(), index); // Place a city
            break;
        default:
            std::cout << "Invalid build choice. Please try again." << std::endl;
    }
}

void Catan::showStatus() {
    std::cout << std::endl << "Status Options: " << std::endl;
    std::cout << "1. Cards of player 1" << std::endl;
    std::cout << "2. Cards of player 2" << std::endl;
    std::cout << "3. Cards of player 3" << std::endl;
    std::cout << "4. Show board" << std::endl;
    std::cout << "5. Show points" << std::endl;

    int statusChoice;
    std::cin >> statusChoice;

    switch (statusChoice) {
        case 1:
            showPlayerCards(player1); // Show cards of player 1
            break;
        case 2:
            showPlayerCards(player2); // Show cards of player 2
            break;
        case 3:
            showPlayerCards(player3); // Show cards of player 3
            break;
        case 4:
            displayBoard(); // Display the current board
            break;
        case 5:
            displayPoints(); // Display the points of all players
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
    }
}

void Catan::welcomeAndSetupPlayers() {
    std::cout << std::endl << "Welcome to Catan!" << std::endl;
    std::cout << std::endl << "Please enter the names of 3 players:" << std::endl;
    std::string name;

    std::cout << "Player 1: ";
    std::cin >> name;
    player1 = Player(name); // initilize a new player with the given name

    std::cout << "Player 2: ";
    std::cin >> name;
    player2 = Player(name); // initilize a new player with the given name

    std::cout << "Player 3: ";
    std::cin >> name;
    player3 = Player(name); // initilize a new player with the given name
    
    std::cout << std::endl;
}

void Catan::tradeCards(const Player &player) {
    std::vector<Player *> playerSelection = {&player1, &player2, &player3};
    CardType giveResource, getResource;
    unsigned int giveAmount, getAmount;
    unsigned int choice;

    std::cout << "Select the resource you want to give: (1: Lumber, 2: Brick, 3: Wool, 4: Grain, 5: Ore): ";
    unsigned int giveResourceChoice;
    std::cin >> giveResourceChoice;
    giveResource = static_cast<CardType>(giveResourceChoice - 1);

    std::cout << "Enter the amount you want to give: ";
    std::cin >> giveAmount;

    if (!playerHasCards(player, giveResource, giveAmount)) {
        std::cout << "You don't have enough of the selected resource to give.\n";
        return;
    }

    std::cout << "Select the resource you want to get (1: Lumber, 2: Brick, 3: Wool, 4: Grain, 5: Ore): ";
    int getResourceChoice;
    std::cin >> getResourceChoice;
    getResource = static_cast<CardType>(getResourceChoice - 1);

    std::cout << "Enter the amount you want to get: ";
    std::cin >> getAmount;

    std::cout << "Select a player to trade with or reject the trade:\n";
    for (size_t i = 0; i < playerSelection.size(); ++i) {
        std::cout << i + 1 << ". " << playerSelection[i]->getName() << "\n";
    }
    std::cout << playerSelection.size() + 1 << ". Reject trade\n";
    std::cin >> choice;
    std::cout << std::endl;

    if (choice > 0 && choice <= playerSelection.size()) {
        if (choice == playerSelection.size() + 1) {
            std::cout << "Trade rejected.\n";
            return;
        }

        Player &otherPlayer = *playerSelection[choice - 1];

        if (!playerHasCards(otherPlayer, getResource, getAmount)) {
            std::cout << otherPlayer.getName() << " doesn't have enough of the selected resource to give.\n";
            return;
        }

        returnCard2Deck(otherPlayer, getResource, getAmount);
        returnCard2Deck(player, giveResource, giveAmount);

        for (unsigned int i = 0; i < giveAmount; i++) {
            takeCard(otherPlayer, giveResource);
        }
        for (unsigned int i = 0; i < getAmount; i++) {
            takeCard(player, getResource);
        }
        std::cout << "Trade completed successfully!\n";
    } else {
        std::cout << "Trade rejected.\n";
    }
}

Board Catan::getBoard() {
            return board;
}

}
