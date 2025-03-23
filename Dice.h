#ifndef DICE_H
#define DICE_H

// Dice Class
class Dice {
    static int dice1; // Dice 1's roll (ranges from 1 - 6)
    static int dice2; // Dice 2's roll (ranges from 1 - 6)
    static bool testing; // Whether in testing mode or not

    public:
        // Ctor for Dice
        Dice(bool testing);

        // Rolls the dice (sets dice1 and dice2 to numbers from 1 - 6)
        static void roll(int d1 = -1, int d2 = -1);

        // Adds dice1 and dice2 values (ranges 1 - 12)
        static int add();

        // Returns true if dice1 and dice2 are equal else false
        static bool isEqual();
};

#endif