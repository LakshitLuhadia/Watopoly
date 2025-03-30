#include "ChanceSquare.h"
#include "Player.h"
#include "Square.h"
#include "Board.h"
#include <memory>
#include <vector>
#include <string>
#include <stdlib.h>
#include <ctime>
using namespace std;

// ctor
ChanceSquare::ChanceSquare(string name, const int index, const bool isProperty) : NonProperty{name, index, isProperty}, totRimCups{0} {
    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator
}


// performAction for FeesSquare
void ChanceSquare::performAction(shared_ptr<Player>& player) const {
    int rimCupChance = rand() % 100 + 1;
    if (rimCupChance == 1 && totRimCups < 4) {
        cout << "You have received a Rim Cup!" << endl;
        player->setNumRimCups(player->getNumRimCups() + 1);
        totRimCups++;
        cout << "You now have " << player->getNumRimCups() << " Rim Cups!" << endl;
    } else if (getName() == "SLC") {
        int roll = rand() % 24 + 1;
        if (roll >= 1 && roll <= 3) {
            cout << "You have to move back 3 spaces!" << endl;
            player->move(-3);
        } else if (roll >= 4 && roll <= 7) {
            cout << "You have to move back 2 spaces!" << endl;
            player->move(-2);
        } else if (roll >= 8 && roll <= 11) {
            cout << "You have to move back 1 space!" << endl;
            player->move(-1);
        } else if (roll >= 12 && roll <= 14) {
            cout << "You have to move forward 1 space!" << endl;
            player->move(1);
        } else if (roll >= 15 && roll <= 18) {
            cout << "You have to move forward 2 spaces!" << endl;
            player->move(2);
        } else if (roll >= 19 && roll <= 22) {
            cout << "You have to move forward 3 spaces!" << endl;
            player->move(3);
        } else if (roll == 23) {
            cout << "You have been sent to Tims Line!" << endl;
            int timsLineIndex = 11;
            player->setPosition(timsLineIndex);
            player->setInTimsLine(true);
        } else if (roll == 24) {
            cout << "You have been sent to OSAP!" << endl;
            int OSAPIndex = 1;
            player->setPosition(OSAPIndex);
            player->addMoney(200); // for OSAP fee
        }
    } else if (getName() == "NEEDLES HALL") {
        int roll = rand() % 18 + 1;
        if (roll == 1) {
            cout << "You have to pay $200!" << endl;
            player->subtractMoney(200);
        } else if (roll >= 2 && roll <= 3) {
            cout << "You have to pay $100!" << endl;
            player->subtractMoney(100);
        } else if (roll >= 4 && roll <= 6) {
            cout << "You have to pay $50!" << endl;
            player->subtractMoney(50);
        } else if (roll >= 7 && roll <= 12) {
            cout << "You just got $25!" << endl;
            player->addMoney(25);
        } else if (roll >= 13 && roll <= 15) {
            cout << "You just got $50!" << endl;
            player->addMoney(50);
        } else if (roll >= 16 && roll <= 17) {
            cout << "You just got $100!" << endl;
            player->addMoney(100);
        } else if (roll == 18) {
            cout << "You just got $200!" << endl;
            player->addMoney(200);
        }
    }
}

