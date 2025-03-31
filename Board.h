#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include "Property.h"
#include "Square.h"
#include "Player.h"
#include "Academic.h"
#include "Residence.h"
#include "Gym.h"
#include "Square.h"
#include "Nonproperty.h"
#include "FeesSquare.h"
#include "OSAPSquare.h"
#include "ChanceSquare.h"
#include "GoToTimsSquare.h"

class Board { // Note to everyone, we will be using smart pointers. No raw pointers.
  private:    
    // Data fields
    int currentPlayerIndex = 0; // The current player
    int numPlayers = 0; // The number of players

    // Data Storing
    std::vector<std::shared_ptr<Square>> squares; // Vector of Squares
    std::vector<std::shared_ptr<Player>> players; // Vector of Players

    // Private functions
    std::shared_ptr<Property> getPropertyByName(const std::string& name) const; // Get a property by name
    std::shared_ptr<Player> getPlayerByName(const std::string& name) const; // Get a player by name

  public:
    // Constructor
    Board(int numPlayers);
    void nextPlayer(); // Move to the next player
    void addPlayer(std::string name, int money); // Add a player
    void removePlayer(std::string name); // Remove a player
    void trade(std::string player, std::string give, std::string receive); // Trade properties between players
    std::shared_ptr<Player> getCurrentPlayer() const; // Get the current player
    std::shared_ptr<Player> getPlayer(int i) const; // Get a player by index
    std::shared_ptr<Square> getSquare(int i) const; // Get a square by index
};

#endif