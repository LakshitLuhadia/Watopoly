#include "GraphicalDisplay.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>

// Constructor
GraphicalDisplay::GraphicalDisplay(std::shared_ptr<Game> game, int width, int height) 
    : game(game), width(width), height(height), needsRedraw(true) {
    
    // Create XWindow
    window = std::make_unique<XWindow>(width, height);
    window->setTitle("Watopoly - Graphical Display");
    
    // Calculate board dimensions
    boardSize = std::min(width, height) - 100;
    squareSize = boardSize / 11;
    boardX = (width - boardSize) / 2;
    boardY = 50;
    
    // Setup colors
    setupColors();
    
    // Map window (display it)
    window->map();
    
    std::cout << "GraphicalDisplay initialized with dimensions " << width << "x" << height << std::endl;
}

// Destructor
GraphicalDisplay::~GraphicalDisplay() {
    // XWindow destructor will handle cleanup
}

// Setup colors for properties and players
void GraphicalDisplay::setupColors() {
    // Property block colors
    const std::pair<std::string, const char*> colorMap[] = {
        {"Arts1", "brown"},
        {"Arts2", "pink"},
        {"Eng", "red"},
        {"Health", "orange"},
        {"Env", "yellow"},
        {"Sci1", "green"},
        {"Sci2", "blue"},
        {"Math", "purple"}
    };
    
    for (const auto& [block, colorName] : colorMap) {
        blockColors[block] = window->allocateColor(colorName);
    }
    
    // Player colors
    const char* playerColorNames[] = {
        "blue", "red", "green", "yellow", "cyan", "magenta", "orange", "dark green"
    };
    
    for (int i = 0; i < 8; i++) {
        playerColors[i] = window->allocateColor(playerColorNames[i]);
    }
}

// Get players from the game - helper method for this implementation
std::vector<std::shared_ptr<Player>> GraphicalDisplay::getGamePlayers() {
    std::vector<std::shared_ptr<Player>> players;
    int numPlayers = game->getNumPlayers();
    
    for (int i = 0; i < numPlayers; i++) {
        players.push_back(game->getBoard()->getPlayer(i));
    }
    
    return players;
}

// Get current player index - helper method for this implementation
int GraphicalDisplay::getCurrentPlayerIndex() {
    // In a real implementation, Game should have a getCurrentPlayerIndex() method
    // For now we'll return 0 as a dummy value
    return 0;
}

// Observer notification method
void GraphicalDisplay::notify() {
    needsRedraw = true;
    
    // Redraw the display
    drawBoard();
    drawPlayers();
    drawImprovements();
    drawPropertyOwnership();
    drawPlayerInfo();
    flushDisplay();
}

// Display the game state
void GraphicalDisplay::display(std::shared_ptr<Board> board, const std::vector<std::shared_ptr<Player>>& players) {
    if (needsRedraw) {
        drawBoard();
        drawPlayers();
        drawImprovements();
        drawPropertyOwnership();
        drawPlayerInfo();
        needsRedraw = false;
    }
    flushDisplay();
}

// Draw the game board
void GraphicalDisplay::drawBoard() {
    // Clear window
    window->clear();
    
    // Draw board outline
    window->drawRectangle(boardX, boardY, boardSize, boardSize, borderColor);
    
    // Draw grid for properties
    window->drawGrid(boardX, boardY, boardSize, boardSize, 11, 11);
    
    // Label the squares with property names
    std::shared_ptr<Board> board = game->getBoard();
    
    for (int i = 0; i < 40; i++) {
        std::shared_ptr<Square> square = board->getSquare(i);
        if (!square) continue;
        
        std::string name = square->getName();
        
        // Calculate position
        int x, y;
        calculateSquarePosition(i, x, y);
        
        // Draw property names (shortened if needed)
        if (name.length() > 10) {
            name = name.substr(0, 9) + "...";
        }
        
        window->drawCenteredText(window->getWindow(), name, x, y - squareSize / 3);
        
        // Draw position numbers for debugging
        std::string posStr = std::to_string(i);
        window->drawCenteredText(window->getWindow(), posStr, x, y);
    }
}

// Draw player tokens on the board
void GraphicalDisplay::drawPlayers() {
    std::vector<std::shared_ptr<Player>> players = getGamePlayers();
    
    for (size_t i = 0; i < players.size(); i++) {
        const auto& player = players[i];
        if (!player || player->getIsBankrupt()) continue;
        
        int position = player->getPosition();
        char symbol = player->getCharacter();
        
        // Calculate position on board
        int x, y;
        calculateSquarePosition(position, x, y);
        
        // Offset each player within the square
        int offsetX = (i % 4) * 15 - 30;
        int offsetY = (i / 4) * 15 - 15;
        
        // Draw player token (colored circle with character)
        unsigned long color = playerColors[i % 8];
        window->fillRectangle(x + offsetX - 10, y + offsetY + squareSize / 4, 20, 20, color);
        window->drawRectangle(x + offsetX - 10, y + offsetY + squareSize / 4, 20, 20, borderColor);
        
        std::string symbolStr(1, symbol);
        window->drawCenteredText(window->getWindow(), symbolStr, 
                               x + offsetX, y + offsetY + squareSize / 4 + 15);
    }
}

// Draw improvements on properties
void GraphicalDisplay::drawImprovements() {
    std::shared_ptr<Board> board = game->getBoard();
    
    for (int i = 0; i < 40; i++) {
        std::shared_ptr<Square> square = board->getSquare(i);
        std::shared_ptr<Academic> academic = std::dynamic_pointer_cast<Academic>(square);
        
        if (academic && academic->getNumImprovements() > 0) {
            int x, y;
            calculateSquarePosition(i, x, y);
            
            // Get improvements
            int improvements = academic->getNumImprovements();
            std::string block = academic->getBlock();
            unsigned long color = blockColors[block];
            
            // Draw improvements as small rectangles
            for (int j = 0; j < improvements; j++) {
                int impX = x - squareSize / 3 + j * 10;
                int impY = y + squareSize / 4 - 25;
                
                window->fillRectangle(impX, impY, 8, 8, color);
                window->drawRectangle(impX, impY, 8, 8, borderColor);
            }
        }
    }
}

// Draw property ownership
void GraphicalDisplay::drawPropertyOwnership() {
    std::shared_ptr<Board> board = game->getBoard();
    std::vector<std::shared_ptr<Player>> players = getGamePlayers();
    
    for (int i = 0; i < 40; i++) {
        std::shared_ptr<Square> square = board->getSquare(i);
        std::shared_ptr<Property> property = std::dynamic_pointer_cast<Property>(square);
        
        if (property) {
            std::shared_ptr<Player> owner = property->getOwner();
            if (owner) {
                int x, y;
                calculateSquarePosition(i, x, y);
                
                // Find player index
                int playerIndex = -1;
                for (size_t j = 0; j < players.size(); j++) {
                    if (players[j] == owner) {
                        playerIndex = j;
                        break;
                    }
                }
                
                if (playerIndex >= 0) {
                    // Draw ownership indicator
                    unsigned long color = playerColors[playerIndex % 8];
                    
                    // Draw border around property
                    int borderX = x - squareSize / 2 + 2;
                    int borderY = y - squareSize / 2 + 2;
                    int borderWidth = squareSize - 4;
                    int borderHeight = squareSize - 4;
                    
                    window->drawRectangle(borderX, borderY, borderWidth, borderHeight, color);
                    
                    // Indicate if mortgaged
                    if (property->getIsMortgaged()) {
                        window->drawLine(borderX, borderY, 
                                       borderX + borderWidth, borderY + borderHeight,
                                       borderColor);
                        window->drawLine(borderX + borderWidth, borderY, 
                                       borderX, borderY + borderHeight,
                                       borderColor);
                    }
                }
            }
        }
    }
}

// Draw player information
void GraphicalDisplay::drawPlayerInfo() {
    std::vector<std::shared_ptr<Player>> players = getGamePlayers();
    int currentPlayerIdx = getCurrentPlayerIndex();
    
    // Draw player info panel below the board
    int infoX = boardX;
    int infoY = boardY + boardSize + 20;
    int infoWidth = boardSize;
    int infoHeight = 100;
    
    window->drawRectangle(infoX, infoY, infoWidth, infoHeight, borderColor);
    
    // Draw current player indicator
    std::string currentPlayerText = "Current Player: ";
    if (currentPlayerIdx >= 0 && static_cast<size_t>(currentPlayerIdx) < players.size()) {
        currentPlayerText += players[currentPlayerIdx]->getName();
        currentPlayerText += " (";
        currentPlayerText += players[currentPlayerIdx]->getCharacter();
        currentPlayerText += ")";
    }
    
    window->drawString(infoX + 10, infoY + 20, currentPlayerText);
    
    // Draw player stats
    int statX = infoX + 10;
    int statY = infoY + 40;
    
    for (size_t i = 0; i < players.size() && i < 8; i++) {
        const auto& player = players[i];
        if (!player) continue;
        
        // Format player information
        std::stringstream ss;
        ss << player->getName() << " (" << player->getCharacter() << "): $" 
           << player->getMoney() << " - " 
           << (player->getIsBankrupt() ? "BANKRUPT" : "ACTIVE");
        
        std::string playerInfo = ss.str();
        
        // Draw with player color
        window->setForeground(playerColors[i % 8]);
        window->drawString(statX, statY, playerInfo);
        
        statY += 20;
    }
}

// Helper method to calculate square position
void GraphicalDisplay::calculateSquarePosition(int position, int& x, int& y) {
    // Bottom row (0-10)
    if (position >= 0 && position <= 10) {
        x = boardX + boardSize - (position * squareSize) - squareSize / 2;
        y = boardY + boardSize - squareSize / 2;
    }
    // Left column (11-19)
    else if (position >= 11 && position <= 19) {
        x = boardX + squareSize / 2;
        y = boardY + boardSize - ((position - 10) * squareSize) - squareSize / 2;
    }
    // Top row (20-30)
    else if (position >= 20 && position <= 30) {
        x = boardX + ((position - 20) * squareSize) + squareSize / 2;
        y = boardY + squareSize / 2;
    }
    // Right column (31-39)
    else {
        x = boardX + boardSize - squareSize / 2;
        y = boardY + ((position - 30) * squareSize) + squareSize / 2;
    }
}

// Helper method to draw centered text
void GraphicalDisplay::drawCenteredText(Window win, const std::string& text, int x, int y) {
    window->drawCenteredText(win, text, x, y);
}

// Getters
int GraphicalDisplay::getWidth() const {
    return width;
}

int GraphicalDisplay::getHeight() const {
    return height;
}

// Flush the display
void GraphicalDisplay::flushDisplay() {
    window->flush();
}
