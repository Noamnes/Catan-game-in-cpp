// noam sayada
// noamsayada1@gmail.com

#pragma once

#include "player.hpp"
#include "CardType.hpp"
#include <memory>

namespace ariel {

// Abstract base class for game cards.
class Card {
public:
    virtual ~Card() = default; // Destructor for derived class cleanup.

    // Returns the type of this card.
    // Must be implemented by all subclasses.
    virtual CardType getType() const = 0;
};

}
