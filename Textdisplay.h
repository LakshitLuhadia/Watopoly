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

    void sideImprovements(std::string &line, int arr[2], std::shared_ptr<Board> board);

    void sidePlayers(std::string &line, int arr[2], std::vector<std::shared_ptr<Player>> players);


    // Override the notify function from Observer
    void notify() override;

    // Display the current state of the game
    void display(std::shared_ptr<Board> board, const std::vector<std::shared_ptr<Player>>& players);

    
};

#endif