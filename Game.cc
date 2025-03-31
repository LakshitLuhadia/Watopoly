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
#include "Textdisplay.h"

Game::Game(int numPlayers): testingMode{false}, board{std::make_shared<Board>(numPlayers)}, numPlayers{numPlayers} {
    auto td = std::make_shared<TextDisplay>(); // Create a TextDisplay object
    attach(td); // Attach TextDisplay as an observer
}

void Game::notifyObservers() {
    // Prepare the data needed by observers
    std::vector<std::shared_ptr<Player>> players;
    for (int i = 0; i < numPlayers; ++i) {
        players.push_back(board->getPlayer(i));
    }
    // Notify all observers
    for (const auto& observer : observers) { 
        auto textDisplay = std::dynamic_pointer_cast<TextDisplay>(observer);
        if (textDisplay) {
            textDisplay->display(board, players); // Pass the board and players to TextDisplay
        }
    }
}

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
        std::cout << "You are in Tims Line. You have " << 3 - currentPlayer->getTurnsInTimsLine() << " turns left." << std::endl;
        std::cout << "You have " << currentPlayer->getNumRimCups() << " Tim Cups left." << std::endl;
        if (currentPlayer->getNumRimCups() > 0) {
            std::cout << "Do you want to use a Tim Cup to get out of Tims Line? (y/n): ";
            std::string response;
            std::cin >> response;
            if (response == "y" || response == "Y") {
                currentPlayer->setInTimsLine(false);
                currentPlayer->setTurnsInTimsLine(0);
                currentPlayer->setNumRimCups(currentPlayer->getNumRimCups() - 1);
                std::cout << "You are out of Tims Line." << std::endl;
                return;
            } else if (response == "n" || response == "N") {
                std::cout << "You chose not to use a Tim Cup." << std::endl;
                std::cout << "You can (roll/pay): ";
                std::string action;
                std::cin >> action;
                if (action == "roll") {
                    dice.roll(die1, die2); // Roll the dice
                    currentPlayer->setTurnsInTimsLine(currentPlayer->getTurnsInTimsLine() + 1);
                    if (currentPlayer->getTurnsInTimsLine() >= 3) {
                        std::cout << "You are out of possible rolls in Tims Line." << std::endl;
                        std::cout << "You have to pay $50 to get out of Tims Line." << std::endl;
                        int cost = 50; // Cost to get out of Tims Line
                        currentPlayer->subtractMoney(cost);
                        currentPlayer->setInTimsLine(false);
                        currentPlayer->setTurnsInTimsLine(0);
                        std::cout << "You paid $" << cost << " to get out of Tims Line." << std::endl;
                    } else {
                        std::cout << "You rolled a " << dice.getDice1() << " and a " << dice.getDice2() << "." << std::endl;
                        if (dice.isEqual()) {
                            currentPlayer->setNumDoubleRolls(currentPlayer->getNumDoubleRolls() + 1);
                        } else {
                            currentPlayer->setNumDoubleRolls(0);
                        }
                    }
                } else if (action == "pay") {
                    int cost = 50; // Cost to get out of Tims Line
                    currentPlayer->subtractMoney(cost);
                    currentPlayer->setInTimsLine(false);
                    currentPlayer->setTurnsInTimsLine(0);
                    std::cout << "You paid $" << cost << " to get out of Tims Line." << std::endl;
                } else {
                    std::cerr << "Invalid action. Please enter 'roll' or 'pay'." << std::endl;
                }
            }
            else {
                std::cerr << "Invalid response. Please enter 'y' or 'n'." << std::endl;
            }
        }
    }
    else {
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
                    auction(property);
                }
            } else {
                // Property is owned
                if (currentPlayer->getName() == property->getOwner()->getName()) {
                    std::cout << "You landed on " << square->getName() << ". It is owned by you." << std::endl;
                } else {
                    std::cout << "You landed on " << square->getName() << ". It is owned by " << property->getOwner()->getName() << ". You have to pay rent." << std::endl;
                    square->performAction(currentPlayer);
                }
            }
        } else {
            // Non-property square actions
            square->performAction(currentPlayer);
        }
    }
    notifyObservers();
}

void Game::next() {
    // Move to the next player
    board->nextPlayer();
    //notifyObservers();
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


void Game::bankrupt() {
    // Declare bankruptcy
    std::shared_ptr<Player> currentPlayer = board->getCurrentPlayer();

    bool bankrupt = currentPlayer->getIsBankrupt();

    if (bankrupt) {
        int numplayers = getNumPlayers();
        if (numplayers == 2) {
            std::cout << "Game Over! " << currentPlayer->getName() << " is bankrupt!" << std::endl;
            std::cout << "The other player wins!" << std::endl;
        } else {
            int index = currentPlayer->getPosition();
            std::shared_ptr<Square> square = board->getSquare(index);
            if (std::shared_ptr<Property> property = std::dynamic_pointer_cast<Property>(square)) {
                std::shared_ptr<Player> owner = property->getOwner();
                if (owner != currentPlayer) {
                    std::vector<std::shared_ptr<Property>> properties = currentPlayer->getProperties();
                    for (auto& property : properties) {
                        property->setOwner(owner);
                        if (std::shared_ptr<Academic> academicBuilding = std::dynamic_pointer_cast<Academic>(property)) {
                            while (academicBuilding->getNumImprovements() > 0) {
                                academicBuilding->sellimprove();
                            }
                        }
                        currentPlayer->removeProperty(properties.back());
                        properties.pop_back();
                    }
                }
            } else {
                
                std::vector<std::shared_ptr<Property>> properties = currentPlayer->getProperties();
                for (auto& property : properties) {
                    std::string propertyName = property->getName();
                    unmortgage(propertyName);
                    property->setOwner(nullptr);
                    currentPlayer->auction(property, currentPlayer);
                }
            }
        }
    }
}

void Game::assets() {
    // Display assets
    // This function will use getProperties function from Player class
    std::vector<std::shared_ptr<Property>> properties = board->getCurrentPlayer()->getProperties();
    std::cout << "You have the following properties: " << std::endl;
    for (auto property : properties) {
        std::cout << property->getName() << std::endl;
    }
    std::cout << "You have $" << board->getCurrentPlayer()->getMoney() << "." << std::endl;
    std::cout << "You have " << board->getCurrentPlayer()->getNumRimCups() << " Tim Cups." << std::endl;
    //notifyObservers();
}

void Game::all() {
    // Display asssets of all players
    for (int i = 0; i < numPlayers; i++) {
        std::cout << board->getPlayer(i)->getName() << " has: " << std::endl;
        std::vector<std::shared_ptr<Property>> properties = board->getPlayer(i)->getProperties();
        std::cout << "Properties: ";
        for (auto property : properties) {
            std::cout << property->getName() << " ";
        }
        std::cout << std::endl;
        std::cout << "Money: " << board->getPlayer(i)->getMoney() << std::endl;
        std::cout << "Tim Cups: " << board->getPlayer(i)->getNumRimCups() << std::endl;
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

void Game::auction(std::shared_ptr<Property> property) {
    auto currentPlayer = board->getCurrentPlayer();
    std::cout << "Starting auction for " << property->getName() << "." << std::endl;

    // Find the starting index of the current player
    int startIndex = 0;
    for (int i = 0; i < numPlayers; ++i) {
        if (board->getPlayer(i) == currentPlayer) {
            startIndex = i;
            break;
        }
    }

    // Get all non-bankrupt players in order starting from current player
    std::vector<std::shared_ptr<Player>> participants;
    for (int i = 0; i < numPlayers; ++i) {
        int idx = (startIndex + i) % numPlayers;
        auto player = board->getPlayer(idx);
        if (!player->getIsBankrupt()) {
            participants.push_back(player);
            std::cout << "Participant: " << player->getName() << std::endl;
        }
    }

    if (participants.empty()) {
        std::cout << "No participants. Property remains unowned." << std::endl;
        return;
    }

    int currentBid = 0; // Start bidding at $0
    std::shared_ptr<Player> highestBidder = nullptr;

    // Track players who have passed
    std::vector<bool> passed(participants.size(), false);
    int activeBidders = participants.size();

    size_t currentIndex = 0; // Index of the current bidder

    while (activeBidders > 1) {
        auto player = participants[currentIndex];
        if (passed[currentIndex]) { // Skip passed players
            currentIndex = (currentIndex + 1) % participants.size();
            continue;
        }

        int minBid = currentBid + 1; // Minimum allowed bid

        std::cout << player->getName() << "'s turn. Current bid: $" 
                  << currentBid << "\n"
                  << "Enter bid (minimum $" << minBid << ") or 'pass': ";

        std::string input;
        std::cin >> input;

        if (input == "pass") {
            passed[currentIndex] = true;
            activeBidders--;
            std::cout << player->getName() << " passes." << std::endl;

            // Move to next player
            currentIndex = (currentIndex + 1) % participants.size();
            continue;
        }

        // Validate numeric input
        bool validNumber = !input.empty() && 
            std::all_of(input.begin(), input.end(), ::isdigit);

        if (!validNumber) {
            std::cerr << "Invalid input! Numbers only." << std::endl;
            continue; // Retry same player
        }

        int bid = std::stoi(input);

        if (bid < minBid) {
            std::cerr << "Bid must be at least $" << minBid << "!" << std::endl;
            continue; // Retry same player
        }

        if (bid > player->getMoney()) {
            std::cerr << player->getName() << " can't afford this bid!" << std::endl;
            continue; // Retry same player
        }

        // Accept valid bid
        currentBid = bid;
        highestBidder = player;

        std::cout << "New highest bid: $" << bid 
                  << " by " << player->getName() << "." << std::endl;

        // Move to next player
        currentIndex = (currentIndex + 1) % participants.size();
    }

    if (highestBidder) {
        highestBidder->subtractMoney(currentBid);
        property->setOwner(highestBidder);
        highestBidder->addProperty(property);
        std::cout << highestBidder->getName() 
                  << " wins " << property->getName() 
                  << " for $" << currentBid << "." << std::endl;
    } else {
        std::cout << "Auction ended with no bids." 
                  << property->getName() 
                  << " remains unowned." 
                  << std::endl;
    }
}
