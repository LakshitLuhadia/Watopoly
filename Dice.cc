#include "Dice.h"
#include <stdlib.h>
#include <ctime>
#include <iostream>

int Dice::dice1 = 0;
int Dice::dice2 = 0;
bool Dice::testing = false;

// Dice Ctor
Dice::Dice(bool testing) {
    dice1 = 0;
    dice2 = 0;
    this->testing = testing; // Set testing mode (default false)
    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator
}

// Roll function for Dice
void Dice::roll(int d1, int d2) {
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
} // Dice::add

// Checks if both dice equal
bool Dice::isEqual() {
    return dice1 == dice2;
} // Dice::isEqual

int Dice::getDice1() const {
    return dice1;
} // Dice::getDice1

int Dice::getDice2() const {
    return dice2;
} // Dice::getDice2
