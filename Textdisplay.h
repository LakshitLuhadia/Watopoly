#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include "Game.h"
#include "Board.h"
#include "Observer.h"

class TextDisplay : public Observer {
    std::shared_ptr<Game> game; // Unique pointer to the Game object

public:
    // Constructor
    TextDisplay(std::shared_ptr<Game> game);

    void sideImprovements(string &line, int arr[2], shared_ptr<Board> board);

    void sidePlayers(string &line, int arr[2], vector<shared_ptr<Player>> players);


    // Override the notify function from Observer
    void notify(Subject &whoNotified) override;

    // Display the current state of the game
    void display();

    // Format a square for display
    //std::string formatSquare(const Square* square) const;
};

#endif