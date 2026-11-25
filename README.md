# TIC TAC TOE

A two-player tic-tac-toe game for the terminal, written in C++17. Players enter
their names, choose a board, and play as many matches as they'd like while the
program keeps a scoreboard for the whole session.

## Features

- Three board types, one allowing some customization:
  - **3x3** with three in a row wins.
  - **5x5** with four in a row wins.
  - **Custom 3–9** with three in a row on a 3x3, four in a row from 4x4 upwards.
- Win detection.
- A scoreboard with wins, losses and draws.
- Sides swap after every match, so no one hogs the first move advantage.
- Board input error handling.

## Requirements

- A C++17 compiler.

## Build and run

### With make

From the game root:

```bash
make        # builds ./tictactoe
make run    # builds and starts the game
make clean  # removes build/ and the binary
```

### Without make

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude src/*.cpp -o tictactoe
./tictactoe
```

## How to play

1. Enter two player names. Blank names are rejected.
2. Choose a board: `1` for 3x3, `2` for 5x5, `3` for a custom size.
3. On your turn, type a row and a column separated by a space, for example
   `2 3`. Coordinates are **1-based**: `1 1` is the top-left cell.
4. After a win or a draw the scoreboard is printed. Answer `y` to play another
   match on the same board, or `n` to stop.
5. End of input (Ctrl-D) exits at any prompt.

## Example session

```text
===========================================
                TIC TAC TOE
===========================================

PLAYER 1: Alice
PLAYER 2: Bob

CHOOSE YOUR BOARD:
  1) 3x3 - three in a row
  2) 5x5 - four in a row
  3) custom size (3-9)
CHOICE: 1

===========================================
 Alice MOVES (X)
 BOARD: 3x3 - 3 IN A ROW

    1 2 3
1   # # #
2   # # #
3   # # #

ROW AND COLUMN: 1 1

===========================================
 Bob MOVES (O)
 BOARD: 3x3 - 3 IN A ROW

    1 2 3
1   X # #
2   # # #
3   # # #

ROW AND COLUMN: 1 1
CELL TAKEN: (1, 1) already has been marked.

[...]

===========================================
 Alice MOVES (X)
 BOARD: 3x3 - 3 IN A ROW

    1 2 3
1   X X #
2   # O O
3   # # #

ROW AND COLUMN: 1 3

    1 2 3
1   X X X
2   # O O
3   # # #

===========================================
 :D :D :D :D :D :D :D :D :D :D :D :D :D :D
        CONGRATS Alice! EPIC WIN
 :D :D :D :D :D :D :D :D :D :D :D :D :D :D
===========================================

===========================================
 :( :( :( :( :( :( :( :( :( :( :( :( :( :(
        WOMP WOMP Bob... BIG LOSS
 :( :( :( :( :( :( :( :( :( :( :( :( :( :(
===========================================

============ CURRENT STATISTICS ============
 || NAME       || WINS   || LOSSES   || DRAWS   ||
 || Alice      || 1      || 0        || 0       ||
 || Bob        || 0      || 1        || 0       ||
============================================
 GAMES PLAYED: 1
============================================

KEEP PLAYING? [Y/N] n
```

## UML class diagram

```mermaid
classDiagram
    direction TB

    class Board {
        <<abstract>>
        -int size_
        -char cells_[9][9]
        +Board(int size)
        +~Board()
        +getSize() int
        +getCell(int row, int column) char
        +isFull() bool
        +isWinningMove(int row, int column) bool
        +placeMark(int row, int column, char symbol) void
        +removeMark(int row, int column) void
        +clear() void
        +print() void
        +getName()*
        +getWinLength()*
    }

    class Board3x3 {
        +Board3x3()
        +getName() string
        +getWinLength() int
    }

    class Board5x5 {
        +Board5x5()
        +getName() string
        +getWinLength() int
    }

    class BoardCustom {
        -int winLength_
        +BoardCustom(int size)
        +getName() string
        +getWinLength() int
    }

    class Player {
        -string name_
        -int wins_
        -int losses_
        -int draws_
        +Player()
        +Player(string name)
        +getName() string
        +getWins() int
        +getLosses() int
        +getDraws() int
        +setName(string name) void
        +addWin() void
        +addLoss() void
        +addDraw() void
        +operator==(Player other) bool
    }

    class Statistics {
        -vector~Player~ players_
        -int gamesPlayed_
        +Statistics()
        +addPlayer(Player player) int
        +findPlayer(string name) int
        +getGamesPlayed() int
        +getPlayer(int index) Player
        +recordWin(int winner, int loser) void
        +recordDraw(int first, int second) void
    }

    class GameMaster {
        -Board* board_
        -string playerOne_
        -string playerTwo_
        -int current_
        +GameMaster(Board* board, string one, string two)
        +play() Result
        -currentName() string
        -currentSymbol() char
    }

    class Result {
        <<enumeration>>
        PLAYER_ONE_WINS
        PLAYER_TWO_WINS
        DRAW
        QUIT
    }

    class runtime_error {
        <<external>>
    }

    class GameError {
        <<exception>>
        +GameError(string message)
    }

    class OutofBoundsError {
        +OutofBoundsError(int row, int column, int size)
    }

    class OccupiedCellError {
        +OccupiedCellError(int row, int column)
    }

    class InvalidBoardSizeError {
        +InvalidBoardSizeError(int size)
    }

    class DuplicatePlayerError {
        +DuplicatePlayerError(string name)
    }

    Board <|-- Board3x3
    Board <|-- Board5x5
    Board <|-- BoardCustom

    GameMaster o-- Board : borrows (aggregation)
    Statistics *-- "0..*" Player : owns (composition)
    GameMaster ..> Result : returns

    runtime_error <|-- GameError
    GameError <|-- OutofBoundsError
    GameError <|-- OccupiedCellError
    GameError <|-- InvalidBoardSizeError
    GameError <|-- DuplicatePlayerError

    Board ..> GameError : throws
    Statistics ..> GameError : throws
    GameMaster ..> GameError : catches
```
