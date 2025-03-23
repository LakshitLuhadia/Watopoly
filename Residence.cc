#include <iostream>
#include <string>
#include "Residence.h"
#include "Player.h"
using namespace std;

// Constructor for Residence
Residence::Residence(const std::string name, const int index, const bool isProperty, const int cost, const bool isAcademic, const bool isResidence, const bool isGym) :
Property{name, index, true, 200, false, true, false} {}

// Destructor for Residence
Residence::~Residence() {}  

// Returns the rent of the residence
int Residence::getRent() const {
    return rent;
} // Residence::getRent

// Performs the action of the residence
void Residence::performAction(Player* player) const {
    // If the property is owned
    Player* owner = getOwner();
    if (owner != nullptr) {
        if (owner != player) {
            // Calculate the rent
            int rent = getRent();
            // Pay the rent
            player->subtractMoney(rent);
            owner->addMoney(rent);
        } 
    } 
}