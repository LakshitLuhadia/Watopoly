#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include <memory>
#include "Property.h"

class Property; // Forward declaration of Property class

// Player Class
class Player {
    const std::string name; // Player name
    char character;         // Player's character
    int money;              // Total money player currently has
    int position;           // Position on board player is on
    bool inTimsLine;        // If player in Tims line
    int turnsInTimsLine;     // Number of rounds player has been in tims line
    bool isBankrupt;        // If player is bankrupt (negative money)
    int numDoubleRolls;     // Number of consecutive double rolls
    int numRimCups;         // Number of Rim Cups player owns
    int numResidences;       // Number of Residences player owns
    std::vector<std::shared_ptr<Property>> properties; // Vector of Player's properties

    public:
        // Ctor for Player
        Player(std::string name, int money);
        // Get Players name
        std::string getName() const;
        // Get Players character
        char getCharacter() const;
        // Set Players character
        void setCharacter(char character);
        // Get Players money
        int getMoney() const;
        // Set Players money
        void setMoney(int money);
        // Get Players position
        int getPosition() const;
        // Set Players position
        void setPosition(int position);
        // Get if Player inTimsLine
        bool getInTimsLine() const;
        // Set if Player inTimsLine
        void setInTimsLine(bool inTimsLine);
        // Get Player's turnsInTimsLine
        int getTurnsInTimsLine() const;
        // Set Player's turnsInTimsLine
        void setTurnsInTimsLine(int turnsInTimsLine);
        // Get if Player isBankrupt
        bool getIsBankrupt() const;
        // Set if Player isBankrupt
        void setIsBankrupt(bool isBankrupt);
        // Get Player's numDoubleRolls
        int getNumDoubleRolls() const;
        // Set Player's numDoubleRolls
        void setNumDoubleRolls(int numDoubleRolls);
        // Get Player's numRimCups
        int getNumRimCups() const;
        // Set Player's numRimCups
        void setNumRimCups(int numRimCups);
        // Get Player's numResidences
        int getNumResidences() const;
        // Set Player's numResidences
        void setNumResidences(int numResidences);
        // Get all the properties owned by Player
        std::vector<std::shared_ptr<Property>> getProperties() const;
        // Move Player to distance
        void move(int distance);
        // Adds amount to Player's money
        void addMoney(int amount);
        // Subtracts amount from Player's money
        void subtractMoney(int amount);
        // Adds property to Player's list of properties
        void addProperty(std::shared_ptr<Property> property);
        // Removes property from Player's list of properties
        void removeProperty(std::shared_ptr<Property> property);
        // Gives Player's property to player
        void auction(std::shared_ptr<Property> property, std::shared_ptr<Player> player);
};

#endif

