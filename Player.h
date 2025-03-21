#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <vector>
#include "Property.h"

// Player Class
class Player {
    const std::string name; // Player name
    int money;              // Total money player currently has
    int position;           // Position on board player is on
    bool inTimsLine;        // If player in Tims line
    bool isBankrupt;        // If player is bankrupt (negative money)
    int numDoubleRolls;     // Number of consecutive double rolls
    int numRimCups;         // Number of Rim Cups player owns
    vector <Property*> properties;

    public:
        // Ctor for Player
        Player(string name; int money);

        // Dtor for Player
        ~Player();

        // Get Players name
        std::string getName() const;

        // Get Players money
        int getMoney();

        // Get Players position
        int getPosition();

        // Get all the properties owned by Player
        vector <Property*> getProperties();

        // Move Player to distance
        void move(int distance);

        // Adds amount to Player's money
        void addMoney(int amount);

        // Subtracts amount from Player's money
        void subtractMoney(int amount);

        // Adds property to Player's list of properties
        void addProperty(Property* property);

        // Removes property from Player's list of properties
        void removeProperty(Property* property);
}

#endif