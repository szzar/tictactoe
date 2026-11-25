#include "Board.h"
#include "Exceptions.h"

Board::Board(int size){
    if (size < 3 || size > 9){
        throw InvalidBoardSizeError(size);
    }

    size_ = size;
    for (int row = 0; row < 9; ++row){
        for (int column = 0; column < 9; ++column){
            cells_[row][column] = '#';
        }
    }
}

int Board::getSize() const{
    return size_;
}

char Board::getCell(int row, int column) const{
    if (row < 1 || row > size_ || column < 1 || column > size_){
        throw OutofBoundsError(row, column, size_);
    }
    return cells_[row - 1][column - 1];
}

bool Board::isFull() const{
    for (int row = 1; row <= size_; ++row) {
        for (int column = 1; column <= size_; ++column){
            if (cells_[row - 1][column - 1] == '#'){
                return false;
            }
        }
    }
    return true;
}

void Board::placeMark(int row, int column, char symbol){
    if (getCell(row, column) != '#'){   // also throws error when off the board
        throw OccupiedCellError(row, column);
    }
    cells_[row - 1][column - 1] = symbol;
}

void Board::removeMark(int row, int column){
    if (row < 1 || row > size_ || column < 1 || column > size_){
        throw OutofBoundsError(row, column, size_);
    }
    cells_[row - 1][column - 1] = '#';
}

void Board::clear(){
    for (int row = 1; row <= size_; ++row) {
        for (int column = 1; column <= size_; ++column){
            removeMark(row, column);
        }
    }
}

bool Board::isWinningMove(int row, int column) const{
    char symbol = getCell(row, column);
    if (symbol == '#') {
        return false;
    }

    // four directions: across, down, and the two diagonals
    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};

    for (int d = 0; d < 4; ++d){
        int count = 1;

        // walk once forwards and once backwards from the new mark.
        for (int step = -1; step <= 1; step += 2){
            int r = row + directions[d][0] * step;
            int c = column + directions[d][1] * step;

            while (r >= 1 && r <= size_ && c >= 1 && c <= size_ &&
                   cells_[r - 1][c - 1] == symbol){
                ++count;
                r += directions[d][0] * step;
                c += directions[d][1] * step;
            }
        }

        if (count >= getWinLength()){
            return true;
        }
    }
    return false;
}

void Board::print() const{
    std::cout << "    ";
    for (int column = 1; column <= size_; ++column){
        std::cout << column << " ";
    }
    std::cout << "\n";

    for (int row = 1; row <= size_; ++row) {
        std::cout << row << "   ";
        for (int column = 1; column <= size_; ++column){
            std::cout << cells_[row - 1][column - 1] << " ";
        }
        std::cout << "\n";
    }
}

// 3x3

Board3x3::Board3x3(): Board(3){}

std::string Board3x3::getName() const{
    return "3x3";
}

int Board3x3::getWinLength() const{
    return 3;
}

// 5x5

Board5x5::Board5x5(): Board(5){}

std::string Board5x5::getName() const{
    return "5x5";
}

int Board5x5::getWinLength() const{
    return 4;
}

// CUSTOM

BoardCustom::BoardCustom(int size) : Board(size){
    winLength_ = (size >= 4) ? 4 : 3;
}

std::string BoardCustom::getName() const{
    return std::to_string(getSize()) + "x" + std::to_string(getSize());
}

int BoardCustom::getWinLength() const{
    return winLength_;
}

