#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include "Game.h"
#include "Board.h"
#include "Observer.h"

class TextDisplay : public Observer {
    std::unique_ptr<Game> g; // Unique pointer to the Game object

public:
    // Constructor
    TextDisplay(std::unique_ptr<Game> game);

    // Override the notify function from Observer
    void notify(Subject &whoNotified) override;

    // Display the current state of the game
    void display() const;

    // Format a square for display
    std::string formatSquare(const Square* square) const;
};

#endif