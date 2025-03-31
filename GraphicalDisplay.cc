#include "GraphicalDisplay.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>

// Constructor
GraphicalDisplay::GraphicalDisplay(std::shared_ptr<Game> game, int width, int height) 
    : game(game), width(width), height(height), needsRedraw(true), activeDialog(0) {
    
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
    
    // Create command buttons
    createCommandButtons();
    
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
    // This is a temporary helper function to work around missing Game::getPlayers() method
    std::vector<std::shared_ptr<Player>> players;
    
    // Try to get player information from the game
    // Commented out to avoid unused variable warning
    // int numPlayers = game->getNumPlayers();
    
    // In the current implementation, we can't directly access the players
    // In a more complete implementation, Game class should have a getPlayers() method
    // For now, we'll return an empty list (or you could implement a different approach
    // like storing a reference to players when they're created)
    
    return players;
}

// Get current player index - helper method for this implementation
int GraphicalDisplay::getCurrentPlayerIndex() {
    // This is a temporary helper function to work around missing Game::getCurrentPlayerIndex() method
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

// Create buttons for game commands
void GraphicalDisplay::createCommandButtons() {
    // Button dimensions
    int buttonWidth = 100;
    int buttonHeight = 30;
    int buttonSpacing = 10;
    int buttonY = height - 50;
    
    // Button labels and commands
    std::vector<std::string> labels = {
        "Roll", "Next", "Trade", "Improve", "Mortgage", 
        "Unmortgage", "Bankrupt", "Assets", "All", "Save"
    };
    
    // Create buttons
    for (size_t i = 0; i < labels.size(); i++) {
        int buttonX = 30 + i * (buttonWidth + buttonSpacing);
        window->createButton(labels[i], buttonX, buttonY, buttonWidth, buttonHeight);
    }
}

// Process button clicks
void GraphicalDisplay::processButtonClick(int buttonIndex) {
    if (buttonIndex < 0 || static_cast<size_t>(buttonIndex) >= 10) return;
    
    std::string command;
    switch (buttonIndex) {
        case 0: command = "Roll"; break;
        case 1: command = "Next"; break;
        case 2: command = "Trade"; break;
        case 3: command = "Improve"; break;
        case 4: command = "Mortgage"; break;
        case 5: command = "Unmortgage"; break;
        case 6: command = "Bankrupt"; break;
        case 7: command = "Assets"; break;
        case 8: command = "All"; break;
        case 9: command = "Save"; break;
    }
    
    if (command == "Roll") {
        game->roll();
    } 
    else if (command == "Next") {
        game->next();
    } 
    else if (command == "Bankrupt") {
        game->bankrupt();
    } 
    else if (command == "Assets") {
        game->assets();
    } 
    else if (command == "All") {
        game->all();
    } 
    else {
        // Commands requiring parameters
        createDialogWindow(command);
    }
    
    // Refresh display
    needsRedraw = true;
}

// Create a dialog window for commands requiring parameters
void GraphicalDisplay::createDialogWindow(const std::string& command) {
    // Implement dialog windows for commands that need parameters
    if (activeDialog) {
        XDestroyWindow(window->getDisplay(), activeDialog);
    }
    
    int dialogWidth = 400;
    int dialogHeight = 250;
    int dialogX = (width - dialogWidth) / 2;
    int dialogY = (height - dialogHeight) / 2;
    
    activeDialog = XCreateSimpleWindow(
        window->getDisplay(), window->getWindow(),
        dialogX, dialogY, dialogWidth, dialogHeight, 2,
        borderColor, backgroundColor
    );
    
    XSelectInput(window->getDisplay(), activeDialog, ButtonPressMask | ExposureMask | KeyPressMask);
    XMapWindow(window->getDisplay(), activeDialog);
    
    // Dialog title
    std::string title = command + " Command";
    window->drawString(10, 30, title);
    
    // Command-specific instructions and input fields
    std::string instructions;
    
    if (command == "Trade") {
        instructions = "Trade with another player\n\nUsage: trade <player> <give> <receive>\n\n"
                       "- <player>: Name of the player to trade with\n"
                       "- <give>: Property name or money amount to give\n"
                       "- <receive>: Property name or money amount to receive";
    } 
    else if (command == "Improve") {
        instructions = "Buy or sell improvements on a property\n\nUsage: improve <property> <buy/sell>\n\n"
                       "- <property>: Name of the property to improve\n"
                       "- <buy/sell>: Whether to buy or sell an improvement";
    } 
    else if (command == "Mortgage") {
        instructions = "Mortgage a property to get funds\n\nUsage: mortgage <property>\n\n"
                       "- <property>: Name of the property to mortgage";
    } 
    else if (command == "Unmortgage") {
        instructions = "Unmortgage a property\n\nUsage: unmortgage <property>\n\n"
                       "- <property>: Name of the property to unmortgage";
    } 
    else if (command == "Save") {
        instructions = "Save the current game state\n\nUsage: save <filename>\n\n"
                       "- <filename>: Name of the file to save to";
    }
    
    // Draw multi-line instructions
    int lineHeight = 20;
    int y = 70;
    std::string line;
    std::istringstream iss(instructions);
    
    while (std::getline(iss, line)) {
        window->drawString(20, y, line);
        y += lineHeight;
    }
    
    // Create command execution button
    Window executeButton = XCreateSimpleWindow(
        window->getDisplay(), activeDialog,
        dialogWidth - 200, dialogHeight - 40, 90, 30, 1,
        borderColor, backgroundColor
    );
    
    XSelectInput(window->getDisplay(), executeButton, ButtonPressMask | ExposureMask);
    XMapWindow(window->getDisplay(), executeButton);
    
    std::string executeText = "Execute";
    window->drawCenteredText(executeButton, executeText, 45, 20);
    
    // Create close button
    Window closeButton = XCreateSimpleWindow(
        window->getDisplay(), activeDialog,
        dialogWidth - 100, dialogHeight - 40, 70, 30, 1,
        borderColor, backgroundColor
    );
    
    XSelectInput(window->getDisplay(), closeButton, ButtonPressMask | ExposureMask);
    XMapWindow(window->getDisplay(), closeButton);
    
    std::string closeText = "Close";
    window->drawCenteredText(closeButton, closeText, 35, 20);
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

// Handle X11 events
void GraphicalDisplay::handleEvents() {
    XEvent event;
    bool running = true;
    
    while (running) {
        if (!window->handleEvent(event)) continue;
        
        switch (event.type) {
            case Expose:
                if (event.xexpose.window == window->getWindow()) {
                    needsRedraw = true;
                }
                
                // Handle dialog expose
                if (activeDialog && event.xexpose.window == activeDialog) {
                    // Redraw dialog content if needed
                }
                break;
                
            case ButtonPress:
                // Handle main window clicks
                if (event.xbutton.window == window->getWindow()) {
                    // Process board clicks
                    int x = event.xbutton.x;
                    int y = event.xbutton.y;
                    
                    // Check if click is within board boundaries
                    if (x >= boardX && x <= boardX + boardSize &&
                        y >= boardY && y <= boardY + boardSize) {
                        // Process board click
                        // Could be used to show property details or select a square
                    }
                }
                
                // Handle button clicks
                int buttonIndex;
                if (window->isButtonClick(event.xbutton.window, buttonIndex)) {
                    processButtonClick(buttonIndex);
                }
                
                // Handle dialog button clicks
                if (activeDialog) {
                    if (event.xbutton.window == activeDialog) {
                        // Handle clicks inside the dialog
                    } else {
                        // Check for dialog child windows (like buttons)
                        Window clickedWindow = event.xbutton.window;
                        
                        // Check if it's the close button
                        if (clickedWindow != window->getWindow() && clickedWindow != activeDialog) {
                            // For now, just close the dialog
                            XDestroyWindow(window->getDisplay(), activeDialog);
                            activeDialog = 0;
                        }
                    }
                }
                break;
                
            case KeyPress: {
                KeySym key = XLookupKeysym(&event.xkey, 0);
                
                // 'q' or 'Q' to quit
                if (key == XK_q || key == XK_Q) {
                    running = false;
                }
                // 'r' to roll
                else if (key == XK_r || key == XK_R) {
                    game->roll();
                    needsRedraw = true;
                }
                // 'n' for next
                else if (key == XK_n || key == XK_N) {
                    game->next();
                    needsRedraw = true;
                }
                // Handle other key shortcuts as needed
                break;
            }
                
            case ConfigureNotify:
                // Handle window resize
                if (event.xconfigure.window == window->getWindow()) {
                    // Window has been resized
                    width = event.xconfigure.width;
                    height = event.xconfigure.height;
                    
                    // Recalculate board dimensions
                    boardSize = std::min(width, height) - 100;
                    squareSize = boardSize / 11;
                    boardX = (width - boardSize) / 2;
                    boardY = 50;
                    
                    needsRedraw = true;
                }
                break;
        }
        
        // Redraw if needed
        if (needsRedraw) {
            display(game->getBoard(), getGamePlayers());
            needsRedraw = false;
        }
    }
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
