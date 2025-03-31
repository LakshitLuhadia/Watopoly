#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include "Game.h"
#include "Board.h"
#include "Observer.h"

class TextDisplay : public Observer {

public:
    // Constructor
    TextDisplay();
    
    // Override the notify function from Observer
    void notify() override;

    // Helper function to add improvements to the sides of the board
    void sideImprovements(std::string &line, int arr[2], std::shared_ptr<Board> board);

    // Helper function to add players to the sides of the board
    void sidePlayers(std::string &line, int arr[2], std::vector<std::shared_ptr<Player>> players);

    // Display the current state of the game
    void display(std::shared_ptr<Board> board, const std::vector<std::shared_ptr<Player>>& players);

};

#endif
