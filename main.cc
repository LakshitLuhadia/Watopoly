#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include "Board.h"
#include "Game.h"
#include "Player.h"
#include "Property.h"
#include "Square.h"
#include "Dice.h"
#include "Academic.h"

// Function to process in-game commands
// This function will be called in the main function
void processInGameCommands(Game& g) {
    auto b = g.getBoard(); // Get the board from the game
    bool hasRolled = false;
    bool hasTakenActionInTimsLine = false;

    while (true) {
        auto currentPlayer = b->getCurrentPlayer();
        std::cout << currentPlayer->getName() << "'s turn." << std::endl;

        // NEW: Handle first turn in Tims Line
        if (currentPlayer->getInTimsLine() && currentPlayer->getTurnsInTimsLine() == 0) {
            hasTakenActionInTimsLine = true; // Block prompt this turn
        }

        // Check if player is in Tims Line and needs to act
        if (currentPlayer->getInTimsLine() 
            && !hasTakenActionInTimsLine 
            && currentPlayer->getTurnsInTimsLine() > 0) {
            std::cout << "You are in Tims Line. Do you want to use a Tim Cup, Roll for doubles, or Pay $50? (tim/roll/pay): ";
            std::string timsCommand;
            std::cin >> timsCommand;

            if (timsCommand == "pay") {
                int cost = 50; // Cost to get out of Tims Line
                if (currentPlayer->getMoney() >= cost) {
                    currentPlayer->subtractMoney(cost);
                    currentPlayer->setInTimsLine(false);
                    currentPlayer->setTurnsInTimsLine(0);
                    std::cout << "You paid $50 to get out of Tims Line." << std::endl;
                    hasTakenActionInTimsLine = true; // Mark action as taken
                } else {
                    std::cout << "Insufficient funds to pay $50!" << std::endl;
                }
            } else if (timsCommand == "tim") {
                if (currentPlayer->getNumRimCups() > 0) {
                    currentPlayer->setInTimsLine(false);
                    currentPlayer->setTurnsInTimsLine(0);
                    currentPlayer->setNumRimCups(currentPlayer->getNumRimCups() - 1);
                    std::cout << "Used Tim Cup to exit Tims Line." << std::endl;
                    hasTakenActionInTimsLine = true; // Mark action as taken
                } else {
                    std::cout << "No Tim Cups available!" << std::endl;
                }
            } else if (timsCommand == "roll") {
                if (hasRolled) {
                    std::cerr << "Invalid Command. You have already rolled this turn." << std::endl;
                } else {
                    g.roll();
                    hasRolled = true;
                    hasTakenActionInTimsLine = true; // Mark action as taken
                }
            } else {
                std::cerr << "Invalid command. Please enter 'tim', 'roll', or 'pay'." << std::endl;
            }

            continue; // Skip other commands after taking action in Tims Line
        }

        // Handle other commands outside of Tims Line actions
        std::string command;
        std::cin >> command;

        if (command == "roll") {
            if (hasRolled) {
                std::cerr << "Invalid Command. You have already rolled this turn." << std::endl;
                continue;
            }

            if (g.getTestingMode()) {
                std::string input;
                std::getline(std::cin, input); // Read the entire line after "roll"

                // Check if input contains two integers
                std::istringstream iss(input);
                int die1, die2;

                if (iss >> die1 >> die2) {
                    if (die1 < 0 || die2 < 0) {
                        std::cerr << "Invalid dice roll. Please enter non-negative numbers." << std::endl;
                        continue;
                    }
                    g.roll(die1, die2); // Call roll with specified dice
                } else {
                    g.roll(-1, -1); // Call usual roll function
                }
            } else {
                g.roll(-1, -1); // Call usual roll function in non-testing mode
            }

            hasRolled = true; // Mark as rolled for this turn
        
        } else if (command == "next") {
            g.next();
            hasRolled = false;
            hasTakenActionInTimsLine = false; // Reset Tims Line action flag for next turn
        } else if (command == "trade") {
            std::string player, give, receive;
            std::cin >> player >> give >> receive;

            bool giveIsInt = std::all_of(give.begin(), give.end(), ::isdigit);
            bool receiveIsInt = std::all_of(receive.begin(), receive.end(), ::isdigit);

            if (!giveIsInt || !receiveIsInt) { 
                g.trade(player, give, receive);
            } else {
                std::cout << "reject" << std::endl;
            }
        
        } else if (command == "improve") {
            std::string property, action;
            std::cin >> property >> action;

            g.improve(property, action);

        } else if (command == "mortgage") {
            std::string property;
            std::cin >> property;
            g.mortgage(property);

        } else if (command == "unmortgage") {
            std::string property;
            std::cin >> property;
            g.unmortgage(property);

        } else if (command == "bankrupt") {
            g.bankrupt();

        } else if (command == "assets") {
            g.assets();

        } else if (command == "all") {
            g.all();

        } else if (command == "save") {
            std::string filename;
            std::cin >> filename;
            g.save(filename);
            
        } else {
            std::cerr << "Invalid command. Please enter a valid command." << std::endl;
        }

        // Check for game end condition
        if (g.getNumPlayers() == 1) {
            auto winner = b->getCurrentPlayer();
            std::cout << winner->getName() << " wins the game!" << std::endl;
            break;
        }
    }
}



// Function to load a game from a file
// This function will be called in the main function
Game processLoadedFile(const std::string& filename) {
    std::ifstream loadfile{filename};
    if (loadfile.fail()) {
        std::cerr << "Cannot open the loaded file" << std::endl;
    }
    Game g;
    std::shared_ptr<Board> board = g.getBoard();    
    int numPlayers;
    loadfile >> numPlayers;
    g.setNumPlayers(numPlayers);
    for (int i = 0; i < numPlayers; ++i) {
        std::string name;
        char character;
        int TimCups;
        int money;
        int position;
        loadfile >> name >> character >> TimCups >> money >> position;
        board->addPlayer(name, money);
        g.setPlayerCharacter(i, character);
        
        if (position == 30) {
            std::cerr << "Player cannot start on square 30 (Go to DC Tims Line)." << std::endl;
        }
        if (position == 10) {
            int inTimsLine;
            loadfile >> inTimsLine;
            if (inTimsLine == 1) {
                int numRollsInTimsLine;
                loadfile >> numRollsInTimsLine;
                if (numRollsInTimsLine < 0 || numRollsInTimsLine > 2) {
                    std::cerr << "Invalid number of rolls in Tims Line. Please enter a number between 0 and 2." << std::endl;
                } else {
                    g.setNumRollsInTimsLine(numRollsInTimsLine);
                }
            }
        }
        g.setPlayerTimCups(i, TimCups);
        g.setPlayerPosition(i, position);
    }
    std::string buildingName;
    while (loadfile >> buildingName) {
        std::string owner;
        int numImprovements;
        loadfile >> owner >> numImprovements;
        g.setBuildingOwner(buildingName, owner);
        g.setBuildingImprovements(buildingName, numImprovements);
    }
    return g;
}

// Helper function to check if a character is valid
bool isCharacter(char character, const std::vector<char>& characters) {
    return std::find(characters.begin(), characters.end(), character) != characters.end();
}

// Function to set up the game
// This function will be called in the main function
Game setupGame() {
    std::cout << "Welcome to the game of Watopoly!" << std::endl;
    while(true) {
        std::vector<char> characters = {'G', 'B', 'D', 'P', 'S', '$', 'L', 'T'};
        std::cout << "Please enter the number of players(2-6): " << std::endl;
        int numPlayers;
        if (!(std::cin >> numPlayers) || numPlayers < 2 || numPlayers > 6) { // if the number of players is not between 2 and 6, print an appropriate error message
            std::cerr << "Invalid number of players. Please enter an integer value between 2 and 6" << std::endl;
            std::cin.clear();
            while (std::cin.get() != '\n');
            continue;
        }
        Game g(numPlayers); // create a new game
        auto b = g.getBoard(); // get the board

        for (int i = 0; i < numPlayers; ++i) {
            std::string name;
            while (true) {
                std::cout << "Please enter the name of player " << i + 1 << ": " << std::endl;
                std::cin >> name;
                if (name.empty() || name == "BANK" || name == "bank") { // if the name is empty or "BANK", print an appropriate error message
                    std::cerr << "Invalid name. Please enter a valid name." << std::endl;
                    std::cin.clear();
                    while (std::cin.get() != '\n');
                    continue;
                } else {
                    break; // break the loop if the name is valid
                }
            }
            b->addPlayer(name, 1500); // add the player
            bool validCharacter = false;
            while (!validCharacter) { // check if the character is valid
                std::cout << "Please enter " << name << "'s character: " << std::endl;
                char character;
                std::cin >> character;
                if (isCharacter(character, characters)) {
                    g.setPlayerCharacter(i, character); // set the player's character
                    characters.erase(std::remove(characters.begin(), characters.end(), character), characters.end()); // remove the character from the list of characters
                    validCharacter = true;
                } else {
                    std::cerr << "Invalid character. Please enter a valid character." << std::endl;
                    std::cerr << "Valid characters are: G, B, D, P, S, $, L, T" << std::endl;
                    std::cin.clear();
                    while (std::cin.get() != '\n');
                    continue;
                }
            }
        }
        std::cout << "Setting things up and starting the game" << std::endl;

        return g;
    }
}

int main(int argc, char* argv[]) {
    bool testingMode = false; // a flag to check if testing mode is on
    bool loadMode = false; // a flag to check if load mode is on
    std::string filename = ""; // a string to store the filename

    for (int i = 1; i < argc; ++i) {
        std::string input_arg = argv[i];
        if (input_arg == "-testing") { // if the input argument is -testing, set the flag to true
            testingMode = true;
        } else if (input_arg == "-load") { // if the input argument is -load file, set the filename to the input filename
            if (i + 1 >= argc) { // if the filename is not provided, print an appropriate error message
                std::cerr << "No file to load. Starting a new game" << std::endl;
                loadMode = false;
            } else {
                filename = argv[i + 1];
                loadMode = true; // set the flag to true
            }
        } else if (loadMode != true) { // else, print an appropriate error message
            std::cerr << "Invalid command line argument" << std::endl;
        }
    }

    if (loadMode) {
        std::cout << "Using loaded game file" << std::endl;
        if (filename.empty() || filename == "") { // if the filename is empty, print an appropriate error message
            std::cerr << "No file to load" << std::endl;
        } else {
            std::ifstream loadFile{filename}; // open the file
            if (loadFile.fail()) { // if the file cannot be opened, print an appropriate error message
                std::cerr << "Cannot open the loaded file" << std::endl;
                return 1;
            } else {
                Game g = processLoadedFile(filename); // process the loaded file
                std::cout << "Loaded game file successfully" << std::endl;
                std::cout << "Starting the game" << std::endl;
                processInGameCommands(g); // process the in-game commands
            }
        }
    } else {
        Game g = setupGame(); // set up the game
        g.setTestingMode(testingMode); // set the testing mode
        processInGameCommands(g); // process the in-game commands
    }
}
