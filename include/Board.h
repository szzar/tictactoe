#pragma once

#include<string>
#include<iostream>

class Board{
    private:
        int size_;
        char cells_[9][9]; // 9x9 is the largest board allowed. char for holding #/x/o

    public:
        Board(int size);
        virtual ~Board(){};

        int getSize() const;
        char getCell(int row, int column) const; // wspolrzedna kratki (row column)
        
        bool isFull() const;
        bool isWinningMove(int row, int column) const;

        void placeMark(int row, int column, char symbol);
        void removeMark(int row, int column); // clears one cell (used by clear())
        void clear(); 
        void print() const;

        virtual std::string getName() const = 0;
        virtual int getWinLength() const = 0;
};

class Board3x3: public Board{
    public:
        Board3x3();
        std::string getName() const override;
        int getWinLength() const override;
};

class Board5x5: public Board{
    public:
        Board5x5();
        std::string getName() const override;
        int getWinLength() const override;
};

class BoardCustom : public Board{
    private:
        int winLength_;
    public:
        BoardCustom(int size);
        std::string getName() const override;
        int getWinLength() const override;
};
