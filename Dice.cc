#include "Dice.h"
#include <stdlib.h>

// Dice Ctor
Dice::Dice(bool testing) {
    dice1 = 0;
    dice2 = 0;
    testing = testing;
}

// Roll function for Dice
void Dice::roll(int d1 = -1, int d2 = -1) {
    if (testing && d1 > -1 && d2 > -1) {
        dice1 = d1;
        dice2 = d2;
    } else {
        dice1 = rand() % 6 + 1;
        dice2 = rand() % 6 + 1;
    }
}

// Returns sum of the 2 dices
int Dice::add() {
    return dice1 + dice2;
}

// Checks if both dice equal
bool Dice::isEqual() {
    return dice1 == dice2;
}

