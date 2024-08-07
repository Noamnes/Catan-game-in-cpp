#include "catan.hpp"

int main() {
    ariel::Catan catanGame;
    // catanGame.setRoadsandSettlements_auto(); // uncomment this line to run the tests of the game
    catanGame.setRoadsandSettlements(); // TODO: uncomment this line to run the game properly, without tests.
    catanGame.runGame(); // run the game
    return 0;
}
