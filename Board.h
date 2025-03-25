#ifndef BOARD_H
#define BOARD_H

// This is still a work in progress
// This is just a skeleton of the Board class
// This class will be used to represent the board of the game

#include <vector>
#include <memory>
#include "Square.h"
#include "Player.h"

class Board { // Note to everyone, we will be using smart pointers. No raw pointers.
    int currentPlayerIndex = 0; // The current player
    int numPlayers; // The number of players
    std::vector<Square*> squares; // Vector of Squares
    std::vector<Player*> players; // Vector of Players

  public:
    void nextPlayer(); // Move to the next player
    void addPlayer(std::string name); // Add a player
};

#endif