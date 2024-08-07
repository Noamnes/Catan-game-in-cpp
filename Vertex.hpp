// noam sayada
// noamsayada1@gmail.com

#pragma once
#include "player.hpp"
#include "Hexagon.hpp"
#include <vector>
#include <utility>
#include <iostream>

namespace ariel {
    
    // Enum for the type of structure on each vertex
    enum Structure {
        None, Settlement, City
    };

    // Class for a vertex on the game board where structures can be built
    class Vertex {

    private:
        unsigned int index;  // Index of the vertex
        Structure structure;  // Structure type on the vertex
        Player* owner = nullptr;  // Owner of the structure
        std::vector<std::pair<unsigned int, unsigned int>> adjacentHexagons;  // Adjacent hexagons

    public:
        // Constructs a Vertex with a specific index
        Vertex(unsigned int index);

        // Returns the index of the vertex
        unsigned int getIndex() const;

        // Returns the structure on the vertex
        Structure getStructure() const;

        // Returns the owner of the structure on the vertex
        Player* getOwner() const;

        // Sets the structure on the vertex and assigns an owner
        bool setStructure(Structure structure, Player& owner);

        // Adds an adjacent hexagon to the vertex
        void addAdjacentHexagon(unsigned int hexagonX, unsigned int hexagonY);

        // Returns the adjacent hexagons of the vertex
        const std::vector<std::pair<unsigned int, unsigned int>>& getAdjacentHexagons() const;

        // Checks if the vertex is adjacent to a specific hexagon
        bool isAdjacentTo(const Hexagon& hex) const;

        // Returns the static list of vertex adjacencies
        static const std::vector<std::vector<std::pair<unsigned int, unsigned int>>>& getVertex2HexagonsMapping();
    };

    // Define vertex adjacencies
    static const std::vector<std::vector<std::pair<unsigned int, unsigned int>>> vertex2hexagons = {
        {{0, 0}}, {{0, 0}}, {{0, 0}, {0, 1}}, {{0, 1}}, {{0, 1}, {0, 2}}, 
        {{0, 2}}, {{0, 2}}, {{1, 0}}, {{0, 0}, {1, 0}}, {{0, 0}, {1, 0}, {1, 1}}, 
        {{0, 0}, {0, 1}, {1, 1}}, {{1, 2}, {0, 1}, {1, 1}}, {{0, 1}, {1, 2}, {0, 2}}, 
        {{1, 3}, {1, 2}, {0, 2}}, {{0, 2}, {1, 3}}, {{1, 3}}, {{2, 0}}, 
        {{1, 0}, {2, 0}}, {{1, 0}, {2, 0}, {2, 1}}, {{1, 0}, {1, 1}, {2, 1}}, 
        {{1, 1}, {2, 1}, {2, 2}}, {{1, 1}, {1, 2}, {2, 2}}, {{1, 2}, {2, 2}, {2, 3}}, 
        {{1, 2}, {1, 3}, {2, 3}}, {{1, 3}, {2, 3}, {2, 4}}, {{1, 3}, {2, 4}}, 
        {{2, 4}}, {{2, 0}}, {{2, 0}, {3, 0}}, {{2, 0}, {2, 1}, {3, 0}}, 
        {{2, 1}, {3, 0}, {3, 1}}, {{2, 1}, {2, 2}, {3, 1}}, {{2, 2}, {3, 1}, {3, 2}}, 
        {{2, 2}, {2, 3}, {3, 2}}, {{2, 3}, {3, 2}, {3, 3}}, {{2, 3}, {2, 4}, {3, 3}}, 
        {{2, 4}, {3, 3}}, {{2, 4}}, {{3, 0}}, {{3, 0}, {4, 0}}, 
        {{3, 0}, {3, 1}, {4, 0}}, {{3, 1}, {4, 0}, {4, 1}}, {{3, 1}, {3, 2}, {4, 1}}, 
        {{3, 2}, {4, 1}, {4, 2}}, {{3, 2}, {3, 3}, {4, 2}}, {{3, 3}, {4, 2}}, 
        {{3, 3}}, {{4, 0}}, {{4, 0}}, {{4, 0}, {4, 1}}, 
        {{4, 1}}, {{4, 1}, {4, 2}}, {{4, 2}}, {{4, 2}}
    };

} 
