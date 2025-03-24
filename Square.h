#ifndef SQUARE_H
#define SQUARE_H
#include <string>
#include "Player.h"

// Square class (abstract)
class Square {
    const std::string name;            // Name of the square
    const int index;                   // Index of the square
    const bool isProperty;             // Is the square a property? 

    public:
        // Constructor for Square
        Square(const std::string name, const int index, const bool isProperty);

        // Getters
        // Returns the name of the square
        std::string getName() const;
        // Returns the index of the square
        int getIndex() const;
        // Returns whether the square is a property
        bool getIsProperty() const;

        // Constant pure virtual function
        // Performs the action of the square
        virtual void performAction(Player* player) const = 0;
};

#endif
