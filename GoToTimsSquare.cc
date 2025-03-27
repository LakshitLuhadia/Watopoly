#include "GoToTimsSquare.h"
#include "Player.h"
#include <memory>
#include <vector>
#include <string>
using namespace std;

// ctor
GoToTimsSquare::GoToTimsSquare(const string name, const int index, const bool isProperty, int timsLineIndex) : NonProperty{name, index, isProperty}, timsLineIndex{timsLineIndex} {}

// performAction for FeesSquare
void GoToTimsSquare::performAction(shared_ptr<Player> player) const {
    player->move(timsLineIndex);
    player->setInTimsLine(true);
}

