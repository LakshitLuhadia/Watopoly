#include <iostream>
#include <string>
#include "Gym.h"
#include "Player.h"
using namespace std;

// Static variables
int Gym::usageFee = 0;
bool Gym::isMonopoly = false;

// Constructor for Gym
Gym::Gym(const std::string name, const int index, const bool isProperty, const int cost, const bool isAcademic, const bool isResidence, const bool isGym) :
Property{name, index, true, 150, false, false, true} {
    usageFee = 0;
    isMonopoly = false;
}

// Returns the usage fee of the gym
int Gym::getusageFee() {
    return usageFee;
} // Gym::getusageFee

// Returns whether the property is part of a monopoly
bool Gym::getIsMonopoly() {
    return isMonopoly;
} // Gym::getIsMonopoly

// Sets whether the property is part of a monopoly
void Gym::setIsMonopoly(bool newIsMonopoly) {
    isMonopoly = newIsMonopoly;
} // Gym::setIsMonopoly

// Performs the action of the gym
void Gym::performAction(std::shared_ptr<Player>& player) const {
    if (getOwner()) {
        if (getOwner() != player) {
            int roll = Dice::add();
            bool isMonopoly = getIsMonopoly();
            if (isMonopoly) {
                usageFee = roll * 10;
            } else {
                usageFee = roll * 4;
            }
            player->subtractMoney(usageFee);
            getOwner()->addMoney(usageFee);
        }
    } 
} // Gym::performAction
