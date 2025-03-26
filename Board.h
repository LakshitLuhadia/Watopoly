#ifndef BOARD_H
#define BOARD_H

// This is still a work in progress
// This is just a skeleton of the Board class
// This class will be used to represent the board of the game

#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include "Property.h"
#include "Square.h"
#include "Player.h"

class Board { // Note to everyone, we will be using smart pointers. No raw pointers.
  private:
    std::shared_ptr<Property> getPropertyByName(const std::string& name) const; // Get a property by name
    std::unique_ptr<Player> getPlayerByName(const std::string& name) const; // Get a player by name
    int currentPlayerIndex = 0; // The current player
    int numPlayers; // The number of players
    std::vector<shared_ptr<Square>> squares; // Vector of Squares
    std::vector<Player*> players; // Vector of Players

  public:
    void nextPlayer(); // Move to the next player
    void addPlayer(std::string name); // Add a player
    void trade(std::string player, std::string give, std::string receive); // Trade properties between players
    std::unique_ptr<Player> getCurrentPlayer() const; // Get the current player
};

#endif