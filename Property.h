#ifndef PROPERTY_H
#define PROPERTY_H
#include <iostream>
#include <string>
#include "Player.h"
#include "Square.h"
#include <memory> 

// Property class (abstract)
class Property: public Square {
    const int cost;                           // Cost of the property
    static int mortgageValue;                 // Mortgage value of the property
    static std::shared_ptr<Player> owner;     // Owner of the property
    static bool isMortgaged;                  // Is the property mortgaged?
    const bool isAcademic;                    // Is the property an academic property?
    const bool isResidence;                   // Is the property a residence?
    const bool isGym;                         // Is the property a gym?

    public:
        // Constructor for Property
        Property(const std::string name, const int index, const bool isProperty, const int cost, const bool isAcademic, const bool isResidence, const bool isGym);

        // Getters
        // Returns the cost of the property
        int getCost() const;
        // Returns the mortgage value of the property
        static int getMortgageValue();
        // Returns the owner of the property
        static std::shared_ptr<Player>& getOwner();
        // Returns whether the property is mortgaged
        static bool getIsMortgaged();
        // Returns whether the property is an academic property
        bool getIsAcademic() const;
        // Returns whether the property is a residence
        bool getIsResidence() const;
        // Returns whether the property is a gym
        bool getIsGym() const;

        // Setters
        // Sets the owner of the property
        static void setOwner(std::shared_ptr<Player> newOwner);
        // Sets the mortgage value of the property
        static void setMortgageValue(int mortgageValue);
        // Sets whether the property is mortgaged
        static void setIsMortgaged(bool isMortgaged);

        // Performs the action of the property
        virtual void performAction(std::shared_ptr<Player>& player) const = 0; // Abstract method
}; 

#endif
