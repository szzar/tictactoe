#pragma once

#include <stdexcept>
#include<string>

class GameError: public std::runtime_error{
    public:
        GameError(const std::string& message): std::runtime_error(message){};
};

class OutofBoundsError: public GameError{
    public:
        OutofBoundsError(int row, int column, int size): GameError("OUT OF BOUNDS: (" + std::to_string(row) + ", " + std::to_string(column) +") is not on a " + std::to_string(size) + "x" + std::to_string(size) + " board."){};
}; // to_string converts the numbers to string ("str" + int does not compil because of params std::runtime accepts)

class OccupiedCellError: public GameError{
    public:
        OccupiedCellError(int row, int column): GameError("CELL TAKEN: (" + std::to_string(row) + ", " + std::to_string(column) +") already has been marked."){};
};


class InvalidBoardSizeError: public GameError {
    public:
    InvalidBoardSizeError(int size): GameError("INVALID SIZE: " + std::to_string(size) + " is not between 3 and 9."){};
};

class DuplicatePlayerError: public GameError {
    public:
        DuplicatePlayerError(const std::string& name): GameError("NAME TAKEN: " + name + " is already playing."){};
};

//std::runtime_error  stores a message and hands it back through what(). what() isused to get string identifying the exception
