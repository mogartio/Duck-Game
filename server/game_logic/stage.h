#ifndef STAGE_H
#define STAGE_H

#include <string>
#define ROW_NUMBER 50
#define COLUMN_NUMBER 50
#include <vector>
#include "player.h"
#include "map.h"

class Stage{
private:
    Map map;
    std::vector<Player>& players;
    void printStage();
    void draw_player(Player&, Coordinate);
    bool is_valid_position(Player&, Coordinate);
public:
    Stage(std::vector<Player>&, const std::string&);
    void add_players_to_stage();
    void delete_player_from_stage(Player&);
    void move_player(Player&, const std::string&);
};

#endif 
