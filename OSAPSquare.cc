#include "OSAPSquare.h"
#include "Player.h"
#include <memory>
#include <vector>
#include <string>
using namespace std;

// ctor
OSAPSquare::OSAPSquare(const string name, const int index, const bool isProperty) : NonProperty{name, index, isProperty}, collectAmount{200} {}

void OSAPSquare::performAction(shared_ptr<Player>& player) const {
    cout << "You have received 200 for OSAP!" << endl;
    player->addMoney(collectAmount);
}

