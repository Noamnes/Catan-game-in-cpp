/** noam sayada
 *  noamsayada1@gmail.com
 */

#include "player.hpp"

namespace ariel {

    Player::Player(const std::string& name) : name(name) {}

    const std::string& Player::getName() const {
        return name;
    }

    void Player::addPoints(unsigned int pts) {
        this->points = this->points + pts;
    }

    void Player::reducePoints(unsigned int pts) {
        this->points = this->points - pts;
    }

    unsigned int Player::getPoints() const {
        return points;
    }

    void Player::addKnights(unsigned int knightCards) {
        this->numOfKnightCards = this->numOfKnightCards + knightCards;
    }

    unsigned int Player::getKnights() const {
        return numOfKnightCards;
    }

}
