#include "OSAPSquare.h"
#include "Player.h"
#include <memory>
using namespace std;

// ctor
OSAPSquare::OSAPSquare() : NonProperty{"COLLECT OSAP", 1, false}, collectAmount{200} {}

void OSAPSquare::performAction(shared_ptr<Player> player) const {
    player->addMoney(collectAmount);
}

