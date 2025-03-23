#include "Player.h"
#include "Property.h"
#include <string>
#include <vector>

// Ctor for Player
Player::Player(string name, int money) : name(name), money(money) {
    position = 0;
    inTimsLine = false;
    isBankrupt = false;
    numDoubleRolls = 0;
    numRimCups = 0;
    properties = nullptr;
}

// Dtor for Player
~Player::Player() {
    
}
