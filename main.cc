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

void processInGameCommands(Game g) {
    auto b = g.getBoard(); // Get the board from the game
    while (true) {
        auto currentPlayer = b->getCurrentPlayer();
        std::cout << currentPlayer->getName() << "'s turn." << std::endl;

        std::string command;
        std::cin >> command;
        if (command == "roll") {
            if (g.getTestingMode()) {
                int die1;
                int die2;
                std::cin >> die1 >> die2;
                if (!std::cin.fail()) {
                    if (die1 < 0 || die2 < 0) {
                        std::cerr << "Invalid dice roll. Please enter a non-negative number." << std::endl;
                        std::cin.clear();
                        std::cin.ignore();
                    } else {
                        g.roll(die1, die2);
                    }
                } else {
                    g.roll();
                }
            } else {
                g.roll();
            }
        } else if (command == "next") {
            g.next();
        } else if (command == "trade") {
            std::string player;
            std::string give;
            std::string receive;
            std::cin >> player >> give >> receive;
            bool giveIsInt = std::all_of(give.begin(), give.end(), ::isdigit);
            bool receiveIsInt = std::all_of(receive.begin(), receive.end(), ::isdigit);
    
            if (giveIsInt && receiveIsInt) {
                std::cout << "reject" << std::endl;
            } else {
                std::cout << "Does "<< player << " want to trade " << give << " for " << receive << "? (y/n):" << std::endl;
                std::string response;
                std::cin >> response;
                if (response == "y" || response == "Y") {
                    std::cout << "accept" << std::endl;
                    g.trade(player, give, receive);
                } else if (response == "n" || response == "N") {
                    std::cout << "reject" << std::endl;
                } else {
                    std::cerr << "Invalid response. Please enter a valid response." << std::endl;
                    std::cin.clear();
                    std::cin.ignore();
                }
            }
        } else if (command == "improve") {
            std::string property;
            std::string action;
            std::cin >> property >> action;
            if (action != "buy" && action != "sell") {
                std::cerr << "Invalid action. Please enter 'buy' or 'sell'." << std::endl;
                std::cin.clear();
                std::cin.ignore();
            } else {
                g.improve(property, action);
            }
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
            std::cout << "Game saved to " << filename << std::endl;
            std::cout << "Exiting the game" << std::endl;
            break;
        } else {
            std::cerr << "Invalid command. Please enter a valid command." << std::endl;
            std::cin.clear();
            std::cin.ignore();
        }
        if (g.getNumPlayers() == 1) {
            auto winner = b->getCurrentPlayer();
            std::cout << "Congratulations! " << winner->getName() << " wins the game." << std::endl;
            break;
        }
    }
}

Game processLoadedFile(const std::string& filename) {
    std::ifstream loadfile{filename};
    if (loadfile.fail()) {
        std::cerr << "Cannot open the loaded file" << std::endl;
    }
    Game g;
    std::shared_ptr<Board> board;
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
        // g.setPlayerMoney(i, money);
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
Game setupGame() {

    std::vector<char> characters = {'G', 'B', 'D', 'P', 'S', '$', 'L', 'T'};
    std::cout << "Welcome to the game of Watopoly!" << std::endl;
    std::cout << "Please enter the number of players(2-6): " << std::endl;
    int numPlayers;
    if (!(std::cin >> numPlayers) || (!(numPlayers >= 2) && !(numPlayers <= 6))) { // if the number of players is not between 2 and 6, print an appropriate error message
        std::cerr << "Invalid number of players. Please enter an integer value between 2 and 6" << std::endl;
        std::cin.clear();
        std::cin.ignore();
    }
    Game g(numPlayers); // create a new game
    auto b = g.getBoard(); // get the board

    for (int i = 0; i < numPlayers; ++i) {
        std::string name;
        std::cout << "Please enter the name of player " << i + 1 << ": " << std::endl;
        std::cin >> name;
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
                std::cin.ignore();
            }
        }
    }
    std::cout << "Setting things up and starting the game" << std::endl;
    //g.setupBoard(); // set up the board

    return g;
}

int main(int argc, char* argv[]) {
    bool testingMode = false; // a flag to check if testing mode is on
    bool loadMode = false; // a flag to check if load mode is on
    std::string filename = ""; // a string to store the filename

    for (int i = 0; i < argc; ++i) {
        std::string input_arg = argv[i];
        if (input_arg == "-testing") { // if the input argument is -testing, set the flag to true
            testingMode = true;
            Game g;
            g.setTestingMode(testingMode);
        } else if (input_arg == "-load") { // if the input argument is -load file, set the filename to the input filename
            if (i + 1 >= argc) { // if the filename is not provided, print an appropriate error message
                std::cerr << "No file to load. Starting a new game" << std::endl;
                loadMode = false;
            } else {
                filename = argv[i + 1];
                loadMode = true; // set the flag to true
            }
        } else { // else, print an appropriate error message
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
        processInGameCommands(g); // process the in-game commands
    }
}
