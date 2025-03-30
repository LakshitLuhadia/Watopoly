#include "Textdisplay.h"
#include <memory>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Constructor
TextDisplay::TextDisplay(std::shared_ptr<Game> game) : 
game{move(game)} {} // TextDisplay::TextDisplay

// Override the notify function from Observer
void TextDisplay::notify() {
    display();
} // TextDisplay::notify

void TextDisplay::sideImprovements(string &line, int arr[2], shared_ptr<Board> board) {
    int sidesCol[2] = {1, 81};
    for (int i = 0; i < 2; ++i) {
        shared_ptr<Square> square = board->getSquare(arr[i]);
        shared_ptr<Academic> academicBuilding = dynamic_pointer_cast<Academic>(square);
        for (int k = 0; k < academicBuilding->getNumImprovements(); ++k) {
            line[sidesCol[i] + k] = 'I';
        }
    }
}

void TextDisplay::sidePlayers(string &line, int arr[2], vector<shared_ptr<Player>> players) {
    int sidesCol[2] = {1, 81};
    for (int i = 0; i < 2; ++i) {
        int k = 0;
        for (const auto& player : players) {
            if (player->getPosition() == arr[i]) {
                line[sidesCol[i] + k] = player->getCharacter();
                ++k;
            }
        }
    }
}

void TextDisplay::display() {
    shared_ptr<Board> board = game->getBoard();
    shared_ptr<Square> square;
    vector<shared_ptr<Player>> players;
    for (int i = 0; i < game->getNumPlayers(); ++i) {
        players.push_back(board->getPlayer(i));  
    }
    ifstream board_file("board.txt");
    string line;
    int counter = 1;
    int squareWidth = 8;
    int sidesCol[2] = {1, 81};
    while (getline(board_file, line)) {
        if (counter == 2) {
            int arr[6] = {22, 24, 25, 27, 28, 30};
            for (int i = 0; i < 6; ++i) {
                square = board->getSquare(arr[i]);
                shared_ptr<Academic> academicBuilding = dynamic_pointer_cast<Academic>(square);
                int tempCol = ((arr[i] - 22) * squareWidth) + squareWidth + 1;
                for (int k = 0; k < academicBuilding->getNumImprovements(); ++k) {
                    line[tempCol + k] = 'I';
                }
            }
        } else if (counter == 5) {
            for (int i = 21; i <= 31; ++i) {
                int tempCol = (i - 21)*squareWidth + 1;
                int k = 0;
                for (const auto& player : players) {
                    if (player->getPosition() == i) {
                        line[tempCol + k] = player->getCharacter();
                        ++k;
                    }
                }

            }
        } 
        else if (counter == 7) {
            int arr[2] = {20, 32};
            sideImprovements(line, arr, board);
        } else if (counter == 10) {
            int arr[2] = {20, 32};
            sidePlayers(line, arr, players);
        } else if (counter == 12) {
            int arr[2] = {19, 33};
            sideImprovements(line, arr, board);
        } else if (counter == 15) {
            int arr[2] = {19, 33};
            sidePlayers(line, arr, players);
        } else if (counter == 20) {
            int arr[2] = {18, 34};
            sidePlayers(line, arr, players);
        } else if (counter == 22) {
            int arr[2] = {17, 35};
            sideImprovements(line, arr, board);
        } else if (counter == 25) {
            int arr[2] = {17, 35};
            sidePlayers(line, arr, players);
        } else if (counter == 30) {
            int arr[2] = {16, 36};
            sidePlayers(line, arr, players);
        } else if (counter == 32) {
            shared_ptr<Square> square = board->getSquare(15);
            shared_ptr<Academic> academicBuilding = dynamic_pointer_cast<Academic>(square);
            for (int k = 0; k < academicBuilding->getNumImprovements(); ++k) {
                line[sidesCol[0] + k] = 'I';
            }
        } else if (counter == 35) {
            int arr[2] = {15, 37};
            sidePlayers(line, arr, players);
        } else if (counter == 37) {
            int arr[2] = {14, 38};
            sideImprovements(line, arr, board);
        } else if (counter == 40) {
            int arr[2] = {14, 38};
            sidePlayers(line, arr, players);
        } else if (counter == 45) {
            int arr[2] = {13, 39};
            sidePlayers(line, arr, players);
        } else if (counter == 47) {
            int arr[2] = {12, 40};
            sideImprovements(line, arr, board);
        } else if (counter == 50) {
            int arr[2] = {12, 40};
            sidePlayers(line, arr, players);
        } else if (counter == 52) {
            int arr[5] = {10, 9, 7, 4, 2};
            for (int i = 0; i < 5; ++i) {
                square = board->getSquare(arr[i]);
                shared_ptr<Academic> academicBuilding = dynamic_pointer_cast<Academic>(square);
                int tempCol = ((10 - arr[i]) * squareWidth) + squareWidth + 1;
                for (int k = 0; k < academicBuilding->getNumImprovements(); ++k) {
                    line[tempCol + k] = 'I';
                }
            }
        } else if (counter == 55) {
            for (int i = 11; i <= 1; --i) {
                int tempCol = (11 - i)*squareWidth + 1;
                int k = 0;
                for (const auto& player : players) {
                    if (player->getPosition() == i) {
                        line[tempCol + k] = player->getCharacter();
                        ++k;
                    }
                }

            }
        }
        counter++;
        cout << line;
    }
}

/*
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
 */

