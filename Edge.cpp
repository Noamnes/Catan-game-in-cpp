#include "Edge.hpp"

namespace ariel {

    Edge::Edge(unsigned int idx, unsigned int v1, unsigned int v2)
            : index(idx), vertex1(v1), vertex2(v2), owner(nullptr) {}

    unsigned int Edge::getIndex() const {
        return index;
    }

    std::pair<unsigned int, unsigned int> Edge::getVertices() const {
        return {vertex1, vertex2};
    }

    Player* Edge::getOwner() const {
        return owner;
    }

    bool Edge::setOwner(Player* newOwner) {
        if (owner != nullptr) {
            return false; // Edge is already owned by another player
        }

        owner = newOwner;
        return true;
    }
}
