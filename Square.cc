#include <string>
#include "Square.h"

// Constructor for Square
Square::Square(const std::string name, const int index, const bool isProperty) : 
name{name}, index{index}, isProperty{isProperty} {}

// Returns the name of the square
std::string Square::getName() const {
    return name;
} // Square::getName

// Returns the index of the square
int Square::getIndex() const {
    return index;
} // Square::getIndex

// Returns whether the square is a property
bool Square::getIsProperty() const {
    return isProperty;
} // Square::getIsProperty
