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
        void performAction(std::shared_ptr<Player>& player) const override;
};

#endif
