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

public:
    Stage(std::vector<Player>&, const std::string&);
    void draw_initial_state();
    void add_players_to_stage();
};

#endif 
