#ifndef STAGE_H
#define STAGE_H

#include <algorithm>
#include <memory>
#include <string>
#define ROW_NUMBER 100
#define COLUMN_NUMBER 100
#include <vector>

#include "../player/weapons/projectiles/projectile.h"

#include "map.h"

class Player;          // Declaracion adelantada para evitar dependencia circular.
class PlayerPosition;  // Idem
class Stage {
private:
    Map map;
    void printStage();
    std::vector<std::shared_ptr<Projectile>> projectiles;
    std::vector<Coordinate> coordinates_to_delete;
    SendQueuesMonitor<std::shared_ptr<GenericMsg>>& senders;
    ProjectileObserver obs;
    std::map<int, Player*> players;

public:
    // Son es para poder mockear la clase mas facilmente
    void draw_player(Player&);
    int is_valid_position(Coordinate, int);
    Stage(const std::string&, SendQueuesMonitor<std::shared_ptr<GenericMsg>>&,
          std::shared_ptr<std::set<uint>> ids);
    void delete_player_from_stage(Player&);
    void print();
    bool should_fall(PlayerPosition&);
    void add_projectile(std::shared_ptr<Projectile>&&);
    void remove_projectile(std::shared_ptr<Projectile>&);
    void update();
    void set(const Coordinate&, const int);
    int get(const Coordinate&);
    std::vector<uint16_t> get_vector_representation() { return map.get_vector_representation(); };
    void set_explosion(Coordinate, int) {
    };  // TODO: Implementar esto que recibe el centro y el rango de una explosion
    std::shared_ptr<Weapon> pick_weapon(Coordinate);
    void add_player(Player*, int id);
    void kill(int id);
    void draw(int object, int size, Coordinate init_position);
    std::set<int> things_projectile_hits(Coordinate position, int size);
};

#endif
