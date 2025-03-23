#include <iostream>
#include <string>
#include "Property.h"
using namespace std;

// Constructor for Property
Property::Property(const std::string name, const int index, const bool isProperty, const int cost, const bool isAcademic) :
Square{name, index, isProperty}, cost{cost}, isAcademic{isAcademic} {
    mortgageValue = cost / 2;       // Mortgage value is half the cost
    owner = nullptr;                // No owner initially
    isMortgaged = false;            // Not mortgaged initially
}

// Destructor for Property
Property::~Property() {}

// Returns the cost of the property
int Property::getCost() const {
    return cost;
}   

// Returns the mortgage value of the property
int Property::getMortgageValue() const {
    return mortgageValue;
} // Property::getMortgageValue

// Returns the owner of the property
Player* Property::getOwner() const {
    return owner;
} // Property::getOwner

// Returns whether the property is mortgaged
bool Property::getIsMortgaged() const {
    return isMortgaged;
} // Property::getIsMortgaged

// Returns whether the property is an academic property
bool Property::getIsAcademic() const {
    return isAcademic;
} // Property::getIsAcademic

// Sets the owner of the property
void Property::setOwner(Player* owner) {
    this->owner = owner;
} // Property::setOwner

// Sets the mortgage value of the property 
void Property::setMortgageValue(int mortgageValue) {
    this->mortgageValue = mortgageValue;
} // Property::setMortgageValue

// Sets whether the property is mortgaged
void Property::setIsMortgaged(bool isMortgaged) {
    this->isMortgaged = isMortgaged;
} // Property::setIsMortgaged

// Performs the action of the property
void Property::performAction(Player* player) const {
    Player* owner = getOwner();
    int cost = getCost();
    if (owner != nullptr) {
        if (owner != player) {
            player->subtractMoney(cost);
            owner->addMoney(cost);
        }
    }
} // Property::performAction
