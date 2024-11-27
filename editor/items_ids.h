#ifndef ITEMS_IDS_H_
#define ITEMS_IDS_H_

#include "../common/messages/generic_msg.h"
#include <set>

namespace Id {
    static const int EMPTY = 100;
    static const int ROCK = 101;
    static const int GRASS = 102;
    static const int COL = 103;
    static const int AK_47 = static_cast<int>(ProjectilesId::AK_47);
    static const int BANANA = static_cast<int>(ProjectilesId::BANANA);
    static const int COWBOY_PISTOL = static_cast<int>(ProjectilesId::COWBOY_PISTOL);
    static const int DUEL_PISTOL = static_cast<int>(ProjectilesId::DUEL_PISTOL);
    static const int SHOTGUN = static_cast<int>(ProjectilesId::SHOTGUN);
    static const int GRENADE = static_cast<int>(ProjectilesId::GRENADE);
    static const int MAGNUM = static_cast<int>(ProjectilesId::MAGNUM);
    static const int SNIPER = static_cast<int>(ProjectilesId::SNIPER);
    static const int LASER_RIFLE = static_cast<int>(ProjectilesId::LASER_RIFLE);
    static const int PEW_PEW_LASER = static_cast<int>(ProjectilesId::PEW_PEW_LASER);
    static const int HELMET = static_cast<int>(ProjectilesId::HELMET);
    // static const int HELMET2 = static_cast<int>(ProjectilesId::HELMET2);
    // static const int HELMET3 = static_cast<int>(ProjectilesId::HELMET3);
    static const int CHEST = static_cast<int>(ProjectilesId::CHEST);
    static const int PLAYER1 = 104;
    static const int PLAYER2 = 105;
    static const int PLAYER3 = 106;
    static const int PLAYER4 = 107;

    extern const std::set<int> weapons;
    extern const std::set<int> players;
    extern const std::set<int> map_items;
}

#endif // ITEMS_IDS_H_