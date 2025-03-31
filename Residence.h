#ifndef RESIDENCE_H
#define RESIDENCE_H
#include <iostream>
#include <string>
#include "Property.h"
#include "Player.h"

// Residence class
class Residence : public Property {
    int rent = 25;                   // Rent of the residence

    public: 
        // Constructor for Residence
        Residence(const std::string name, const int index, const bool isProperty, const int cost, const bool isAcademic, const bool isResidence, const bool isGym);

        // Getters
        // Returns the rent of the residence
        int getRent() const;
        
        // Setters
        // Sets the rent of the residence
        void setRent(int newRent);

        // Performs the action of the residence
        void performAction(std::shared_ptr<Player>& player) const override;
};

#endif
