#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include "Property.h"
#include "Square.h"
#include "Board.h"
#include "Square.h"
#include "Player.h"
using namespace std;

void Board::nextPlayer() {
    // Move to the next player
    currentPlayerIndex = (currentPlayerIndex + 1) % numPlayers;
}

std::shared_ptr<Property> Board::getPropertyByName(const std::string& name) const {
    // Get a property by name
    for (const auto& square : squares) {
        if (square->getName() == name && square->getIsProperty()) {
            return dynamic_cast<make_shared<Property>>(square.get());
        }
    }
    return nullptr; // Return nullptr if the property is not found
}

std::unique_ptr<Player> Board::getPlayerByName(const std::string& name) const {
    // Get a player by name
    for (auto player : players) {
        if (player->getName() == name) {
            return player;
        }
    }
    return nullptr; // Return nullptr if the player is not found
}

void Board::trade(std::string player, std::string give, std::string receive) {
    // Trade properties between players
    bool giveIsInt = std::all_of(give.begin(), give.end(), ::isdigit);
    bool receiveIsInt = std::all_of(receive.begin(), receive.end(), ::isdigit);

    if (giveIsInt && !receiveIsInt) {
        int money = getPlayerByName(player)->getMoney();
        int new_money = money + std::stoi(give);
        getPlayerByName(player)->setMoney(new_money);
        getPlayerByName(player)->removeProperty(getPropertyByName(receive));

        players[currentPlayerIndex]->addProperty(getPropertyByName(receive));
        players[currentPlayerIndex]->setMoney(players[currentPlayerIndex]->getMoney() - std::stoi(give));
    } else if (!giveIsInt && receiveIsInt) {
        int money = getPlayerByName(player)->getMoney();
        int new_money = money - std::stoi(receive);
        getPlayerByName(player)->setMoney(new_money);
        getPlayerByName(player)->addProperty(getPropertyByName(give));

        players[currentPlayerIndex]->removeProperty(getPropertyByName(give));
        players[currentPlayerIndex]->setMoney(players[currentPlayerIndex]->getMoney() + std::stoi(receive));
    } else if (!giveIsInt && !receiveIsInt) {
        getPlayerByName(player)->removeProperty(getPropertyByName(receive));
        players[currentPlayerIndex]->addProperty(getPropertyByName(receive));

        getPlayerByName(player)->addProperty(getPropertyByName(give));
        players[currentPlayerIndex]->removeProperty(getPropertyByName(give));
    }
}

std::unique_ptr<Player> Board::getCurrentPlayer() const {
    // Get the current player
    return players[currentPlayerIndex];
}
    
