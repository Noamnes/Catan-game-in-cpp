// noam sayada
// noamsayada1@gmail.com

#pragma once

#include <utility>
#include "player.hpp"

namespace ariel {

// Represents a road on the game board where players can build.
class Edge {

private:
    unsigned int index;  // Edge identifier
    unsigned int vertex1;  // First connected vertex
    unsigned int vertex2;  // Second connected vertex
    Player* owner;  // Pointer to the edge owner

public:
    // Initializes an Edge with a given index and the vertices it connects.
    Edge(unsigned int index, unsigned int vertex1, unsigned int vertex2);

    // Retrieves the edge's index.
    unsigned int getIndex() const;

    // Retrieves the vertices connected by the edge.
    std::pair<unsigned int, unsigned int> getVertices() const;

    // Retrieves the owner of the edge.
    Player* getOwner() const;

    // Assigns an owner to the edge.
    bool setOwner(Player* player);
};

}
