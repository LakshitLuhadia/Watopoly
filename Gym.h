#ifndef GYM_H
#define GYM_H
#include <iostream>
#include <string>
#include "Property.h"
#include "Player.h"
#include "Dice.h"

// Gym class
class Gym: public Property {
    static int usageFee;                // Usage fee of the gym
    static bool isMonopoly;             // If the the property is part of a monopoly

    public:
        // Constructor for Gym
        Gym(const std::string name, const int index, const bool isProperty, const int cost, const bool isAcademic, const bool isResidence, const bool isGym);

        // Getters
        // Returns the usage fee of the gym
        static int getusageFee();
        // Returns whether the property is part of a monopoly
        static bool getIsMonopoly();

        // Setters
        // Sets whether the property is part of a monopoly
        static void setIsMonopoly(bool isMonopoly);

        // Performs the action of the gym
        void performAction(std::shared_ptr<Player>& player) const override;
};

#endif
