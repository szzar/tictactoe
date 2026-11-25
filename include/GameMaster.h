#pragma once

#include "Board.h"
#include <iostream>
#include <string>

enum Result {PLAYER_ONE_WINS, PLAYER_TWO_WINS, DRAW, QUIT}; // match end results

class GameMaster {
public:
    GameMaster(Board* board, const std::string& playerOne, const std::string& playerTwo);

    Result play();

private:
    std::string currentName() const; // name of the player whose turn it is
    char currentSymbol() const; // 'X' or 'O'

    Board* board_;
    std::string playerOne_;
    std::string playerTwo_;
    int current_; // 0 = player one, 1 = player two
};

