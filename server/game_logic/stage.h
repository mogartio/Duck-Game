#ifndef STAGE_H
#define STAGE_H

#include <string>
#include "air_state.h"
#define ROW_NUMBER 50
#define COLUMN_NUMBER 50
#include <vector>
#include "map.h"

class Player; // Declaracion adelantada para evitar dependencia circular.
class Stage{
private:
    Map map;
    void printStage();
public:
    void draw_player(Player&);
    bool is_valid_position(Player&, Coordinate);
    Stage(const std::string&);
    void delete_player_from_stage(Player&);
    void move_player(Player&, const std::string&);
    void print();
    bool should_fall(Player&);
};

#endif 
