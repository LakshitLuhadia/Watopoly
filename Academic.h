#ifndef ACADEMIC_H
#define ACADEMIC_H
#include <iostream>
#include <string>
#include "Property.h"
#include "Player.h"
#include "Administration.h"
using std::vector; 

// Academic class
class Academic: public Property {
    const std::string block;                  // Block of the property
    const int improvementCost;                // Cost of improvements
    const vector <int> tution{};              // Tuition fees for the property
    static int numImprovements;                      // Number of improvements on the property
    static bool isMonopoly;                          // Is the property part of a monopoly?
    static bool isImprovable;                        // Is the property improvable?
    static bool isSellable;                           // Is the property sellable?

    public:
        // Constructor for Academic
        Academic(const std::string name, const int index, const bool isProperty, const int cost, const bool isAcademic, const bool isResidence, const bool isGym, const std::string block, const int improvementCost, const vector <int> tution);

        // Destructor for Academic
        ~Academic();

        // Getters
        // Returns the block of the property
        std::string getBlock() const;
        // Returns the improvement cost of the property
        int getImprovementCost() const;
        // Returns the tuition fees of the property
        int getTuition(int level) const;
        // Returns the number of improvements on the property
        static int getNumImprovements();
        // Returns whether the property is part of a monopoly
        static bool getIsMonopoly();
        // Returns whether the property is improvable
        static bool getIsImprovable();
        // Returns whether the property is sellable
        static bool getIsSellable();

        // Setters
        // Sets the number of improvements on the property
        static void setNumImprovements(int numImprovements);
        // Sets whether the property is part of a monopoly
        static void setIsMonopoly(bool isMonopoly);
        // Sets whether the property is improvable
        static void setIsImprovable(bool isImprovable);
        // Sets whether the property is sellable
        static void setIsSellable(bool isSellable);

        // Implement the improvement method
        // Make Improvements
        void addimprove();
        // Sell Improvements
        void sellimprove();


        // Performs the action of the property
        void performAction(Player* player) const override;
};

#endif