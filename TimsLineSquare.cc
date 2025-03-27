#include "TimsLineSquare.h"
#include "Player.h"
#include <memory>
using namespace std;

// ctor
TimsLineSquare::TimsLineSquare() : NonProperty{"DC Tims Line", 11, false}, bailCost{50} {}

void TimsLineSquare::performAction(shared_ptr<Player> player) const {

}
