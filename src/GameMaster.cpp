#include "GameMaster.h"
#include "Exceptions.h"

GameMaster::GameMaster(Board* board, const std::string& playerOne, const std::string& playerTwo){
    board_ = board;
    playerOne_ = playerOne;
    playerTwo_ = playerTwo;
    current_ = 0;
}

Result GameMaster::play(){
    current_ = 0;

    while (true){
        std::cout << "\n===========================================\n";
        std::cout << " " << currentName() << " MOVES (" << currentSymbol() << ")\n";
        std::cout << " BOARD: " << board_->getName() << " - " << board_->getWinLength()
                  << " IN A ROW\n\n";
        board_->print();
        std::cout << "\nROW AND COLUMN: ";
        // basically does the NAME MOVES (x/o), BOARD: NxN - Y in a row and asks for coords

        int row = 0;
        int column = 0;

        if (!(std::cin >> row >> column)){
            if (std::cin.eof()){
                std::cout << "\nINPUT CLOSED.\n";
                return QUIT; // end of input (Ctrl-D or closed stream)
            }
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "ENTER TWO NUMBERS.\n";
            continue;
        }
        std::cin.ignore(1000, '\n');

        try {
            board_->placeMark(row, column, currentSymbol()); // placeMark throws so nothing is written!
        } catch (GameError& error){
            std::cout << error.what() << "\n";
            continue;   // error when placing a mark, e.g. trying to place out of bounds; player tries again
        }

        if (board_->isWinningMove(row, column)){
            std::cout << "\n";
            board_->print();
            return (current_ == 0) ? PLAYER_ONE_WINS : PLAYER_TWO_WINS;
        }
        if (board_->isFull()){
            std::cout << "\n";
            board_->print();
            return DRAW;
        }

        current_ = 1 - current_; // 0 becomes 1, 1 becomes 0
    }
}

std::string GameMaster::currentName() const{
    return (current_ == 0) ? playerOne_ : playerTwo_;
}

char GameMaster::currentSymbol() const{
    return (current_ == 0) ? 'X' : 'O';
}
