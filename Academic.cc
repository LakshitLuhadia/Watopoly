#include <iostream>
#include <string>
#include "Academic.h"
#include "Player.h"
using namespace std;
using std::vector;

// Constructor for Academic
Academic::Academic(const std::string name, const int index, const bool isProperty, const int cost, const bool isAcademic, const bool isResidence, const bool isGym, const std::string block, const int improvementCost, const vector <int> tution) :
Property{name, index, isProperty, cost, isAcademic, isResidence, isGym}, block{block}, improvementCost{improvementCost}, tution{tution} {
    numImprovements = 0;            // No improvements initially
    isMonopoly = false;             // Not part of a monopoly initially
    isImprovable = true;            // Improvable initially
    isSellable = true;              // Sellable initially
}

// Destructor for Academic
Academic::~Academic() {}

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
    vector <int> tution = this->tution;
    return tution[level];
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

// Implement the add improvement method
void Academic::addimprove() {
    Player* owner = getOwner();
    if (isMonopoly) {
        if (isImprovable) {
            if (numImprovements > 0) {
                isSellable = true;  
            }
            if (numImprovements == 5) {
                isImprovable = false;
            } else {
                numImprovements++;
                owner->subtractMoney(improvementCost);
                Administration::addMoney(improvementCost);
            }
        }
    }
} // Academic::improve

// Implement the sell improvement method
void Academic::sellimprove() {
    Player* owner = getOwner();
    if (isMonopoly) {
        if (isImprovable) {
            if (numImprovements < 5) {
                isImprovable = true;
            }
            if (numImprovements == 0) {
                isImprovable = true;
            } else {
                numImprovements--;
                owner->addMoney(improvementCost / 2);
                Administration::subtractMoney(improvementCost / 2);
            }
        }
    }
} // Academic::sellimprove

// Performs the action of the property
void Academic::performAction(Player* player) const {
    Player* owner = getOwner();
    if (owner != nullptr) {
        if (owner != player) {
            int tuition = getTuition(numImprovements);
            player->subtractMoney(tuition);
            owner->addMoney(tuition);
        }
    }
} // Academic::performAction