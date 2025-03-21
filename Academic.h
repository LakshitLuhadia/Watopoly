#ifndef ACADEMIC_H
#define ACADEMIC_H
#include <iostream>
#include <string>
#include "Property.h"
#include "Player.h"
using std::vector; 

// Academic class
class Academic: public Property {
    const int improvementCost;                // Cost of improvements
    const vector <int> tution{};              // Tuition fees for the property
    int numImprovements;                      // Number of improvements on the property
    bool isMonopoly;                          // Is the property part of a monopoly?
    bool isImprovable;                        // Is the property improvable?

    public:
        // Constructor for Academic
        Academic(const std::string name, const int index, const bool isProperty, const int cost, const bool isAcademic, const int improvementCost, const vector <int> tution);

        // Destructor for Academic
        ~Academic();

        // Getters
        // Returns the improvement cost of the property
        int getImprovementCost() const;
        // Returns the tuition fees of the property
        int getTuition(int level) const;
        // Returns the number of improvements on the property
        int getNumImprovements() const;
        // Returns whether the property is part of a monopoly
        bool getIsMonopoly() const;
        // Returns whether the property is improvable
        bool getIsImprovable() const;

        // Setters
        // Sets the number of improvements on the property
        void setNumImprovements(int numImprovements);
        // Sets whether the property is part of a monopoly
        void setIsMonopoly(bool isMonopoly);
        // Sets whether the property is improvable
        void setIsImprovable(bool isImprovable);

        // Performs the action of the property
        void performAction(Player* player) const override;
};

#endif