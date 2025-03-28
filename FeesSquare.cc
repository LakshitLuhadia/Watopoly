#include "FeesSquare.h"
#include "Player.h"
#include <memory>
#include <vector>
#include <string>
using namespace std;

// ctor
FeesSquare::FeesSquare(const string name, const int index, const bool isProperty, int fees) : NonProperty{name, index, isProperty}, fees{fees} {}

// performAction for FeesSquare
void FeesSquare::performAction(shared_ptr<Player>& player) const {
    player->subtractMoney(fees);
}

