// noam sayada
// noamsayada1@gmail.com

#pragma once

#include "Card.hpp"
#include "CardType.hpp"

namespace ariel {

// Represents a development card within the game.
class DevelopmentCard : public Card {

private:
    CardType type;  // Specifies the type of development card.

public:
    // Initializes a DevelopmentCard with a specified type.
    // @param type: The type assigned to this development card.
    DevelopmentCard(CardType type);

    // Retrieves the type of this development card.
    // @return CardType: The type of this card.
    CardType getType() const override;

};

// Represents a Knight card, a variant of development card.
class KnightCard : public DevelopmentCard {
public:
    // Initializes a KnightCard.
    KnightCard();
};

// Represents a Victory Point card, a variant of development card.
class VictoryPointCard : public DevelopmentCard {
public:
    // Initializes a VictoryPointCard.
    VictoryPointCard();
};

// Represents a Road Building card, a variant of development card.
class RoadBuildingCard : public DevelopmentCard {
public:
    // Initializes a RoadBuildingCard.
    RoadBuildingCard();
};

// Represents a Year of Plenty card, a variant of development card.
class YearOfPlentyCard : public DevelopmentCard {
public:
    // Initializes a YearOfPlentyCard.
    YearOfPlentyCard();
};

// Represents a Monopoly card, a variant of development card.
class MonopolyCard : public DevelopmentCard {
public:
    // Initializes a MonopolyCard.
    MonopolyCard();
};

}