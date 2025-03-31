#ifndef GRAPHICALDISPLAY_H
#define GRAPHICALDISPLAY_H

#include <memory>
#include "Game.h"
#include <vector>
#include "Board.h"
#include "Player.h"
#include "Subject.h"

#include "Observer.h"
#include "XWindow.h"

class Game;

// Assuming that Observer is defined (as it is for TextDisplay).
class GraphicalDisplay : public Observer {
    std::shared_ptr<Board> board;
    int width, height;
    std::shared_ptr<Xwindow> window;
	
        // Helper functions for coloring.
    int getColorForPlayer(char c);
    void drawColoredChar(int col, int row, char c, int bgColor);

	public:
    // Constructor: create the Xwindow and store the game pointer.
    GraphicalDisplay(std::shared_ptr<Board> board, int width = 800, int height = 800);
    void display(std::shared_ptr<Board> board, const std::vector<std::shared_ptr<Player>>& players);
    // The notify method is called whenever the game state changes.
    virtual void notify() override;
    
    virtual ~GraphicalDisplay();
};

#endif
