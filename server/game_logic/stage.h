#ifndef STAGE_H
#define STAGE_H

#define ROW_NUMBER 50
#define COLUMN_NUMBER 50
#include <vector>
#include "player.h"

class Stage{
private:
    int matrix[ROW_NUMBER][COLUMN_NUMBER];
    std::vector<Player>& players;
    void printStage();

public:
    Stage(std::vector<Player>&);
    void draw_initial_state();
    void add_players_to_stage();
};

#endif 
