#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include "Board.h"
#include "Game.h"
#include "Player.h"



Game processLoadedFile(const std::ifstream& filename) {
    std::ifstream loadfile(filename);
    if (loadfile.fail()) {
        std::cerr << "Cannot open the loaded file" << std::endl;
        return 1;
    }
    Game g;
    g.loadFile(loadfile); // Call the loadFile function in the Game class
    return g;
}

// Function to set up the game
Game setupGame() {
    Game g;
    Board b;
    std::vector<char> characters = {'G', 'B', 'D', 'P', 'S', '$', 'L', 'T'};
    std::cout << "Welcome to the game of Watopoly!" << std::endl;
    std::cout << "Please enter the number of players(2-6): " << std::endl;
    int numPlayers;
    if (!std::cin >> numPlayers || (!numPlayers >= 2 && !numPlayers <= 6)) { // if the number of players is not between 2 and 6, print an appropriate error message
        std::cerr << "Invalid number of players. Please enter an integer value between 2 and 6" << std::endl;
        std::cin.clear();
        std::cin.ignore();
        return 1;
    }
    g.setNumPlayers(numPlayers); // set the number of players
    for (int i = 0; i < numPlayers; ++i) {
        std::string name;
        std::cout << "Please enter the name of player " << i + 1 << ": " << std::endl;
        std::cin >> name;
        g.addPlayer(Player* name); // add the player
        bool validCharacter = false;
        while (!validCharacter) { // check if the character is valid
            std::cout << "Please enter " << name << "'s character: " << std::endl;
            std::string character;
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
    g.setupPropertires(); // set up the properties vector
    g.setupNonProperties(); // set up the non-properties vector
    g.setupBoard(); // set up the board
    g.setupPlayers(); // set up the players
    g.start(); // start the game

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
        } else if (input_arg == "-load file") { // if the input argument is -load file, set the filename to the input filename
            filename = argv[i + 1];
            loadMode = true; // set the flag to true
        } else { // else, print an appropriate error message
            std::cerr << "Invalid command line argument" << std::endl;
            return 1;
        }
    }
    
    if (testingMode) {
        std::cout << "Testing mode is on" << std::endl;
        inTestMode();
    }

    if (loadMode) {
        std::cout << "Using loaded game file" << std::endl;
        if (filename.empty() || filename == "") { // if the filename is empty, print an appropriate error message
            std::cerr << "No file to load" << std::endl;
            return 1;
        } else {
            std::ifstream loadFile{filename}; // open the file
            if (loadfile.fail()) { // if the file cannot be opened, print an appropriate error message
                std::cerr << "Cannot open the loaded file" << std::endl;
                return 1;
            } else {
                processLoadedFile(loadFile); // process the loaded file
            }
        }
    }

    gameSetup(); // set up the game
    processInGameCommands(); // process the in-game commands
    return 0;
}