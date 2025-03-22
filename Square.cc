#include <string>
#include "Square.h"
#include "Player.h"

// Constructor for Square
Square::Square(std::string name, int index, bool isProperty) : 
name{name}, index{index}, isProperty{isProperty} {}

// Destructor for Square
Square::~Square() {}

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
