
// noam sayada
// noamsayada1@gmail.com

#pragma once

#include "Card.hpp"
#include "CardType.hpp"

namespace ariel {

// A class for a special card in the game.
class SpecialCard : public Card {
private:
    CardType type;  // Type of the special card

public:
    // Create a SpecialCard with a given type.
    SpecialCard(CardType type);

    // Get the type of this special card.
    CardType getType() const override;
};

// A class for the Largest Army card, a type of special card.
class LargestArmyCard : public SpecialCard {
public:
    // Create a LargestArmyCard.
    LargestArmyCard();
};

}
