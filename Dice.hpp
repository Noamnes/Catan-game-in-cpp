// noam sayada
// noamsayada1@gmail.com

#pragma once

#include <random>

namespace ariel {

// This class represents a dice used in the game.
class Dice {

private:
    std::mt19937 generator;  // Random number generator based on Mersenne Twister
    std::uniform_int_distribution<unsigned int> distribution;  // Uniform distribution for values 1 through 6

public:
    // Constructor that sets up the random number generator and distribution.
    Dice();

    // Rolls the dice and gives back a random number from 1 to 6.
    unsigned int roll();

};

}
