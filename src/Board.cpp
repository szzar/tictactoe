#include "Board.h"
#include "Exceptions.h"

Board::Board(int size){ // checks the size and fills every cell with '#'
    if (size < 3 || size > 9){
        throw InvalidBoardSizeError(size);
    }
    // initializing the grid (printing happens in print())
    size_ = size;
    for (int row = 0; row < 9; ++row){
        for (int column = 0; column < 9; ++column){
            cells_[row][column] = '#';
        }
    }
}

int Board::getSize() const{
    return size_; // const bo nic nie zmienia
}

char Board::getCell(int row, int column) const{ // a translator from 1,1 to 0,0 standardizing operations on indexes for all the methods
    if (row < 1 || row > size_ || column < 1 || column > size_){
        throw OutofBoundsError(row, column, size_);
    }
    return cells_[row - 1][column - 1]; // because players make action on 1-n counting system, but code operations are on 0-n
}

bool Board::isFull() const{ // if it finds one #, returns false - board is not full
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
    if (getCell(row, column) != '#'){   // getCell here also throws error when off the board
        throw OccupiedCellError(row, column); // not '#' means it already has a mark -> illegal
    }
    cells_[row - 1][column - 1] = symbol; // symbol = mark = o/x
}

void Board::removeMark(int row, int column){
    if (row < 1 || row > size_ || column < 1 || column > size_){
        throw OutofBoundsError(row, column, size_);
    }
    cells_[row - 1][column - 1] = '#'; // changes back to #
}

void Board::clear(){ // calls removeMark on every cell
    for (int row = 1; row <= size_; ++row) {
        for (int column = 1; column <= size_; ++column){
            removeMark(row, column);
        }
    }
}

bool Board::isWinningMove(int row, int column) const{
    char symbol = getCell(row, column); // the mark that was just placed
    if (symbol == '#') {
        return false;
    }

    // four directions: across, down, and the two diagonals
    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
    // 0  1 -> step right (horizontal)
    // 1  0 -> step down (vertical)
    // 1  1 -> step down-right (the \ diagonal)
    // 1 -1 -> step down-left  (the / diagonal)

    for (int d = 0; d < 4; ++d){
        int count = 1;

        // walk once forwards and once backwards from the new mark
        for (int step = -1; step <= 1; step += 2){ // step = -1 walks backwards and then +1 (-1+2) forward
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

void Board::print() const{ // prints the header 1 2 3 .. and rows 
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
    winLength_ = (size >= 4) ? 4 : 3; // if size >= 4 then 4, otherwise 3 (on 4x4 or larger 3 is too easy)
}

std::string BoardCustom::getName() const{
    return std::to_string(getSize()) + "x" + std::to_string(getSize()); // NxN
}

int BoardCustom::getWinLength() const{
    return winLength_;
}

