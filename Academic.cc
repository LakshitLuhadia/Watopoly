#include <iostream>
#include <string>
#include "Academic.h"
#include "Player.h"
using namespace std;
using std::vector;

// Constructor for Academic
Academic::Academic(const std::string name, const int index, const bool isProperty, const int cost, const bool isAcademic, const int improvementCost, const vector <int> tution) :
Property{name, index, isProperty, cost, isAcademic}, improvementCost{improvementCost}, tution{tution} {
    numImprovements = 0;            // No improvements initially
    isMonopoly = false;             // Not part of a monopoly initially
    isImprovable = true;            // Improvable initially
}

// Destructor for Academic
Academic::~Academic() {}

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
int Academic::getNumImprovements() const {
    return numImprovements;
} // Academic::getNumImprovements

// Returns whether the property is part of a monopoly
bool Academic::getIsMonopoly() const {
    return isMonopoly;
} // Academic::getIsMonopoly

// Returns whether the property is improvable
bool Academic::getIsImprovable() const {
    return isImprovable;
} // Academic::getIsImprovable

// Sets the number of improvements on the property
void Academic::setNumImprovements(int numImprovements) {
    this->numImprovements = numImprovements;
} // Academic::setNumImprovements   

// Sets whether the property is part of a monopoly
void Academic::setIsMonopoly(bool isMonopoly) {
    this->isMonopoly = isMonopoly;
} // Academic::setIsMonopoly

// Sets whether the property is improvable
void Academic::setIsImprovable(bool isImprovable) {
    this->isImprovable = isImprovable;
} // Academic::setIsImprovable

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