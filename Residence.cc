#include <iostream>
#include <string>
#include "Residence.h"
#include "Player.h"
using namespace std;

// Constructor for Residence
Residence::Residence(const std::string name, const int index, const bool isProperty, const int cost, const bool isAcademic, const bool isResidence, const bool isGym) :
Property{name, index, true, 200, false, true, false} 
{} // Residence::Residence

// Returns the rent of the residence
int Residence::getRent() const {
    return rent;
} // Residence::getRent

// Performs the action of the residence
void Residence::performAction(std::shared_ptr<Player>& player) const {
    if (getOwner()) {
        if (getOwner().get() != player.get()) {
            int rent = getRent();
            player->subtractMoney(rent);
            getOwner()->addMoney(rent);
        }
    } 
} // Residence::performAction