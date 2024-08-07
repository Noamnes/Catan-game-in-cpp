
// noam sayada
// noamsayada1@gmail.com

#pragma once

#include <string>
#include <vector>
#include <memory>

namespace ariel {

// This class models a game player.
class Player {

private:
    std::string name;  // Player's name
    unsigned int points = 0;  // Current score of the player
    unsigned int numOfKnightCards = 0;  // Number of knight cards the player has

public:
    // Initializes a Player with a specified name.
    Player(const std::string& name);

    Player(){}

    // Retrieves the player's name.
    const std::string& getName() const;

    // Increases the player's score by a given amount.
    void addPoints(unsigned int points);

    // Returns the player's current score.
    unsigned int getPoints() const;

    // Decreases the player's score by a specified amount.
    void reducePoints(unsigned int points);

    // Increases the player's knight card count.
    void addKnights(unsigned int numOfKnightCards);

    // Returns the current number of knight cards the player has.
    unsigned int getKnights() const;

};

}
