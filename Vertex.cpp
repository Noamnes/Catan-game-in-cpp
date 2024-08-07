/** noam sayada
 *  noamsayada1@gmail.com
 */

#include "Vertex.hpp"
#include "Hexagon.hpp"
#include <iostream>

using namespace ariel;

Vertex::Vertex(unsigned int idx) : index(idx), structure(None), owner(nullptr) {}

unsigned int Vertex::getIndex() const {
    return index;
}

Structure Vertex::getStructure() const {
    return structure;
}

Player* Vertex::getOwner() const {
    return owner;
}

void Vertex::addAdjacentHexagon(unsigned int hexX, unsigned int hexY) {
    adjacentHexagons.emplace_back(hexX, hexY);
}

const std::vector<std::pair<unsigned int, unsigned int>>& Vertex::getAdjacentHexagons() const {
    return adjacentHexagons;
}

bool Vertex::isAdjacentTo(const Hexagon& hex) const {
    const auto& adjList = vertex2hexagons[this->index];

    for (const auto& adj : adjList) {
        if (adj.first == hex.getX() && adj.second == hex.getY()) {
            return true;
        }
    }
    return false;
}

const std::vector<std::vector<std::pair<unsigned int, unsigned int>>>& Vertex::getVertex2HexagonsMapping() {
    return vertex2hexagons;
}

bool Vertex::setStructure(Structure newStructure, Player& player) {
    if (newStructure == Settlement) {
        if (structure == None) {
            structure = Settlement;
            this->owner = &player;
            std::cout << "Settlement created!" << std::endl;
            return true;
        }
    } else if (newStructure == City) {
        if (structure == Settlement) {
            structure = City;
            std::cout << "City created!" << std::endl;
            return true;
        }
    }
    return false;
}
