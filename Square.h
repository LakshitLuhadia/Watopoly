#ifndef SQUARE_H
#define SQUARE_H
#include <string>
#include "Player.h"

// Square class (abstract)
class Square {
    const std::string name;       // Name of the square
    const int index;                   // Index of the square
    const bool isProperty;              // Is the square a property? 

    public:
        // Constructor for Square
        Square(std::string name, int index, bool isProperty);

        // Destructor for Square
        virtual ~Square();

        // Getters
        // Returns the name of the square
        std::string getName() const;
        // Returns the index of the square
        int getIndex() const;
        // Returns whether the square is a property
        bool getIsProperty() const;

        // Pure virtual function
        // Performs the action of the square
        virtual void performAction(Player* player) = 0;
};

#endif