#include "Player.h"
#include "Property.h"
#include "Academic.h"
#include "Residence.h"
#include "Gym.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Ctor for Player
Player::Player(string name, int money)
    : name(name), money(money), position(0), inTimsLine(false), 
      turnsInTimsLine(0), isBankrupt(false), numDoubleRolls(0), 
      numRimCups(0), numResidences(0) {
}
// Get Players name
string Player::getName() const {
    return name;
}
// Get Players character
char Player::getCharacter() const {
    return character;
}
// Set Players character
void Player::setCharacter(char character) {
    this->character = character;
}
// Get Players money
int Player::getMoney() const {
    return money;
}
// Set Players money
void Player::setMoney(int money) {
    this->money = money;
    if (this->money < 0) {
        isBankrupt = true;
    }
}
// Get Players position
int Player::getPosition() const {
    return position;
}
// Set Players position
void Player::setPosition(int position) {
    this->position = position;
}
// Get if Player inTimsLine
bool Player::getInTimsLine() const {
    return inTimsLine; 
}
// Set if Player inTimsLine
void Player::setInTimsLine(bool inTimsLine) {
    this->inTimsLine = inTimsLine;
}
// Get Player's turnsInTimsLine
int Player::getTurnsInTimsLine() const {
    return turnsInTimsLine;
}
// Set Player's turnsInTimsLine
void Player::setTurnsInTimsLine(int turnsInTimsLine) {
    this->turnsInTimsLine = turnsInTimsLine;
}
// Get if Player isBankrupt
bool Player::getIsBankrupt() const {
    return isBankrupt;
}
// Get Player's numDoubleRolls
int Player::getNumDoubleRolls() const {
    return numDoubleRolls;
}
// Set Player's numDoubleRolls
void Player::setNumDoubleRolls(int numDoubleRolls) {
    this->numDoubleRolls = numDoubleRolls;
}
// Get Player's numRimCups
int Player::getNumRimCups() const {
    return numRimCups;
}
// Set Player's numRimCups
void Player::setNumRimCups(int numRimCups) {
    this->numRimCups = numRimCups;
}
// Get Player's numResidences
int Player::getNumResidences() const {
    return numResidences;
}
// Set Player's numResidences
void Player::setNumResidences(int numResidences) {
    this->numResidences = numResidences;
}
// Get all the properties owned by Player
vector<shared_ptr<Property>> Player::getProperties() const {
    return properties;
}
// Move Player to distance
void Player::move(int distance) {
    position += distance;
}
// Adds amount to Player's money
void Player::addMoney(int amount) {
    money += amount;
}
// Subtracts amount from Player's money
void Player::subtractMoney(int amount) {
    money -= amount;
    if (money < 0) {
        isBankrupt = true;
    }
}
// Adds property to Player's list of properties
void Player::addProperty(shared_ptr<Property> property) {
    properties.push_back(property);
    if (property->getIsResidence()) {
        numResidences++;
    }
}
// Removes property from Player's list of properties and sets its owner to nullptr
void Player::removeProperty(shared_ptr<Property> property) {
    if (property->getIsAcademic()) {
        shared_ptr<Academic> academicProperty = dynamic_pointer_cast<Academic>(property);
        int improvements = academicProperty->getNumImprovements();
        for (int i = 0; i < improvements; ++i) {
            academicProperty->sellimprove();
        }
        if (academicProperty->getIsMonopoly()) {
            academicProperty->setIsMonopoly(false);
        }
    } else if (property->getIsGym()) {
        shared_ptr<Gym> gymProperty = dynamic_pointer_cast<Gym>(property);
        if (gymProperty->getIsMonopoly()) {
            gymProperty->setIsMonopoly(false);
        }
    } else if (property->getIsResidence()) {
        numResidences--;
    }
    auto it = std::find(properties.begin(), properties.end(), property);
    if (it != properties.end()) {
        properties.erase(it);
    }
    property->setOwner(nullptr);
}
// Gives Player's property to player
void Player::auction(shared_ptr<Property> property, shared_ptr<Player> player) {
    if (property->getIsAcademic()) {
        shared_ptr<Academic> academicProperty = dynamic_pointer_cast<Academic>(property);
        int improvements = academicProperty->getNumImprovements();
        for (int i = 0; i < improvements; ++i) {
            academicProperty->sellimprove();
        }
        if (academicProperty->getIsMonopoly()) {
            academicProperty->setIsMonopoly(false);
        }
    } else if (property->getIsGym()) {
        shared_ptr<Gym> gymProperty = dynamic_pointer_cast<Gym>(property);
        if (gymProperty->getIsMonopoly()) {
            gymProperty->setIsMonopoly(false);
        }
    } else if (property->getIsResidence()) {
        numResidences--;
    }
    auto it = std::find(properties.begin(), properties.end(), property);
    if (it != properties.end()) {
        properties.erase(it);
    }
    property->setOwner(player);
}

