#ifndef BOARD_H
#define BOARD_H

// This is still a work in progress
// This is just a skeleton of the Board class
// This class will be used to represent the board of the game

#include <vector>
#include "Square.h"
#include "Player.h"

class Board {
    vector<Square*> squares; // Vector of Squares
    vector<Player*> players; // Vector of Players
};

#endif