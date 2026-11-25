#include <iostream>
#include <string>

#include "Board.h"
#include "Exceptions.h"
#include "GameMaster.h"
#include "Player.h"
#include "Statistics.h"

void printIntro(){
    std::cout << "\n";
    std::cout << "===========================================\n";
    std::cout << "                TIC TAC TOE\n";
    std::cout << "===========================================\n\n";
}

void printWin(const std::string& name){
    std::cout << "\n===========================================\n";
    std::cout << " :D :D :D :D :D :D :D :D :D :D :D :D :D :D\n";
    std::cout << "        CONGRATS " << name << "! EPIC WIN\n";
    std::cout << " :D :D :D :D :D :D :D :D :D :D :D :D :D :D\n";
    std::cout << "===========================================\n";
}

void printLoss(const std::string& name){
    std::cout << "\n===========================================\n";
    std::cout << " :( :( :( :( :( :( :( :( :( :( :( :( :( :(\n";
    std::cout << "        WOMP WOMP " << name << "... BIG LOSS\n";
    std::cout << " :( :( :( :( :( :( :( :( :( :( :( :( :( :(\n";
    std::cout << "===========================================\n";
}

void printDraw(){
    std::cout << "\n===========================================\n";
    std::cout << " :| :| :| :| :| :| :| :| :| :| :| :| :| :|\n";
    std::cout << "          IT'S A DRAW... NOBODY WINS\n";
    std::cout << " :| :| :| :| :| :| :| :| :| :| :| :| :| :|\n";
    std::cout << "===========================================\n";
}

// getline bcs reads the whole line
std::string readName(const std::string& prompt){
    std::string name;

    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, name)) {
            return "";
        }
        if (!name.empty()) {
            return name;
        }
        std::cout << "A PLAYER NEEDS A NAME.\n";
    }
}


int readInt(const std::string& prompt){
    int value = 0;

    std::cout << prompt;
    while (!(std::cin >> value)){
        if (std::cin.eof()) {
            return -1;
        }
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "TYPE A NUMBER: ";
    }
    std::cin.ignore(1000, '\n');
    return value;
}

int registerPlayer(Statistics& stats, const std::string& prompt){
    Player player;

    while (true){
        std::string name = readName(prompt);
        if (name.empty()) {
            return -1;
        }

        player.setName(name);
        try{
            return stats.addPlayer(player);
        } catch (DuplicatePlayerError& error){
            std::cout << error.what() << "\n";
        }
    }
}

Board* chooseBoard(){
    while (true){
        std::cout << "\nCHOOSE YOUR BOARD:\n";
        std::cout << "  1) 3x3 - three in a row\n";
        std::cout << "  2) 5x5 - four in a row\n";
        std::cout << "  3) custom size (3-9)\n";

        int choice = readInt("CHOICE: ");
        if (choice == -1){
            return nullptr; // no board: the input ended, so main stops
        }
        if (choice == 1){
            return new Board3x3();
        }
        if (choice == 2){
            return new Board5x5();
        }
        if (choice == 3){
            int size = readInt("BOARD SIZE (3-9): ");
            if (size == -1){
                return nullptr;
            }
            try{
                return new BoardCustom(size);
            } catch (InvalidBoardSizeError& error){
                std::cout << error.what() << "\n"; //.what() is for getting the string identifying exceptions
            }
        } else{
            std::cout << "PICK 1, 2 OR 3.\n";
        }
    }
}

bool playAgain(){
    std::string answer;

    std::cout << "\nKEEP PLAYING? [Y/N] ";
    if (!std::getline(std::cin, answer)){
        return false;
    }
    return answer == "y" || answer == "Y" || answer == "yes" || answer == "YES";
}

int main(){
    printIntro();

    Statistics stats; // default constructor: empty scoreboard and 0 games

    int index1 = registerPlayer(stats, "PLAYER 1: ");
    if (index1 == -1){
        return 0;
    }
    int index2 = registerPlayer(stats, "PLAYER 2: ");
    if (index2 == -1){
        return 0;
    }

    Board* board = chooseBoard();  
    if (board == nullptr) {
        return 0;
    }

    bool swap = false;

    while (true){
        int starterIndex = swap ? index2 : index1; //
        int otherIndex = swap ? index1 : index2; // decide who is X this match

        board->clear();   // remove the marks from the previous match

        GameMaster game(board, stats.getPlayer(starterIndex).getName(),stats.getPlayer(otherIndex).getName());
        Result result = game.play();

        if (result == QUIT){
            break;
        }

        if (result == PLAYER_ONE_WINS){ // depending on who wins, correct printing order
            stats.recordWin(starterIndex, otherIndex);
            printWin(stats.getPlayer(starterIndex).getName());
            printLoss(stats.getPlayer(otherIndex).getName());
        } else if (result == PLAYER_TWO_WINS){
            stats.recordWin(otherIndex, starterIndex);
            printWin(stats.getPlayer(otherIndex).getName());
            printLoss(stats.getPlayer(starterIndex).getName());
        } else{
            stats.recordDraw(starterIndex, otherIndex);
            printDraw();
        }

        std::cout << stats;   // operator<<

        if (!playAgain()){
            break;
        }
        swap = !swap;
    }

    delete board;
    return 0;
}
