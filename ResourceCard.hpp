// noam sayada
// noamsayada1@gmail.com

#pragma once

#include "Card.hpp"
#include "CardType.hpp"

namespace ariel {

// This class represents a resource card in the game.
class ResourceCard : public Card {

private:
    CardType type;  // Type of the resource card

public:
    // Creates a ResourceCard with a given type.
    //
    // @param type The resource card type.
    ResourceCard(CardType type);

    // Returns the resource card type.
    //
    // @return CardType The resource card type.
    CardType getType() const override;

};

}
