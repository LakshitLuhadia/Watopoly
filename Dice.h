#ifndef DICE_H
#define DICE_H

// Dice Class
class Dice {
    int dice1; // Dice 1's roll (ranges from 1 - 6)
    int dice2; // Dice 2's roll (ranges from 1 - 6)

    public:
        // Ctor for Dice
        Dice();

        // Rolls the dice (sets dice1 and dice2 to numbers from 1 - 6)
        void roll();

        // Adds dice1 and dice2 values (ranges 1 - 12)
        int add();

        // Returns true if dice1 and dice2 are equal else false
        bool isEqual();
}

#endif

