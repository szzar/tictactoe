#pragma once

#include<string>

class Player{
    private:
        std::string name_;
        int wins_;
        int losses_;
        int draws_;

    public:
        Player();
        Player(const std::string& name);

        // const = bcs they only read the objects
        const std::string& getName() const;
        int getWins() const;
        int getLosses() const;
        int getDraws() const;

        void setName(const std::string& name);
        void addWin();
        void addLoss();
        void addDraw();

        // statistics::findPlayer uses this to search the scoreboard vvv
        bool operator==(const Player& other) const; // true when both objects describe the same player
        //

};
