#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Player.h"

// to facilitate object oeprations requirement tbh

class Statistics{
    private:
        std::vector<Player> players_;
        int gamesPlayed_;

    public:
        Statistics();

        int addPlayer(const Player& player); // returns the new index
        int findPlayer(const std::string& name) const; // -1 when no name match
        int getGamesPlayed() const;
        const Player& getPlayer(int index) const;

        void recordWin(int winner, int loser);
        void recordDraw(int first, int second);

};

std::ostream& operator<<(std::ostream& out, const Statistics& stats); // scoreboard printing
