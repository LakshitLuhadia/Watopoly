#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
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
#include "Textdisplay.h"

class TextDisplay; // Forward declaration of TextDisplay class

class Game: public Subject {
    bool testingMode; // a flag to check if testing mode is on
    std::shared_ptr<Board> board; // the board
    int numPlayers = 0; // the number of players
    std::shared_ptr<TextDisplay> td; // the text display
    void auction(std::shared_ptr<Property> property); // auction function

    public:
        // Ctor for Game
        Game(int numPlayers = 0);
        void notifyObservers(); // notify all observers
        void roll(int die1 = -1, int die2 = -1); // rolls the dice
        void next(); // moves to the next player
        void trade(std::string player, std::string give, std::string receive);
        void improve(const std::string& property, const std::string& action);
        void mortgage(std::string property);
        void unmortgage(std::string property);
        void bankrupt();
        void assets();
        void all();
        void save(std::string filename);
        void setNumPlayers(int numPlayers);
        void setNumRollsInTimsLine(int numRollsInTimsLine);
        void setPlayerTimCups(int pos, int TimCups);
        void setPlayerMoney(int pos, int money);
        void setPlayerPosition(int pos, int position);
        void addPlayer(std::string name, int money);
        void setPlayerCharacter(int pos, char character);
        void setupBoard();
        void setBuildingOwner(std::string buildingName, std::string owner);
        void setBuildingImprovements(std::string buildingName, int numImprovements);
        void setTestingMode(bool testingMode);
        bool getTestingMode() const;
        int getNumPlayers() const;
        std::shared_ptr<Board> getBoard() const;
};

#endif
