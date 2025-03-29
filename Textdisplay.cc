#include "Textdisplay.h"
using namespace std;

// Constructor
TextDisplay::TextDisplay(std::unique_ptr<Game> game) : 
g{std::move(game)} {} // TextDisplay::TextDisplay

// Override the notify function from Observer
void TextDisplay::notify(Subject &whoNotified) {
    display();
} // TextDisplay::notify

// Display the current state of the game
void TextDisplay::display() const {
    const Board& board = g->getBoard();
    const std::vector<Square*>& squares = board.getSquares();
    const std::vector<Player*>& players = g->getPlayers();

    // Board layout dimensions (adjust based on actual board structure)
    const int rows = 10; // Example rows
    const int cols = 4;  // Example columns

    // Create a grid to hold formatted strings
    std::vector<std::vector<std::string>> grid(rows, std::vector<std::string>(cols));

    // Populate grid with square info
    for (size_t i = 0; i < squares.size(); ++i) {
        const Square* square = squares[i];
        int row = i / cols;
        int col = i % cols;
        grid[row][col] = formatSquare(square);
    }

    // Overlay player positions on the grid
    for (const Player* player : players) {
        int pos = player->getPosition();
        int row = pos / cols;
        int col = pos % cols;
        // Append player's character to the square's string
        grid[row][col] += " " + player->getCharacter();
    }

    // Print the grid
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            std::cout << std::left << std::setw(20) << cell; 
        }
        std::cout << std::endl;
} // TextDisplay::display

// Format a square for display
std::string TextDisplay::formatSquare(const Square* square) const {
    std::string str;
    switch (square->getType()) {
        case Square::Type::ACADEMIC: {
            const Academic* academic = static_cast<const Academic*>(square);
            str = academic->getName();
            if (academic->getOwner()) {
                str += " (" + academic->getOwner()->getName().substr(0, 1) + ")";
            }
            int improvements = academic->getNumImprovements();
            if (improvements > 0) {
                str += " " + std::string(improvements, 'I');
            }
            break;
        }
        case Square::Type::RESIDENCE: {
            const Residence* residence = static_cast<const Residence*>(square);
            str = residence->getName();
            if (residence->getOwner()) {
                str += " (" + residence->getOwner()->getName().substr(0, 1) + ")";
            }
            break;
        }
        case Square::Type::GYM: {
            const Gym* gym = static_cast<const Gym*>(square);
            str = gym->getName();
            if (gym->getOwner()) {
                str += " (" + gym->getOwner()->getName().substr(0, 1) + ")";
            }
            break;
        }
        default: 
            str = square->getName();
            break;
    }
    return str;
} // TextDisplay::formatSquare