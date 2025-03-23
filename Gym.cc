#include <iostream>
#include <string>
#include "Gym.h"
#include "Player.h"
using namespace std;

// Constructor for Gym
Gym::Gym(const std::string name, const int index, const bool isProperty, const int cost, const bool isAcademic) :
Property{name, index, true, 150, false} {}

// Destructor for Gym
Gym::~Gym() {}

// Returns the usage fee of the gym
int Gym::getusageFee() const {
    return usageFee;
} // Gym::getusageFee

// Returns whether the property is part of a monopoly
bool Gym::getIsMonopoly() const {
    return isMonopoly;
} // Gym::getIsMonopoly

// Sets whether the property is part of a monopoly
void Gym::setIsMonopoly(bool isMonopoly) {
    this->isMonopoly = isMonopoly;
} // Gym::setIsMonopoly

// Performs the action of the gym
void Gym::performAction(Player* player) const {
    // If the property is owned
    Player* owner = getOwner();
    if (owner != nullptr) {
        if (owner != player) {
            int roll = Dice::add();
            bool isMonopoly = getIsMonopoly();
            if (isMonopoly) {
                roll *= 10;
            } else {
                roll *= 4;
            }
            player->subtractMoney(roll);
            owner->addMoney(roll);
        }
    } 
} // Gym::performAction