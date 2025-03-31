#ifndef GRAPHICAL_DISPLAY_H
#define GRAPHICAL_DISPLAY_H
#include "Observer.h"
#include "Game.h"
#include "Board.h"
#include "XWindow.h"

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <atomic>

class GraphicalDisplay : public Observer {
    // Order these to match constructor initialization list
    std::shared_ptr<Game> game;
    int width, height;
    std::unique_ptr<XWindow> window;
    
    // Board layout constants
    int boardSize;
    int squareSize;
    int boardX, boardY;
    
    // Property colors by block
    std::map<std::string, unsigned long> blockColors;
    
    // UI state
    bool needsRedraw;
    
    // Colors for players and UI elements
    unsigned long playerColors[8];
    unsigned long backgroundColor;
    unsigned long textColor;
    unsigned long borderColor;
    
public:
    // Constructor and destructor
    GraphicalDisplay(std::shared_ptr<Game> game, int width = 800, int height = 800);
    ~GraphicalDisplay();
    
    // Observer interface
    void notify() override;
    
    // Display methods
    void display(std::shared_ptr<Board> board, const std::vector<std::shared_ptr<Player>>& players);
    int getWidth() const;
    int getHeight() const;
    
    // Drawing methods
    void drawBoard();
    void drawPlayers();
    void drawImprovements();
    void drawPropertyOwnership();
    void drawPlayerInfo();
    
    // Helper methods for player data (temporary workarounds)
    std::vector<std::shared_ptr<Player>> getGamePlayers();
    int getCurrentPlayerIndex();
    
    // Utility methods
    void setupColors();
    void calculateSquarePosition(int position, int& x, int& y);
    void drawCenteredText(Window win, const std::string& text, int x, int y);
    void flushDisplay();
};

#endif
