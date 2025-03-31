#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include "Property.h"
#include "Square.h"
#include "Board.h"
#include "Player.h"
using namespace std;

// Constructor for Board
Board::Board(int numPlayers) : numPlayers(numPlayers) {
    // Initialize the squares
    squares.push_back(std::make_shared<OSAPSquare>("OSAP", 0, false));
    squares.push_back(std::make_shared<Academic>("AL", 1, true, 40, true, false, false, "Arts1", 50, vector<int>{2, 10, 30, 90, 160, 250}));
    squares.push_back(std::make_shared<ChanceSquare>("SLC", 2, false));
    squares.push_back(std::make_shared<Academic>("ML", 3, true, 60, true, false, false, "Arts1", 50, vector<int>{4, 20, 60, 180, 320, 450}));
    squares.push_back(std::make_shared<FeesSquare>("TUITION", 4, false, 300));
    squares.push_back(std::make_shared<Residence>("MKV", 5, true, 200, false, true, false));
    squares.push_back(std::make_shared<Academic>("ECH", 6, true, 100, true, false, false, "Arts2", 50, vector<int>{6, 30, 90, 270, 400, 550}));
    squares.push_back(std::make_shared<ChanceSquare>("NEEDLES HALL", 7, false));
    squares.push_back(std::make_shared<Academic>("PAS", 8, true, 100, true, false, false, "Arts2", 50, vector<int>{6, 30, 90, 270, 400, 550}));
    squares.push_back(std::make_shared<Academic>("HH", 9, true, 120, true, false, false, "Arts2", 50, vector<int>{8, 40, 100, 300, 450, 600}));
    squares.push_back(std::make_shared<NonProperty>("DC Tims Line", 10, false));
    squares.push_back(std::make_shared<Academic>("RCH", 11, true, 140, true, false, false, "Eng", 100, vector<int>{10, 50, 150, 450, 625, 750}));
    squares.push_back(std::make_shared<Gym>("PAC", 12, true, 150, false, false, true));
    squares.push_back(std::make_shared<Academic>("DWE", 13, true, 140, true, false, false, "Eng", 100, vector<int>{10, 50, 150, 450, 625, 750}));
    squares.push_back(std::make_shared<Academic>("CPH", 14, true, 160, true, false, false, "Eng", 100, vector<int>{12, 60, 180, 500, 700, 900}));
    squares.push_back(std::make_shared<Residence>("UWP", 15, true, 200, false, true, false));
    squares.push_back(std::make_shared<Academic>("LHI", 16, true, 180, true, false, false, "Health", 100, vector<int>{14, 70, 200, 550, 750, 950}));
    squares.push_back(std::make_shared<ChanceSquare>("SLC", 17, false));
    squares.push_back(std::make_shared<Academic>("BMH", 18, true, 180, true, false, false, "Health", 100, vector<int>{14, 70, 200, 550, 750, 950}));
    squares.push_back(std::make_shared<Academic>("OPT", 19, true, 200, true, false, false, "Health", 100, vector<int>{16, 80, 220, 600, 800, 1000}));
    squares.push_back(std::make_shared<NonProperty>("Goose Nesting", 20, false));
    squares.push_back(std::make_shared<Academic>("EV1", 21, true, 220, true, false, false, "Env", 150, vector<int>{18, 90, 250, 700, 875, 1050}));
    squares.push_back(std::make_shared<ChanceSquare>("NEEDLES HALL", 22, false));
    squares.push_back(std::make_shared<Academic>("EV2", 23, true, 220, true, false, false, "Env", 150, vector<int>{18, 90, 250, 700, 875, 1050}));
    squares.push_back(std::make_shared<Academic>("EV3", 24, true, 240, true, false, false, "Env", 150, vector<int>{20, 100, 300, 750, 925, 1100}));
    squares.push_back(std::make_shared<Residence>("V1", 25, true, 200, false, true, false));
    squares.push_back(std::make_shared<Academic>("PHYS", 26, true, 260, true, false, false, "Sci1", 150, vector<int>{22, 110, 330, 800, 975, 1150}));
    squares.push_back(std::make_shared<Academic>("B1", 27, true, 260, true, false, false, "Sci1", 150, vector<int>{22, 110, 330, 800, 975, 1150}));
    squares.push_back(std::make_shared<Gym>("CIF", 28, true, 150, false, false, true));
    squares.push_back(std::make_shared<Academic>("B2", 29, true, 280, true, false, false, "Sci1", 150, vector<int>{24, 120, 360, 850, 1025, 1200}));
    squares.push_back(std::make_shared<GoToTimsSquare>("GO TO TIMS", 30, false, 11));
    squares.push_back(std::make_shared<Academic>("EIT", 31, true, 300, true, false, false, "Sci2", 200, vector<int>{26, 130, 390, 900, 1100, 1275}));
    squares.push_back(std::make_shared<Academic>("ESC", 32, true, 300, true, false, false, "Sci2", 200, vector<int>{26, 130, 390, 900, 1100, 1275}));  
    squares.push_back(std::make_shared<ChanceSquare>("SLC", 33, false));
    squares.push_back(std::make_shared<Academic>("C2", 34, true, 320, true, false, false, "Sci2", 200, vector<int>{28, 150, 450, 1000, 1200, 1400}));
    squares.push_back(std::make_shared<Residence>("REV", 35, true, 200, false, true, false));
    squares.push_back(std::make_shared<ChanceSquare>("NEEDLES HALL", 36, false));
    squares.push_back(std::make_shared<Academic>("MC", 37, true, 350, true, false, false, "Math", 200, vector<int>{35, 175, 500, 1100, 1300, 1500}));
    squares.push_back(std::make_shared<FeesSquare>("COOP FEE", 38, false, 150));
    squares.push_back(std::make_shared<Academic>("DC", 39, true, 400, true, false, false, "Math", 200, vector<int>{50, 200, 600, 1400, 1700, 2000}));

}


// This is a private function that gets a property by name
std::shared_ptr<Property> Board::getPropertyByName(const std::string& name) const {
    // Get a property by name
    for (const auto& square : squares) {
        if (square->getName() == name && square->getIsProperty()) {
            return std::dynamic_pointer_cast<Property>(square);
        }
    }
    return nullptr; // Return nullptr if the property is not found
}

// This is a private function that gets a player by name
std::shared_ptr<Player> Board::getPlayerByName(const std::string& name) const {
    // Get a player by name
    for (auto player : players) {
        if (player->getName() == name) {
            return player;
        }
    }
    return nullptr; // Return nullptr if the player is not found
}

// Move to the next player
void Board::nextPlayer() {
    numPlayers = players.size();
    currentPlayerIndex = (currentPlayerIndex + 1) % numPlayers;
}

// Add a player
void Board::addPlayer(string name, int money) {
    shared_ptr<Player> p = make_shared<Player>(name, money);
    players.push_back(p);
    numPlayers++;
}

// Remove a player
void Board::removePlayer(string name) {
    for (auto it = players.begin(); it != players.end(); ++it) {
        if ((*it)->getName() == name) {
            players.erase(it);
            break;
        }
    }
    numPlayers--;
}

// Trade properties between players
void Board::trade(std::string player, std::string give, std::string receive) {
    bool giveIsInt = std::all_of(give.begin(), give.end(), ::isdigit);
    bool receiveIsInt = std::all_of(receive.begin(), receive.end(), ::isdigit);

    if (giveIsInt && !receiveIsInt) {
        int money = getPlayerByName(player)->getMoney();
        int new_money = money + std::stoi(give);
        getPlayerByName(player)->setMoney(new_money);
        getPlayerByName(player)->auction(getPropertyByName(receive), players[currentPlayerIndex]);
        players[currentPlayerIndex]->setMoney(players[currentPlayerIndex]->getMoney() - std::stoi(give)); 
    
    } else if (!giveIsInt && receiveIsInt) {
        int money = getPlayerByName(player)->getMoney();
        int new_money = money - std::stoi(receive);
        getPlayerByName(player)->setMoney(new_money);
        players[currentPlayerIndex]->auction(getPropertyByName(give), getPlayerByName(player));
        players[currentPlayerIndex]->setMoney(players[currentPlayerIndex]->getMoney() + std::stoi(receive));
    } else if (!giveIsInt && !receiveIsInt) {
        players[currentPlayerIndex]->auction(getPropertyByName(give), getPlayerByName(player));
        getPlayerByName(player)->auction(getPropertyByName(receive), players[currentPlayerIndex]);
    } else {
        std::cout << "reject" << std::endl;
    }
}

// Get the current player
std::shared_ptr<Player> Board::getCurrentPlayer() const {
    return players[currentPlayerIndex];
}

// Get a player by index
std::shared_ptr<Player> Board::getPlayer(int i) const {
    return players[i];
}

// Get a square by index
std::shared_ptr<Square> Board::getSquare(int i) const {
    return squares[i];
}
