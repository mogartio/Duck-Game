#ifndef STAGE_H
#define STAGE_H

#include <algorithm>
#include <memory>
#include <string>
#define ROW_NUMBER 50
#define COLUMN_NUMBER 50
#include <vector>

#include "../player/projectile.h"

#include "map.h"

class Player;          // Declaracion adelantada para evitar dependencia circular.
class PlayerPosition;  // Idem
class Stage {
private:
    Map map;
    void printStage();
    std::vector<std::unique_ptr<Projectile>> projectiles;
    std::vector<Coordinate> coordinates_to_delete;

public:
    // Son es para poder mockear la clase mas facilmente
    void draw_player(Player&);
    bool is_valid_position(Coordinate, int);
    Stage(const std::string&);
    void delete_player_from_stage(Player&);
    void print();
    bool should_fall(PlayerPosition&);
    void add_projectile(std::unique_ptr<Projectile>&&);
    void remove_projectile(std::unique_ptr<Projectile>&);
    void update();
    void set(const Coordinate&, const int);
    int get(const Coordinate&);
};

#endif
