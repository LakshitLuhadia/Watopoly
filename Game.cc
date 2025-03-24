#include <iostream>
#include <vector>
#include <string>
#include "Subject.h"
#include "Player.h"
#include "Property.h"
#include "Board.h"

Game::Game(): testingMode{false}, numPlayers{0} {} // Board is yet to be initialized

Game::~Game() {}

void Game::roll() {
    Dice::roll()
}

void Game::next() {
    // Move to the next player
    board->nextPlayer();
}

void Game::trade(std::string player, std::string give, std::string receive) {
    // Trade properties between players
    // This function will use addProperty and removeProperty functions from Player class
    // It will also use setOwner function from Property class
}

void Game::improve(std::string property, std::string action) {
    // Improve a property
    // This function will use setNumImprovements function from Property class
}

void Game::mortgage(std::string property) {
    // Mortgage a property
    // This function will use setMortgaged and the related functions from Property class
}
    
void Game::unmortgage(std::string property) {
    // Unmortgage a property
    // This function will use setMortgaged and the related functions from Property class
}

void Game::bankrupt() {
    // Declare bankruptcy
    // This function will use bankrupt function from Player class
}

void Game::assets() {
    // Display assets
    // This function will use getProperties function from Player class
}

void Game::all() {
    // Display asssets of all players
    // This function will use getProperties function from Player class
    // This function will also use getPlayer function from Board class
}

void Game::save(std::string filename) {
    // Save the game
    // This function will use save function from Board class
}

void Game::setNumPlayers(int numPlayers) {
    this->numPlayers = numPlayers;
}

void Game::setNumRollsInTimsLine(int numRollsInTimsLine) {
    // Set the number of rolls in Tims Line
    // This function will use setNumRollsInTimsLine function from Player class
}

void Game::setPlayerTimCups(int i, int TimCups) {
    // Set the number of Tim Cups
    // This function will use setTimCups function from Player class
}

void Game::setPlayerMoney(int i, int money) {
    // Set the money of the player
    // This function will use setMoney function from Player class
}

void Game::setPlayerPosition(int i, int position) {
    // Set the position of the player
    // This function will use setPosition function from Player class
}

void Game::addPlayer(std::string name) {
    // Add a player
    // This function will use addPlayer function from Board class
}   

void Game::setPlayerCharacter(int i, char character) {
    // Set the character of the player
    // This function will use setCharacter function from Player class
}

void Game::setupBoard() {
    // Set up the board
    // This function will use setupBoard function from Board class
}

void Game::setupPlayers() {
    // Set up the players
    // This function will use setupPlayers function from Board class
}

void Game::setBuildingOwner(std::string buildingName, std::string owner) {
    // Set the owner of a building
    // This function will use setOwner function from Property class
}

void Game::setBuildingImprovements(std::string buildingName, int numImprovements) {
    // Set the number of improvements of a building
    // This function will use setNumImprovements function from Property class
}

void Game::setTestingMode(bool testingMode) {
    this->testingMode = testingMode;
}

void Game::notifyObservers() {
    // Notify the observers
    // This function will use notify function from Subject class
}

