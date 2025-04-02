#include <iostream>
#include <string>
#include "Property.h"
#include "Square.h"
#include "Player.h"
using namespace std;


// Constructor for Property
Property::Property(const std::string& name, const int index, const bool isProperty, const int cost, const bool isAcademic, const bool isResidence, const bool isGym) :
Square{name, index, isProperty}, cost{cost}, isAcademic{isAcademic}, isResidence{isResidence}, isGym{isGym} {
    mortgageValue = cost / 2;       // Mortgage value is half the cost
    owner = nullptr;                // No owner initially
    isMortgaged = false;            // Not mortgaged initially
} // Property::Property

// Returns the cost of the property
int Property::getCost() const {
    return cost;
} // Property::getCost

// Returns the mortgage value of the property
int Property::getMortgageValue() const{
    return mortgageValue;
} // Property::getMortgageValue

// Returns the owner of the property
std::shared_ptr<Player> Property::getOwner() const {
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

// Returns whether the property is a residence
bool Property::getIsResidence() const {
    return isResidence;
} // Property::getIsResidence

// Returns whether the property is a gym
bool Property::getIsGym() const {
    return isGym;
} // Property::getIsGym

// Sets the owner of the property
void Property::setOwner(std::shared_ptr<Player> newOwner) {
    owner = newOwner;
} // Property::setOwner

// Sets the mortgage value of the property 
void Property::setMortgageValue(int newMortgageValue) {
    mortgageValue = newMortgageValue;
} // Property::setMortgageValue

// Sets whether the property is mortgaged
void Property::setIsMortgaged(bool newIsMortgaged) {
    isMortgaged = newIsMortgaged;
} // Property::setIsMortgaged

void Property::performAction(std::shared_ptr<Player>& player) const {
    return; // No action for non-property squares
} // Property::performAction
