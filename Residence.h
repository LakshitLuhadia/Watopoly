#ifndef RESIDENCE_H
#define RESIDENCE_H
#include <iostream>
#include <string>
#include "Property.h"
#include "Player.h"

// Residence class
class Residence : public Property {
    const int rent = 25;                   // Rent of the residence

    public: 
        // Constructor for Residence
        Residence(const std::string name, const int index, const bool isProperty, const int cost, const bool isAcademic);

        // Destructor for Residence
        ~Residence();

        // Getters
        // Returns the rent of the residence
        int getRent() const;

        // Performs the action of the residence
        void performAction(Player* player) const override;
};

#endif