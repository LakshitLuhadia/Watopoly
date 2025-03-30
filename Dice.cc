#include "Dice.h"
#include <stdlib.h>

// Dice Ctor
Dice::Dice(bool testing) {
    dice1 = 0;
    dice2 = 0;
    testing = false;
}

// Roll function for Dice
void Dice::roll(int d1, int d2) {
    if (testing && d1 > -1 && d2 > -1) {
        dice1 = d1;
        dice2 = d2;
    }
    dice1 = rand() % 6 + 1;
    dice2 = rand() % 6 + 1;
}

// Returns sum of the 2 dices
int Dice::add() {
    return dice1 + dice2;
} // Dice::add

// Checks if both dice equal
bool Dice::isEqual() {
    return dice1 == dice2;
} // Dice::isEqual

