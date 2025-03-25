#include <vector>
#include "Board.h"
#include "Square.h"
#include "Player.h"

void Board::nextPlayer() {
    // Move to the next player
    currentPlayerIndex = (currentPlayerIndex + 1) % numPlayers;
}
