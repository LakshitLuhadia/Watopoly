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
class GraphicalDisplay; // Forward declaration of GraphicalDisplay class

class Game: public Subject {
    bool testingMode; // a flag to check if testing mode is on
    std::shared_ptr<Board> board; // the board
    int numPlayers = 0; // the number of players
    std::shared_ptr<TextDisplay> td; // the text display
    std::shared_ptr<GraphicalDisplay> gd; // the graphical display
    int getPropertyRent(std::shared_ptr<Property> property); // get the rent of a property
    void auction(std::shared_ptr<Property> property); // auction function
    void checkAcademicforMonopoly(std::shared_ptr<Player> owner, std::shared_ptr<Property> prop); // check for monopoly
    void checkResidenceforMonopoly(std::shared_ptr<Player> owner, std::shared_ptr<Property> prop); // check for monopoly
    void checkGymforMonopoly(std::shared_ptr<Player> owner, std::shared_ptr<Property> prop); // check for monopoly

    public:
        // Ctor for Game
        Game(int numPlayers = 0);
        void notifyObservers(); // notify all observers
        void roll(int die1 = -1, int die2 = -1); // rolls the dice
        void next(); // moves to the next player
        // trade function
        void trade(std::string player, std::string give, std::string receive);
        // improve academic properties function
        void improve(const std::string& property, const std::string& action);
        // mortage property function
        void mortgage(std::string property);
        // unmortgage property function
        void unmortgage(std::string property);
        // bankrupt function
        void bankrupt();
        // print a players assets function
        void assets();
        // print all players assets function
        void all();
        // save the game in filename 
        void save(std::string filename);
        // load the game from filename
        void setNumPlayers(int numPlayers);
        void setNumRollsInTimsLine(int numRollsInTimsLine);
        void setPlayerTimCups(int pos, int TimCups);
        void setPlayerMoney(int pos, int money);
        void setPlayerPosition(int pos, int position);
        void addPlayer(std::string name, int money);
        void removePlayer(std::string name);
        void setPlayerCharacter(int pos, char character);
        void setBuildingOwner(std::string buildingName, std::string owner);
        void setBuildingImprovements(std::string buildingName, int numImprovements);
        // set testing mode
        void setTestingMode(bool testingMode);
        // get testing mode
        bool getTestingMode() const;
        // get the number of players
        int getNumPlayers() const;
        // get the board
        std::shared_ptr<Board> getBoard() const;
};

#endif
