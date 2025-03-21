#include "Dice.h"
#include <stdlib.h>

// Dice Ctor
Dice::Dice() : dice1(0), dice2(0) {}

// Roll function for Dice
void Dice::roll() {
    dice1 = rand() % 6 + 1;
    dice2 = rand() % 6 + 1;
}

// Returns sum of the 2 dices
int Dice::add() {
    return dice1 + dice2;
}

// Checks if both dice equal
bool Dice::isEqual() {
    return dice1 == dice2;
}

