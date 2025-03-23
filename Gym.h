#ifndef GYM_H
#define GYM_H
#include <iostream>
#include <string>
#include "Property.h"
#include "Player.h"
using std::vector; 

// Gym class
class Gym: public Property {
    int usageFee = 0;                    // Usage fee of the gym
    bool isMonopoly = false;             // Is the property part of a monopoly?

    public:
        // Constructor for Gym
        Gym(const std::string name, const int index, const bool isProperty, const int cost, const bool isAcademic);

        // Destructor for Gym
        ~Gym();

        // Getters
        // Returns the usage fee of the gym
        int getusageFee() const;
        // Returns whether the property is part of a monopoly
        bool getIsMonopoly() const;

        // Setters
        // Sets whether the property is part of a monopoly
        void setIsMonopoly(bool isMonopoly);

        // Performs the action of the gym
        void performAction(Player* player) const override;
};

#endif