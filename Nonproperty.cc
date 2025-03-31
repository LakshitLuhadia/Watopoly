#include "Nonproperty.h"

// NonProperty class constructor
NonProperty::NonProperty(const std::string name, const int index, const bool isProperty) : 
Square{name, index, isProperty} {} // NonProperty::NonProperty

// performAction for NonProperty class
void NonProperty::performAction(std::shared_ptr<Player>& player) const {
    return; // No action for non-property squares
}

