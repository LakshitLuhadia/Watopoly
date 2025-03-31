#include "GoToTimsSquare.h"
#include "Player.h"
#include <memory>
#include <vector>
#include <string>
using namespace std;

// ctor
GoToTimsSquare::GoToTimsSquare(const string name, const int index, const bool isProperty, int timsLineIndex) : NonProperty{name, index, isProperty}, timsLineIndex{timsLineIndex} {}

// performAction for GoToTimsSquare
void GoToTimsSquare::performAction(shared_ptr<Player>& player) const {
    cout << "You have been sent to Tims Line!" << endl;
    player->setPosition(timsLineIndex);
    player->setInTimsLine(true);
}

