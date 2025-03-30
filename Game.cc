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

Game::Game(int numPlayers): testingMode{false}, board{std::make_shared<Board>(numPlayers)}, numPlayers{numPlayers} {}

void Game::roll(int die1, int die2) {
    Dice dice(testingMode);
    auto currentPlayer = board->getCurrentPlayer();
    if (currentPlayer->getNumDoubleRolls() >= 3) {
        std::cout << "You rolled doubles three times in a row. Moving to DC Tims Line." << std::endl;
        currentPlayer->setPosition(10); // Move to DC Tims Line
        currentPlayer->setInTimsLine(true);
        currentPlayer->setNumDoubleRolls(0);
        return;
    } 
    if (currentPlayer->getInTimsLine()) {
        std::cout << "You are in Tims Line. You have " << currentPlayer->getTurnsInTimsLine() << " turns left." << std::endl;
        currentPlayer->setTurnsInTimsLine(currentPlayer->getTurnsInTimsLine() + 1);
        if (currentPlayer->getTurnsInTimsLine() >= 3) {
            currentPlayer->setInTimsLine(false);
            currentPlayer->setTurnsInTimsLine(0);
            std::cout << "You are out of Tims Line." << std::endl;
        }
    }
    dice.roll(die1, die2); // Roll the dice
    // if (testingMode) {
    //     if (die1 < 0 || die2 < 0) {
    //         std::cerr << "Error: Invalid dice values in testing mode." << std::endl;
    //         return;
    //     }
    //     dice.roll(die1, die2); // Roll with specified values
    // } else {
    //     dice.roll(); // Roll randomly
    // }
    std::cout << "You rolled a " << dice.getDice1() << " and a " << dice.getDice2() << "." << std::endl;

    if (dice.isEqual()) {
        currentPlayer->setNumDoubleRolls(currentPlayer->getNumDoubleRolls() + 1);
    } else {
        currentPlayer->setNumDoubleRolls(0);
    }
    int move = dice.add();
    currentPlayer->move(move);
    int newPosition = currentPlayer->getPosition();
    std::shared_ptr<Square> square = board->getSquare(newPosition);
    std::cout << square->getName() << std::endl;
    if (square->getIsProperty()) {
        std::shared_ptr<Property> property = std::dynamic_pointer_cast<Property>(square);
        if (property->getOwner() == nullptr) {
            // Property is unowned
            int cost = property->getCost();
            std::cout << "You landed on " << square->getName() << ". It is unowned and it costs " << cost <<". Do you want to buy it? (y/n): ";
            std::string response;
            std::cin >> response;
            if (response == "y" || response == "Y") {
                currentPlayer->addProperty(property);
                currentPlayer->subtractMoney(cost);
                property->setOwner(currentPlayer);
                std::cout << square->getName() << " bought " << "by " << currentPlayer->getName() << "." << std::endl;
            } else if (response == "n" || response == "N") {
                std::cout << "Property not bought." << std::endl;
                std::cout << "Starting Auction" << std::endl;
                currentPlayer->auction(property, currentPlayer);
            }
        } else {
            // Property is owned
            std::cout << "You landed on " << square->getName() << ". It is owned by " << property->getOwner() << ". You have to pay rent." << std::endl;
            square->performAction(currentPlayer);
        }
    } else {
        // Non-property square actions
        square->performAction(currentPlayer);
    }
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

void Game::improve(const std::string& property, const std::string& action) {
    std::shared_ptr<Player> currentPlayer = board->getCurrentPlayer();

    // Find the property by name
    std::shared_ptr<Square> square = nullptr;
    for (int i = 0; i < 40; ++i) {
        if (board->getSquare(i)->getName() == property) {
            square = board->getSquare(i);
            break;
        }
    }

    if (!square) {
        std::cerr << "Error: Property not found." << std::endl;
        std::cin.clear();
        std::cin.ignore();
        return;
    }

    // Ensure the square is an academic building
    Academic* academicBuilding = dynamic_cast<Academic*>(square.get());
    if (!academicBuilding) {
        std::cerr << "Error: Only academic buildings can be improved." << std::endl;
        std::cin.clear();
        std::cin.ignore();
        return;
    }

    // Ensure the current player owns the property
    if (academicBuilding->getOwner() != currentPlayer) {
        std::cerr << "Error: You do not own this property." << std::endl;
        std::cin.clear();
        std::cin.ignore();
        return;
    }

    // Handle the action
    if (action == "buy") {
        if (!academicBuilding->getIsImprovable()) {
            std::cerr << "Error: Improvements cannot be bought for this property at this time." << std::endl;
            std::cin.clear();
            std::cin.ignore();
            return;
        }

        // Add improvement
        academicBuilding->addimprove();
        std::cout << "Improvement bought for " << property 
                  << ". Current improvements: " 
                  << academicBuilding->getNumImprovements() << std::endl;

    } else if (action == "sell") {
        if (!academicBuilding->getIsSellable()) {
            std::cerr << "Error: Improvements cannot be sold for this property at this time." << std::endl;
            std::cin.clear();
            std::cin.ignore();
            return;
        }

        // Sell improvement
        academicBuilding->sellimprove();
        std::cout << "Improvement sold for " << property 
                  << ". Current improvements: " 
                  << academicBuilding->getNumImprovements() << std::endl;

    } else {
        std::cerr << "Error: Invalid action. Use 'buy' or 'sell'." << std::endl;
        std::cin.clear();
        std::cin.ignore();
        return;
    }
}

void Game::mortgage(std::string property) {
    // Mortgage a property
    // This function will use setMortgaged and the related functions from Property class
    // Validate property exists
    std::shared_ptr<Square> square = nullptr;
    for (int i = 0; i < 40; ++i) {
        if (board->getSquare(i)->getName() == property) {
            square = board->getSquare(i);
            break;
        }
    }

    if (!square) {
        std::cerr << "Error: Property not found." << std::endl;
        return;
    }

    // Check ownership
    std::shared_ptr<Property> propertySquare = std::dynamic_pointer_cast<Property>(square);
    if (!propertySquare || propertySquare->getOwner() != board->getCurrentPlayer()) {
        std::cerr << "Error: You don't own this property." << std::endl;
        return;
    }

    // Check improvements
    if (std::shared_ptr<Academic> academicBuilding = std::dynamic_pointer_cast<Academic>(propertySquare)) {
        if (academicBuilding->getNumImprovements() > 0) {
            std::cerr << "Error: You cannot mortgage a property with improvements." << std::endl;
            return;
        }
    }
    

    // Check mortgage status
    if (propertySquare->getIsMortgaged()) {
        std::cerr << "Error: Property is already mortgaged." << std::endl;
        return;
    }

    // Execute mortgage
    std::shared_ptr<Player> currentPlayer = board->getCurrentPlayer();
    currentPlayer->addMoney(propertySquare->getMortgageValue());
    propertySquare->setIsMortgaged(true);

    std::cout << "Property " << property << " has been mortgaged." << std::endl;

}
    
void Game::unmortgage(std::string property) {
    // Unmortgage a property
    // This function will use setMortgaged and the related functions from Property class
    std::shared_ptr<Square> square = nullptr;
    for (int i = 0; i < 40; ++i) {
        if (board->getSquare(i)->getName() == property) {
            square = board->getSquare(i);
            break;
        }
    }

    if (!square) {
        std::cerr << "Error: Property not found." << std::endl;
        return;
    }

    // Check ownership
    std::shared_ptr<Property> propertySquare = std::dynamic_pointer_cast<Property>(square);
    if (!propertySquare || propertySquare->getOwner() != board->getCurrentPlayer()) {
        std::cerr << "Error: You don't own this property." << std::endl;
        return;
    }

    // Check mortgage status
    if (!propertySquare->getIsMortgaged()) {
        std::cerr << "Error: Property is not mortgaged." << std::endl;
        return;
    }

    // Calculate cost
    int cost = propertySquare->getCost() * 0.6; // 0.6% of the cost

    // Check if player has enough money
    std::shared_ptr<Player> currentPlayer = board->getCurrentPlayer();
    if (currentPlayer->getMoney() < cost) {
        std::cerr << "Error: You don't have enough money to unmortgage this property." << std::endl;
        return;
    }

    // Execute unmortgage
    currentPlayer->subtractMoney(cost);
    propertySquare->setIsMortgaged(false);
    
    std::cout << "Property " << property << " has been unmortgaged." << std::endl;
}

int Game::attemptToRaiseFunds(std::shared_ptr<Player> player, int debtAmount) {
    int raisedFunds = player->getMoney();
    auto properties = player->getProperties();

    for (auto property : properties) {
        if (property->getIsAcademic()) {
            std::shared_ptr<Academic> academic = std::dynamic_pointer_cast<Academic>(property);
            int numImprovements = academic->getNumImprovements();
            for (int i = 0; i < numImprovements; ++i) {
                if (raisedFunds >= debtAmount) {
                    break;
                }
                academic->sellimprove();
                raisedFunds += academic->getImprovementCost();
            }
        }
    }

    properties = player->getProperties(); // Get updated properties after selling improvements
    for (auto property : properties) {
        if (!property->getIsMortgaged()) {
            int mortgageValue = property->getMortgageValue();
            if (raisedFunds >= debtAmount) {
                break;
            }
            mortgage(property->getName());
            raisedFunds += mortgageValue;
        }
    }

    int totalFunds = player->getMoney();

    std::cout << "Total funds after liquidation: $" << totalFunds << std::endl;
    std::cout << "Debt amount: $" << debtAmount << std::endl;

    return totalFunds;
}

void Game::bankrupt() {
    // Declare bankruptcy
    // This function will use bankrupt function from Player class
    // This is not an important function   bool bankrupt = board->getCurrentPlayer()->getIsBankrupt();
}

void Game::assets() {
    // Display assets
    // This function will use getProperties function from Player class
    std::vector<std::shared_ptr<Property>> properties = board->getCurrentPlayer()->getProperties();
    std::cout << "You have the following properties: " << std::endl;
    for (auto property : properties) {
        std::cout << property->getName() << std::endl;
    }
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
            if (board->getSquare(i)->getIsProperty() == false) {
                // Do not save the non-property square
                continue;
            } else {
                std::shared_ptr<Property> property = std::dynamic_pointer_cast<Property>(board->getSquare(i));
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

void Game::addPlayer(std::string name, int money) {
    board->addPlayer(name, money);
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

/*
 * This function iterates through the squares on the game board to find
 * the building with the specified name. If the building is a property,
 * it updates the owner of the property to the specified owner.
 */
void Game::setBuildingOwner(std::string buildingName, std::string owner) {
    for (int i = 0; i < 40; i++) {
        if (board->getSquare(i)->getName() == buildingName) {
            if (board->getSquare(i)->getIsProperty()) {
                std::shared_ptr<Property> property = std::dynamic_pointer_cast<Property>(board->getSquare(i)); // Downcast to Property
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
        if (board->getSquare(i)->getName() == buildingName) {
            if (board->getSquare(i)->getIsProperty()) {
                std::shared_ptr<Property> property = std::dynamic_pointer_cast<Property>(board->getSquare(i)); // Downcast to Property
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

bool Game::getTestingMode() const {
    return testingMode;
} // Game::getTestingMode

int Game::getNumPlayers() const {
    return numPlayers;
} // Game::getNumPlayers

std::shared_ptr<Board> Game::getBoard() const {
    return board;
} // Game::getBoard
