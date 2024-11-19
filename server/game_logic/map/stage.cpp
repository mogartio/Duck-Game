#include <algorithm>
#include <cmath>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../player/player.h"
#define FREE 0
#define OCCUPIED 1
#define DEATH -1
#define FLOOR 1
#define BACKGROUND 0
#define PLAYER_SIZE 3
#define LEFT "a"
#define RIGHT "d"
#define UP "w"
#include "../player/weapons/projectiles/projectile.h"
#include "../player/weapons/projectiles/projectile_dropped_weapon.h"

#include "csv_reader.h"
#include "csv_writer.h"
#include "stage.h"

Stage::Stage(const std::string& file_name, SendQueuesMonitor<std::shared_ptr<GenericMsg>>& senders,
             std::shared_ptr<std::set<uint>> ids):
        map(0, 0), senders(senders), obs(this->senders, ids) {
    CSVWriter::write_map("main_map.csv");
    CSVReader reader(file_name);
    map = std::move(reader.read_map());
}

void Stage::print() { map.print(); }

void Stage::add_projectile(std::shared_ptr<Projectile>&& projectile) {
    projectile.get()->attach(obs);
    projectiles.push_back(std::move(projectile));
}

void Stage::remove_projectile(std::shared_ptr<Projectile>& projectile) {
    auto position_to_delete = std::find_if(
            projectiles.begin(), projectiles.end(),
            [&](const std::shared_ptr<Projectile>& p) { return p.get() == projectile.get(); });
    if (position_to_delete != projectiles.end()) {  // si se encontro borrar, sino se encontro... no
        projectiles.erase(position_to_delete);
    }
}

void Stage::kill(int id) { players[id]->die(); }

void Stage::update() {
    for (const auto& c: coordinates_to_delete) {
        map.set(c, BACKGROUND);
    }
    coordinates_to_delete.clear();
    for (auto iterator = projectiles.begin(); iterator != projectiles.end();) {
        if (*iterator == nullptr) {
            continue;
        }
        bool projectile_was_erased =
                (*iterator)->ray_trace(*this);  // *iterator = unique_ptr(projectile)
        if (projectile_was_erased) {
            remove_projectile(*iterator);
            continue;
        }
        (*iterator)->update();
        iterator++;
    }
}

void Stage::add_player(Player* player, int id) { players[id] = player; }

void Stage::draw_player(Player& player) {
    if (!player.lives()) {
        return;
    }
    Coordinate init_position = player.get_position();
    int x = init_position.x;
    int y = init_position.y;
    for (int i = 0; i < PLAYER_SIZE; i++) {
        for (int j = 0; j < PLAYER_SIZE; j++) {
            Coordinate current(x + i, y + j);
            player.occupy(current);
            map.set(current, player.get_id());
        }
    }
}

void Stage::delete_player_from_stage(Player& player) {
    std::vector<Coordinate> occupied = player.get_occupied();
    for (const auto& coordinate: occupied) {
        map.set(coordinate,
                BACKGROUND);  //  TODO: eliminar todo esto y usar lo de coordenadas a borrar
    }
}

bool Stage::should_fall(PlayerPosition& player_position) {
    Coordinate current_position = player_position.get_position();
    Coordinate duck_feet(current_position.x, current_position.y + PLAYER_SIZE);
    for (int i = 0; i < PLAYER_SIZE; i++) {
        Coordinate aux(duck_feet.x + i, duck_feet.y);
        if (map.get(aux) != Config::get_instance()->mapsId["background"] && map.get(aux) != -1) {
            return false;
        }
    }
    return true;
}

// color seria el id del personaje
int Stage::is_valid_position(Coordinate position, int color) {
    for (int i = 0; i < PLAYER_SIZE; i++) {
        for (int j = 0; j < PLAYER_SIZE; j++) {
            Coordinate aux(position.x + j, position.y + i);
            if (map.out_of_range(aux)) {
                return DEATH;
            }
            int value = map.get(aux);
            if (value != BACKGROUND && value != color) {
                return OCCUPIED;
            }
        }
    }
    return FREE;
}

std::shared_ptr<Weapon> Stage::pick_weapon(Coordinate position) {
    for (auto& projectile: projectiles) {
        if (ProjectileDroppedWeapon* weaponProjectile =
                    dynamic_cast<ProjectileDroppedWeapon*>(projectile.get())) {
            if (weaponProjectile->get_position() == position) {
                std::shared_ptr new_weapon = (weaponProjectile->get_weapon());
                coordinates_to_delete.push_back(position);
                remove_projectile(projectile);
                return new_weapon;
            }
        }
        if (ProjectileThrownWeapon* weaponProjectile =
                    dynamic_cast<ProjectileThrownWeapon*>(projectile.get())) {
            if (weaponProjectile->get_position() == position) {
                std::shared_ptr new_weapon = weaponProjectile->get_weapon();
                coordinates_to_delete.push_back(position);
                remove_projectile(projectile);
                return new_weapon;
            }
        }
    }
    return nullptr;
}

void Stage::set(const Coordinate& coor, const int value) {
    map.set(coor, value);
    if (value > 1) {
        coordinates_to_delete.push_back(coor);
    }
}
int Stage::get(const Coordinate& coor) { return map.get(coor); }
