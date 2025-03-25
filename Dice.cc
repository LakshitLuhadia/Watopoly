#include "Dice.h"
#include <stdlib.h>

// Dice Ctor
Dice::Dice() {
    dice1 = 0;
    dice2 = 0;
} // Dice::Dice

// Roll function for Dice
void Dice::roll() {
    dice1 = rand() % 6 + 1;
    dice2 = rand() % 6 + 1;
} // Dice::roll

// Returns sum of the 2 dices
int Dice::add() {
    return dice1 + dice2;
} // Dice::add

// Checks if both dice equal
bool Dice::isEqual() {
    return dice1 == dice2;
} // Dice::isEqual

