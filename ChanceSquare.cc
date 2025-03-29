#include "ChanceSquare.h"
#include "Player.h"
#include "Square.h"
#include "Board.h"
#include <memory>
#include <vector>
#include <string>
#include <stdlib.h>
using namespace std;

// ctor
ChanceSquare::ChanceSquare(string name, const int index, const bool isProperty) : NonProperty{name, index, isProperty}, totRimCups{0} {}


// performAction for FeesSquare
void ChanceSquare::performAction(shared_ptr<Player>& player) const {
    int rimCupChance = rand() % 100 + 1;
    if (rimCupChance == 1 && totRimCups < 4) {
        player->setNumRimCups(player->getNumRimCups() + 1);
        totRimCups++;
    } else if (getName() == "SLC") {
        int roll = rand() % 24 + 1;
        if (roll >= 1 && roll <= 3) {
            player->move(-3);
        } else if (roll >= 4 && roll <= 7) {
            player->move(-2);
        } else if (roll >= 8 && roll <= 11) {
            player->move(-1);
        } else if (roll >= 12 && roll <= 14) {
            player->move(1);
        } else if (roll >= 15 && roll <= 18) {
            player->move(2);
        } else if (roll >= 19 && roll <= 22) {
            player->move(3);
        } else if (roll == 23) {
            int timsLineIndex = 11;
            player->setPosition(timsLineIndex);
            player->setInTimsLine(true);
        } else if (roll == 24) {
            int OSAPIndex = 1;
            player->setPosition(OSAPIndex);
            // maybe add 200 depending on setPosition implementation in player
        }
    } else if (getName() == "NEEDLES HALL") {
        int roll = rand() % 18 + 1;
        if (roll == 1) {
            player->subtractMoney(200);
        } else if (roll >= 2 && roll <= 3) {
            player->subtractMoney(100);
        } else if (roll >= 4 && roll <= 6) {
            player->subtractMoney(50);
        } else if (roll >= 7 && roll <= 12) {
            player->addMoney(25);
        } else if (roll >= 13 && roll <= 15) {
            player->addMoney(50);
        } else if (roll >= 16 && roll <= 17) {
            player->addMoney(100);
        } else if (roll == 18) {
            player->addMoney(200);
        }
    }
}

