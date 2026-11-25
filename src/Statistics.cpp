#include "Statistics.h"
#include "Exceptions.h"

#include<iomanip>

Statistics::Statistics(){
    gamesPlayed_ = 0;
}

int Statistics::addPlayer(const Player& player){
    if (findPlayer(player.getName()) != -1){
        throw DuplicatePlayerError(player.getName());
    }

    players_.push_back(player);
    return (int)players_.size() - 1;
}

int Statistics::findPlayer(const std::string& name) const{
    Player probe(name);

    for (int i = 0; i < (int)players_.size(); ++i){
        if (players_[i] == probe){   // Player::operator==
            return i;
        }
    }
    return -1;
}


int Statistics::getGamesPlayed() const{
    return gamesPlayed_;
}

const Player& Statistics::getPlayer(int index) const{
    return players_[index];
}

void Statistics::recordWin(int winner, int loser){
    players_[winner].addWin();
    players_[loser].addLoss();
    ++gamesPlayed_;
}

void Statistics::recordDraw(int first, int second){
    players_[first].addDraw();
    players_[second].addDraw();
    ++gamesPlayed_;
}







std::ostream& operator<<(std::ostream& out, const Statistics& stats) {
    out << "\n============ CURRENT STATISTICS ============\n";
    out << " || " << std::left << std::setw(10) << "NAME"
        << " || " << std::setw(6) << "WINS"
        << " || " << std::setw(8) << "LOSSES"
        << " || " << std::setw(7) << "DRAWS" << " ||\n";

    for (int i = 0; i < 2; ++i) {
        const Player& player = stats.getPlayer(i);
        out << " || " << std::left << std::setw(10) << player.getName()
            << " || " << std::setw(6) << player.getWins()
            << " || " << std::setw(8) << player.getLosses()
            << " || " << std::setw(7) << player.getDraws() << " ||\n";
    }

    out << "============================================\n";
    out << " GAMES PLAYED: " << stats.getGamesPlayed() << "\n";
    out << "============================================\n";
    return out;
}
