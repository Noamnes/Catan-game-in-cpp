// noam sayada
// noamsayada1@gmail.com

#pragma once
#include "CardType.hpp"

namespace ariel {

    // This class represents a hexagon tile in the game that generates a specific resource.
    class Hexagon {

    private:
        CardType type;  // Specifies the type of resource produced by the hexagon
        unsigned int number;  // Represents the number for dice rolls associated with the hexagon
        unsigned int x;  // X-coordinate of the hexagon
        unsigned int y;  // Y-coordinate of the hexagon

    public:
        // Constructs a Hexagon with a given type, number, and coordinates.
        Hexagon(CardType type, unsigned int number, unsigned int x, unsigned int y);

        // Retrieves the type of resource the hexagon produces.
        CardType getType() const;

        // Retrieves the number for dice rolls associated with the hexagon.
        unsigned int getNumber() const;

        // Retrieves the x-coordinate of the hexagon.
        unsigned int getX() const;

        // Retrieves the y-coordinate of the hexagon.
        unsigned int getY() const;
        
    };
}
