#include <algorithm>
#include <cmath>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../player/player.h"
#define FLOOR 1
#define BACKGROUND 0
#define PLAYER_SIZE 3
#define LEFT "a"
#define RIGHT "d"
#define UP "w"
#include "../player/weapons/projectiles/projectile.h"

#include "csv_reader.h"
#include "csv_writer.h"
#include "stage.h"

Stage::Stage(const std::string& file_name, SendQueuesMonitor<GenericMsg*>& senders):
        map(0, 0), senders(senders), obs(this->senders) {
    CSVWriter::write_map("main_map.csv");
    CSVReader reader(file_name);
    map = std::move(reader.read_map());
}

void Stage::print() { map.print(); }

void Stage::add_projectile(std::unique_ptr<Projectile>&& projectile) {
    projectile.get()->attach(&obs);
    projectiles.push_back(std::move(projectile));
}

void Stage::remove_projectile(std::unique_ptr<Projectile>& projectile) {
    auto position_to_delete = std::find_if(
            projectiles.begin(), projectiles.end(),
            [&](const std::unique_ptr<Projectile>& p) { return p.get() == projectile.get(); });
    if (position_to_delete != projectiles.end()) {  // si se encontro borrar, sino se encontro... no
        projectiles.erase(position_to_delete);
    }
}

void Stage::update() {
    for (auto& c: coordinates_to_delete) {
        map.set(c, BACKGROUND);
    }
    for (auto iterator = projectiles.begin(); iterator != projectiles.end();) {
        bool projectile_was_erased =
                (*iterator)->ray_trace(*this);  // *iterator = unique_ptr(projectile)
        if (projectile_was_erased) {
            remove_projectile(*iterator);
            continue;
        }
        iterator++;
    }
}

void Stage::draw_player(Player& player) {
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
    for (auto& coordinate: occupied) {
        map.set(coordinate, BACKGROUND);
    }
}

bool Stage::should_fall(PlayerPosition& player_position) {
    Coordinate current_position = player_position.get_position();
    Coordinate duck_feet(current_position.x, current_position.y + PLAYER_SIZE);
    for (int i = 0; i < PLAYER_SIZE; i++) {
        Coordinate aux(duck_feet.x + i, duck_feet.y);
        if (map.get(aux) == Config::get_instance()->mapsId["floor"] ||
            map.get(aux) == Config::get_instance()->mapsId["wall"]) {
            return false;
        }
    }
    return true;
}

bool Stage::is_valid_position(Coordinate position, int color) {
    for (int i = 0; i < PLAYER_SIZE; i++) {
        for (int j = 0; j < PLAYER_SIZE; j++) {
            Coordinate aux(position.x + j, position.y + i);
            if (map.out_of_range(aux)) {
                return false;
            }
            int value = map.get(aux);
            if (value != BACKGROUND && value != color) {
                return false;
            }
        }
    }
    return true;
}

void Stage::set(const Coordinate& coor, const int value) {
    map.set(coor, value);
    if (value > 1) {
        coordinates_to_delete.push_back(coor);
    }
}
int Stage::get(const Coordinate& coor) { return map.get(coor); }
