#include "TimsLineSquare.h"
#include "Player.h"
#include <memory>
#include <vector>
#include <string>
using namespace std;

// ctor
TimsLineSquare::TimsLineSquare(const string name, const int index, const bool isProperty) : NonProperty{name, index, isProperty}, bailCost{50} {}

void TimsLineSquare::performAction(shared_ptr<Player> player) const {
    // theres nothing to do really
}
