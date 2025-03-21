#ifndef PROPERTY_H
#define PROPERTY_H
#include <iostream>
#include <string>
#include "Player.h"
#include "Square.h"

// Property class (abstract)
class Property: public Square {
    const int cost;                           // Cost of the property
    int mortgageValue;                        // Mortgage value of the property
    Player* owner;                            // Owner of the property
    bool isMortgaged;                         // Is the property mortgaged?
    const bool isAcademic;                    // Is the property an academic property?

    public:
        // Constructor for Property
        Property(const std::string name, const int index, const bool isProperty, const int cost, const bool isAcademic);

        // Destructor for Property
        virtual ~Property();

        // Getters
        // Returns the cost of the property
        int getCost() const;
        // Returns the mortgage value of the property
        int getMortgageValue() const;
        // Returns the owner of the property
        Player* getOwner() const;
        // Returns whether the property is mortgaged
        bool getIsMortgaged() const;
        // Returns whether the property is an academic property
        bool getIsAcademic() const;

        // Setters
        // Sets the owner of the property
        void setOwner(Player* owner);
        // Sets the mortgage value of the property
        void setMortgageValue(int mortgageValue);
        // Sets whether the property is mortgaged
        void setIsMortgaged(bool isMortgaged);

        // Performs the action of the property
        virtual void performAction(Player* player) const override;
};

#endif