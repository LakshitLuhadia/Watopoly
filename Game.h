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

class Game: public Subject {
    static bool testingMode; // a flag to check if testing mode is on
    int numPlayers = 0; // the number of players
    Board *board; // the board

    public:
        // Ctor for Game
        Game();
        void roll(int die1 = -1, int die2 = -1); // rolls the dice
        void next(); // moves to the next player
        void trade(std::string player, std::string give, std::string receive);
        void improve(std::string property, std::string action);
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
        void addPlayer(std::string name);
        void setPlayerCharacter(int pos, char character);
        void setupBoard();
        void setupPlayers();
        void setBuildingOwner(std::string buildingName, std::string owner);
        void setBuildingImprovements(std::string buildingName, int numImprovements);
        void setTestingMode(bool testingMode);
        void notifyObservers();
        // Functions added after UML:

};

#endif
