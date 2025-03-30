#include "Textdisplay.h"
#include <memory>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Constructor
TextDisplay::TextDisplay() {} // TextDisplay::TextDisplay

// Override the notify function from Observer
void TextDisplay::notify() {
    cout << "TextDisplay: Game state has changed." << endl;
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

void TextDisplay::display(std::shared_ptr<Board> board, const std::vector<std::shared_ptr<Player>>& players) {
    //shared_ptr<Board> board = game->getBoard();
    shared_ptr<Square> square;
    //vector<shared_ptr<Player>> players;
    // for (int i = 0; i < game->getNumPlayers(); ++i) {
    //     players.push_back(board->getPlayer(i));  
    // }
    ifstream board_file("board.txt");
    string line;
    int counter = 1;
    int squareWidth = 8;
    int sidesCol[2] = {1, 81};
    while (getline(board_file, line)) {
        if (counter == 2) {
            int arr[6] = {21, 23, 24, 26, 27, 29};
            for (int i = 0; i < 6; ++i) {
                square = board->getSquare(arr[i]);
                shared_ptr<Academic> academicBuilding = dynamic_pointer_cast<Academic>(square);
                int tempCol = ((arr[i] - 21) * squareWidth) + squareWidth + 1;
                for (int k = 0; k < academicBuilding->getNumImprovements(); ++k) {
                    line[tempCol + k] = 'I';
                }
            }
        } else if (counter == 5) {
            for (int i = 20; i <= 30; ++i) {
                int tempCol = (i - 20)*squareWidth + 1;
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
            int arr[2] = {19, 31};
            sideImprovements(line, arr, board);
        } else if (counter == 10) {
            int arr[2] = {19, 31};
            sidePlayers(line, arr, players);
        } else if (counter == 12) {
            int arr[2] = {18, 32};
            sideImprovements(line, arr, board);
        } else if (counter == 15) {
            int arr[2] = {18, 32};
            sidePlayers(line, arr, players);
        } else if (counter == 20) {
            int arr[2] = {17, 33};
            sidePlayers(line, arr, players);
        } else if (counter == 22) {
            int arr[2] = {16, 34};
            sideImprovements(line, arr, board);
        } else if (counter == 25) {
            int arr[2] = {16, 34};
            sidePlayers(line, arr, players);
        } else if (counter == 30) {
            int arr[2] = {15, 35};
            sidePlayers(line, arr, players);
        } else if (counter == 32) {
            shared_ptr<Square> square = board->getSquare(14);
            shared_ptr<Academic> academicBuilding = dynamic_pointer_cast<Academic>(square);
            for (int k = 0; k < academicBuilding->getNumImprovements(); ++k) {
                line[sidesCol[0] + k] = 'I';
            }
        } else if (counter == 35) {
            int arr[2] = {14, 36};
            sidePlayers(line, arr, players);
        } else if (counter == 37) {
            int arr[2] = {13, 37};
            sideImprovements(line, arr, board);
        } else if (counter == 40) {
            int arr[2] = {13, 37};
            sidePlayers(line, arr, players);
        } else if (counter == 45) {
            int arr[2] = {12, 38};
            sidePlayers(line, arr, players);
        } else if (counter == 47) {
            int arr[2] = {11, 39};
            sideImprovements(line, arr, board);
        } else if (counter == 50) {
            int arr[2] = {11, 39};
            sidePlayers(line, arr, players);
        } else if (counter == 52) {
            int arr[5] = {9, 8, 6, 3, 1};
            for (int i = 0; i < 5; ++i) {
                square = board->getSquare(arr[i]);
                shared_ptr<Academic> academicBuilding = dynamic_pointer_cast<Academic>(square);
                int tempCol = ((9 - arr[i]) * squareWidth) + squareWidth + 1;
                for (int k = 0; k < academicBuilding->getNumImprovements(); ++k) {
                    line[tempCol + k] = 'I';
                }
            }
        } else if (counter == 55) {
            for (int i = 10; i <= 1; --i) {
                int tempCol = (10 - i)*squareWidth + 1;
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
        cout << line << endl;
    }
}

