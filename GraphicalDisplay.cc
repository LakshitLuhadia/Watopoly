#include "GraphicalDisplay.h"
#include "Academic.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

GraphicalDisplay::GraphicalDisplay(shared_ptr<Board> board, int width, int height)
    : board(board), width(width), height(height), window(make_shared<Xwindow>(width, height)) {
    // Optionally, perform an initial draw here.
}

GraphicalDisplay::~GraphicalDisplay() {}

void GraphicalDisplay::display(shared_ptr<Board> board, const vector<shared_ptr<Player>>& players) {
    ifstream board_file("board.txt");
    if (!board_file.is_open()) {
        cerr << "GraphicalDisplay: Cannot open board.txt" << endl;
        return;
    }

    string line;
    int counter = 1;
    int squareWidth = 8;
    int sidesCol[2] = {1, 81};
    int lineHeight = 15; // vertical spacing (in pixels) between lines
    // Clear the window (fill entire area with a background color, e.g., Blue).
    window->fillRectangle(0, 0, width, height, Xwindow::White);

    while(getline(board_file, line)) {
        // Mimic modifications similar to TextDisplay:
        if (counter == 2) {
            int arr[6] = {21, 23, 24, 26, 27, 29};
            for (int i = 0; i < 6; ++i) {
                auto square = board->getSquare(arr[i]);
                auto academicBuilding = dynamic_pointer_cast<Academic>(square);
                if (academicBuilding) {
                    int tempCol = ((arr[i] - 21) * squareWidth) + squareWidth + 1;
                    for (int k = 0; k < academicBuilding->getNumImprovements(); ++k) {
                        if (tempCol + k < (int)line.size())
                            line[tempCol + k] = 'I';
                    }
                }
            }
        } else if (counter == 5) {
            for (int i = 20; i <= 30; ++i) {
                int tempCol = (i - 20) * squareWidth + 1;
                int k = 0;
                for (const auto& player : players) {
                    if (player->getPosition() == i) {
                        if (tempCol + k < (int)line.size())
                            line[tempCol + k] = player->getCharacter();
                        ++k;
                    }
                }
            }
        } else if (counter == 7) {
            int arr[2] = {19, 31};
            for (int j = 0; j < 2; ++j) {
                auto square = board->getSquare(arr[j]);
                auto academicBuilding = dynamic_pointer_cast<Academic>(square);
                if (academicBuilding) {
                    for (int k = 0; k < academicBuilding->getNumImprovements(); ++k) {
                        int index = sidesCol[j] + k;
                        if (index < (int)line.size()) line[index] = 'I';
                    }
                }
            }
        } else if (counter == 10) {
            int arr[2] = {19, 31};
            for (int j = 0; j < 2; ++j) {
                int k = 0;
                for (const auto& player : players) {
                    if (player->getPosition() == arr[j]) {
                        int index = sidesCol[j] + k;
                        if (index < (int)line.size()) line[index] = player->getCharacter();
                        ++k;
                    }
                }
            }
        } else if (counter == 12) {
            int arr[2] = {18, 32};
            for (int j = 0; j < 2; ++j) {
                auto square = board->getSquare(arr[j]);
                auto academicBuilding = dynamic_pointer_cast<Academic>(square);
                if (academicBuilding) {
                    for (int k = 0; k < academicBuilding->getNumImprovements(); ++k) {
                        int index = sidesCol[j] + k;
                        if (index < (int)line.size()) line[index] = 'I';
                    }
                }
            }
        } else if (counter == 15) {
            int arr[2] = {18, 32};
            for (int j = 0; j < 2; ++j) {
                int k = 0;
                for (const auto& player : players) {
                    if (player->getPosition() == arr[j]) {
                        int index = sidesCol[j] + k;
                        if (index < (int)line.size()) line[index] = player->getCharacter();
                        ++k;
                    }
                }
            }
        } else if (counter == 20) {
            int arr[2] = {17, 33};
            for (int j = 0; j < 2; ++j) {
                int k = 0;
                for (const auto& player : players) {
                    if (player->getPosition() == arr[j]) {
                        int index = sidesCol[j] + k;
                        if (index < (int)line.size()) line[index] = player->getCharacter();
                        ++k;
                    }
                }
            }
        } else if (counter == 22) {
            int arr[2] = {16, 34};
            for (int j = 0; j < 2; ++j) {
                auto square = board->getSquare(arr[j]);
                auto academicBuilding = dynamic_pointer_cast<Academic>(square);
                 if (academicBuilding) {
                    for (int k = 0; k < academicBuilding->getNumImprovements(); ++k) {
                        int index = sidesCol[j] + k;
                        if (index < (int)line.size()) line[index] = 'I';
                    }
                }
            }
        } else if (counter == 25) {
            int arr[2] = {16, 34};
            for (int j = 0; j < 2; ++j) {
                int k = 0;
                for (const auto& player : players) {
                    if (player->getPosition() == arr[j]) {
                        int index = sidesCol[j] + k;
                        if (index < (int)line.size()) line[index] = player->getCharacter();
                        ++k;
                    }
                }
            }
        } else if (counter == 30) {
            int arr[2] = {15, 35};
            for (int j = 0; j < 2; ++j) {
                int k = 0;
                for (const auto& player : players) {
                    if (player->getPosition() == arr[j]) {
                        int index = sidesCol[j] + k;
                        if (index < (int)line.size()) line[index] = player->getCharacter();
                        ++k;
                    }
                }
            }
        } else if (counter == 32) {
            auto square = board->getSquare(14);
            auto academicBuilding = dynamic_pointer_cast<Academic>(square);
            if (academicBuilding) {
                for (int k = 0; k < academicBuilding->getNumImprovements(); ++k) {
                    int index = sidesCol[0] + k;
                    if (index < (int)line.size()) line[index] = 'I';
                }
            }
        } else if (counter == 35) {
            int arr[2] = {14, 36};
            for (int j = 0; j < 2; ++j) {
                int k = 0;
                for (const auto& player : players) {
                    if (player->getPosition() == arr[j]) {
                        int index = sidesCol[j] + k;
                        if (index < (int)line.size()) line[index] = player->getCharacter();
                        ++k;
                    }
                }
            }
        } else if (counter == 37) {
            int arr[2] = {13, 37};
            for (int j = 0; j < 2; ++j) {
                auto square = board->getSquare(arr[j]);
                auto academicBuilding = dynamic_pointer_cast<Academic>(square);
                if (academicBuilding) {
                    for (int k = 0; k < academicBuilding->getNumImprovements(); ++k) {
                        int index = sidesCol[j] + k;
                        if (index < (int)line.size()) line[index] = 'I';
                    }
                }
            }
        } else if (counter == 40) {
            int arr[2] = {13, 37};
            for (int j = 0; j < 2; ++j) {
                int k = 0;
                for (const auto& player : players) {
                    if (player->getPosition() == arr[j]) {
                        int index = sidesCol[j] + k;
                        if (index < (int)line.size()) line[index] = player->getCharacter();
                        ++k;
                    }
                }
            }
        } else if (counter == 45) {
            int arr[2] = {12, 38};
            for (int j = 0; j < 2; ++j) {
                int k = 0;
                for (const auto& player : players) {
                    if (player->getPosition() == arr[j]) {
                        int index = sidesCol[j] + k;
                        if (index < (int)line.size()) line[index] = player->getCharacter();
                        ++k;
                    }
                }
            }
        } else if (counter == 47) {
            int arr[2] = {11, 39};
            for (int j = 0; j < 2; ++j) {
                auto square = board->getSquare(arr[j]);
                auto academicBuilding = dynamic_pointer_cast<Academic>(square);
                if (academicBuilding) {
                    for (int k = 0; k < academicBuilding->getNumImprovements(); ++k) {
                        int index = sidesCol[j] + k;
                        if (index < (int)line.size()) line[index] = 'I';
                    }
                }
            }
        } else if (counter == 50) {
            int arr[2] = {11, 39};
            for (int j = 0; j < 2; ++j) {
                int k = 0;
                for (const auto& player : players) {
                    if (player->getPosition() == arr[j]) {
                        int index = sidesCol[j] + k;
                        if (index < (int)line.size()) line[index] = player->getCharacter();
                        ++k;
                    }
                }
            }
        } else if (counter == 52) {
            int arr[5] = {9, 8, 6, 3, 1};
            for (int i = 0; i < 5; ++i) {
                auto square = board->getSquare(arr[i]);
                auto academicBuilding = dynamic_pointer_cast<Academic>(square);
                if (academicBuilding) {
                    int tempCol = ((9 - arr[i]) * squareWidth) + squareWidth + 1;
                    for (int k = 0; k < academicBuilding->getNumImprovements(); ++k) {
                        if (tempCol + k < (int)line.size())
                            line[tempCol + k] = 'I';
                    }
                }
            }
        } else if (counter == 55) {
            for (int i = 10; i >= 0; --i) {
                int tempCol = ((10 - i) * squareWidth) + 1;
                int k = 0;
                for (const auto& player : players) {
                    if (player->getPosition() == i) {
                        if (tempCol + k < (int)line.size())
                            line[tempCol + k] = player->getCharacter();
                        ++k;
                    }
                }
            }
        }
        // Draw the modified line in the window at x=0 and y determined by the counter.
        window->drawString(0, counter * lineHeight, line);
        counter++;
    }
}

void GraphicalDisplay::notify() {
    // Build the players vector using a safe loop (assumes board->getPlayer(i) returns nullptr when out-of-range).
    vector<shared_ptr<Player>> players;
    for (int i = 0; ; ++i) {
        auto p = board->getPlayer(i);
        if (!p) break;
        players.push_back(p);
    }
    display(board, players);
}
