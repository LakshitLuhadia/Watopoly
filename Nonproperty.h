#ifndef NONPROPERTY_H
#define NONPROPERTY_H
#include <iostream>
#include <string>
#include "Square.h"

class NonProperty: public Square {
    public:
        // Constructor for NonProperty
        NonProperty(const std::string name, const int index, const bool isProperty);
        
        // Performs the action of the NonProperty
        virtual void performAction(Player* player) const = 0;
};

#endif