#include "Statistics.h"
#include "Exceptions.h"

#include<iomanip>









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
