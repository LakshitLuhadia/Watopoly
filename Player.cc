#include "Player.h"
#include "Property.h"
#include <string>
#include <vector>
using namespace std;

// Ctor for Player
Player::Player(string name, int money)
    : name(name), money(money), position(0), inTimsLine(false), 
      turnsInTimsLine(0), isBankrupt(false), numDoubleRolls(0), 
      numRimCups(0), numResidences(0) {
}

