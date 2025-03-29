#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <fstream>
#include "Subject.h"
#include "Player.h"
#include "Property.h"
#include "Dice.h"
#include "Academic.h"
#include "Residence.h"
#include "Gym.h"
#include "Square.h"
#include "Nonproperty.h"
#include "Board.h"
#include "Game.h"

Game::Game(): testingMode{false}, numPlayers{0}, board{std::make_shared<Board>()} {} // Board is yet to be initialized

void Game::roll() {
    Dice::roll();
    notifyObservers();
}

void Game::next() {
    // Move to the next player
    board->nextPlayer();
    notifyObservers();
}

void Game::trade(std::string player, std::string give, std::string receive) {
    // Trade properties between players
    // This function will use addProperty and removeProperty functions from Player class
    // It will also use setOwner function from Property class
    bool giveIsInt = std::all_of(give.begin(), give.end(), ::isdigit);
    bool receiveIsInt = std::all_of(receive.begin(), receive.end(), ::isdigit);

    if (giveIsInt && receiveIsInt) {
        std::cout << "reject" << std::endl;
    } else {
        board->trade(player, give, receive);
    }
    notifyObservers();
}

void Game::improve(std::string property, std::string action) {
    
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
    board->getCurrentPlayer()->getProperties();
    notifyObservers();
}

void Game::all() {
    // Display asssets of all players
    // This function will use getProperties function from Player class
    // This function will also use getPlayer function from Board class
    for (int i = 0; i < numPlayers; i++) {
        std::cout << board->getPlayer(i)->getName() << " has: " << std::endl; 
        board->getPlayer(i)->getProperties();
    }
    notifyObservers();
}

void Game::save(std::string filename) {
    // Save the game
    std::ofstream savefile{filename};
    if (savefile.fail()) {
        std::cerr << "Cannot open the save file" << std::endl;
    } else {
        // Save the game state
        // Save the number of players first
        savefile << numPlayers << std::endl;
        for (int i = 0; i < numPlayers; i++) {
            std::shared_ptr<Player> p = board->getPlayer(i);
            // This is following the format: name character numRimCups money position
            savefile << p->getName() << " " << p->getCharacter() << " " << p->getNumRimCups() << " " 
                     << p->getMoney() << " " << p->getPosition() << " ";
            if (p->getPosition() == 10) {
                if (p->getInTimsLine()) { // Check if the player is in Tims Line
                    savefile << 1 << " " << p->getTurnsInTimsLine() << " " << std::endl;
                } else {
                    savefile << 0 << std::endl;
                }
            }
        }
        for (int i = 0; i < 40; i++) {
            // This is following the format: name owner numImprovements
            if (board->getSquares(i)->getIsProperty() == false) {
                // Do not save the non-property square
                continue;
            } else {
                std::shared_ptr<Property> property = std::dynamic_pointer_cast<Property>(board->getSquares(i));
                if (property) {
                    savefile << property->getName() << " ";
                    if (property->getOwner() == nullptr) {
                        savefile << "BANK" << " ";
                    } else {
                        savefile << property->getOwner() << " ";
                    }

                    if (property->getIsMortgaged()) {
                        savefile << -1 << std::endl; // -1 for mortgaged
                    } else if (property->getIsResidence() || property->getIsGym()) {
                        savefile << 0 << std::endl; // No improvements for Residence and Gym
                    } else {
                        std::shared_ptr<Academic> academicBuilding = std::dynamic_pointer_cast<Academic>(property); // Downcast to Academic
                        if (!academicBuilding->getIsMonopoly()) {
                            savefile << 0 << std::endl; // No improvements for non-monopoly
                        } else {
                            // Save the number of improvements for Academic buildings
                            savefile << academicBuilding->getNumImprovements() << std::endl;
                        }
                    }
                }
            }
        }
    }
}

void Game::setNumPlayers(int numPlayers) {
    this->numPlayers = numPlayers;
}

void Game::setNumRollsInTimsLine(int numRollsInTimsLine) {
    // Set the number of rolls in Tims Line
    // This function will use setNumRollsInTimsLine function from Player class
    board->getCurrentPlayer()->setTurnsInTimsLine(numRollsInTimsLine);
}

void Game::setPlayerTimCups(int i, int TimCups) {
    // Set the number of Tim Cups
    // This function will use setTimCups function from Player class
    board->getPlayer(i)->setNumRimCups(TimCups);
}

void Game::setPlayerMoney(int i, int money) {
    // Set the money of the player
    // This function will use setMoney function from Player class
    board->getPlayer(i)->setMoney(money);
}

void Game::setPlayerPosition(int i, int position) {
    // Set the position of the player
    // This function will use setPosition function from Player class
    board->getPlayer(i)->setPosition(position);
}

void Game::addPlayer(std::string name) {
    board->addPlayer(name);
} // Game::addPlayer

void Game::setPlayerCharacter(int i, char character) {
    // Set the character of the player
    // This function will use setCharacter function from Player class
    board->getPlayer(i)->setCharacter(character);
}

void Game::setupBoard() {
    // Set up the board
    // This function will use setupBoard function from Board class
}

void Game::setupPlayers() {
    // Set up the players
    // This function will use setupPlayers function from Board class
}

/*
 * This function iterates through the squares on the game board to find
 * the building with the specified name. If the building is a property,
 * it updates the owner of the property to the specified owner.
 */
void Game::setBuildingOwner(std::string buildingName, std::string owner) {
   // Board *board = this->board; This line is not needed
    for (int i = 0; i < 40; i++) {
        if (board->getSquares(i)->getName() == buildingName) {
            if (board->getSquares(i)->getIsProperty()) {
                std::shared_ptr<Property> property = std::dynamic_pointer_cast<Property>(board->getSquares(i)); // Downcast to Property
                for (int j = 0; j < numPlayers; j++) {
                    if (board->getPlayer(j)->getName() == owner) {
                        property->setOwner(board->getPlayer(j)); // Set the owner of the property
                        break;
                    }
                }
            }
        }
    }
} // Game::setBuildingOwner

void Game::setBuildingImprovements(std::string buildingName, int numImprovements) {
    // Set the number of improvements of a building
    // This function will use setNumImprovements function from Property class
    for (int i = 0; i < 40; i++) {
        if (board->getSquares(i)->getName() == buildingName) {
            if (board->getSquares(i)->getIsProperty()) {
                std::shared_ptr<Property> property = std::dynamic_pointer_cast<Property>(board->getSquares(i)); // Downcast to Property
                if (property) {
                    std::shared_ptr<Academic> academicBuilding = std::dynamic_pointer_cast<Academic>(property); // Downcast to Academic
                    if (academicBuilding) {
                        academicBuilding->setNumImprovements(numImprovements);
                    }
                }
            }
        }
    }
}

void Game::setTestingMode(bool testingMode) {
    this->testingMode = testingMode;
} // Game::setTestingMode
