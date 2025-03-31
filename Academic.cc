#include <iostream>
#include <string>
#include "Academic.h"
#include "Player.h"
using namespace std;
using std::vector;

// Constructor for Academic
Academic::Academic(const std::string name, const int index, const bool isProperty, const int cost, const bool isAcademic, const bool isResidence, const bool isGym, const std::string block, const int improvementCost, const vector <int> tuition) :
Property{name, index, isProperty, cost, isAcademic, isResidence, isGym}, block{block}, improvementCost{improvementCost}, tuition{tuition} {
    numImprovements = 0;            // No improvements initially
    isMonopoly = false;             // Not part of a monopoly initially
    isImprovable = true;            // Improvable initially
    isSellable = false;             // Not Sellable initially
} // Academic::Academic

// Returns the block of the property
std::string Academic::getBlock() const {
    return block;
} // Academic::getBlock

// Returns the improvement cost of the property
int Academic::getImprovementCost() const {
    return improvementCost;
} // Academic::getImprovementCost

// Returns the tuition fees of the property
int Academic::getTuition(int level) const {
    return tuition[level];
} // Academic::getTuition

// Returns the number of improvements on the property
int Academic::getNumImprovements() {
    return numImprovements;
} // Academic::getNumImprovements

// Returns whether the property is part of a monopoly
bool Academic::getIsMonopoly() {
    return isMonopoly;
} // Academic::getIsMonopoly

// Returns whether the property is improvable
bool Academic::getIsImprovable() {
    return isImprovable;
} // Academic::getIsImprovable

// Returns whether the property is sellable
bool Academic::getIsSellable() {
    return isSellable;
} // Academic::getIsSellable

// Sets the number of improvements on the property
void Academic::setNumImprovements(int newNumImprovements) {
    numImprovements = newNumImprovements;
} // Academic::setNumImprovements   

// Sets whether the property is part of a monopoly
void Academic::setIsMonopoly(bool newIsMonopoly) {
    isMonopoly = newIsMonopoly;
} // Academic::setIsMonopoly

// Sets whether the property is improvable
void Academic::setIsImprovable(bool newIsImprovable) {
    isImprovable = newIsImprovable;
} // Academic::setIsImprovable

// Sets whether the property is sellable
void Academic::setIsSellable(bool newIsSellable) {
    isSellable = newIsSellable;
} // Academic::setIsSellable

// Implement the add improvement method
void Academic::addimprove() {
    if (getOwner() != nullptr) {
        if (isMonopoly) {
            if (isImprovable) {
                if (numImprovements > 0) {
                    setIsSellable(true);  
                }
                if (numImprovements == 5) {
                    setIsImprovable(false);
                } else {
                    numImprovements++;
                    getOwner()->subtractMoney(improvementCost);
                }
            }
        }
    }
} // Academic::improve

// Implement the sell improvement method
void Academic::sellimprove() {
    if (getOwner() != nullptr) {
        if (isMonopoly) {
            if (isImprovable) {
                if (numImprovements < 5) {
                    setIsImprovable(true);
                }
                if (numImprovements == 0) {
                    setIsSellable(false);
                } else {
                    numImprovements--;
                    getOwner()->addMoney(improvementCost / 2);
                }
            }
        }
    }
} // Academic::sellimprove

// Performs the action of the property
void Academic::performAction(std::shared_ptr<Player>& player) const {
    if (getOwner() != nullptr) {
        if (getOwner() != player) {
            if (isMonopoly) {
                if (numImprovements == 0) {
                    int tuition = getTuition(numImprovements) * 2;
                    player->subtractMoney(tuition);
                    getOwner()->addMoney(tuition);
                } else {
                    int tuition = getTuition(numImprovements);
                    player->subtractMoney(tuition);
                    getOwner()->addMoney(tuition);
                }
            } else {
                int tuition = getTuition(numImprovements);
                player->subtractMoney(tuition);
                getOwner()->addMoney(tuition);
            }
        }
    } 
} // Academic::performAction
