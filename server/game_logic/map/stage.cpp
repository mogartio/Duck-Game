#include <algorithm>
#include <cmath>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../player/player.h"
#include "../player/weapons/mystery_box.h"
#define FREE 0
#define OCCUPIED 1
#define DEATH -1
#define FLOOR 1
#define BACKGROUND 0
#define PLAYER_SIZE 6
#define BOX_SIZE 4
#define LEFT "a"
#define RIGHT "d"
#define UP "w"
#include "../player/weapons/projectiles/projectile.h"
#include "../player/weapons/projectiles/projectile_dropped_weapon.h"

#include "stage.h"

Stage::Stage(Map& map, SendQueuesMonitor<std::shared_ptr<GenericMsg>>& senders,
             std::shared_ptr<std::set<uint>> ids):
        map(map), senders(senders), obs(this->senders, ids) {}

void Stage::print() { map.print(); }

void Stage::add_projectile(std::shared_ptr<Projectile>&& projectile) {
    projectile.get()->attach(obs);
    projectile->updateShot();
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

void Stage::remove_box(std::shared_ptr<MysteryBox>& box) {
    auto position_to_delete = std::find_if(
            boxes.begin(), boxes.end(),
            [&](const std::shared_ptr<MysteryBox>& b) { return b.get() == box.get(); });
    if (position_to_delete != boxes.end()) {  // si se encontro borrar, sino se encontro... no
        boxes.erase(position_to_delete);
    }
}

void Stage::kill(int id) { players[id]->die(); }

bool Stage::take_damage(int player_id) {
    if (players[player_id]->has_chest() || players[player_id]->has_helmet()) {
        players[player_id]->take_damage();
        return true;
    }
    return false;
}

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
        if (*iterator) {
            projectile_was_erased = (*iterator)->update();
        }
        if (projectile_was_erased) {
            remove_projectile(*iterator);
            continue;
        }
        iterator++;
    }
    for (const auto& box: new_boxes) {
        Coordinate position = box->get_position();
        obs.update({}, static_cast<uint8_t>(position.x), static_cast<uint8_t>(position.y),
                   static_cast<uint8_t>(MYSTERY_BOX), 0,
                   0);  // por conveniencia la caja se manda por mensaje como si fuera un proyectil
                        // para que la dibuje el render.
    }
    new_boxes.clear();
    for (const auto& [center_position, radius]: explosions) {
        explode(center_position, radius);
    }
    explosions.clear();
    for (auto& new_weapon: new_weapons) {
        new_weapon.get()->attach(obs);
        projectiles.push_back(std::move(new_weapon));
    }
    new_weapons.clear();
}

void Stage::draw(int object, int size, Coordinate init_position) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Coordinate current(init_position.x + i, init_position.y + j);
            set(current, object);
        }
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

    int size = PLAYER_SIZE;
    if (player.get_state() == PLAYING_DEAD) {
        size = 3;
        y += 3;
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
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

bool Stage::should_fall(Coordinate init_position, int size) {
    Coordinate bottom_pos(init_position.x, init_position.y + size);
    for (int i = 0; i < size; i++) {
        Coordinate aux(bottom_pos.x + i, bottom_pos.y);
        if (map.get(aux) != Config::get_instance()->mapsId["background"] && map.get(aux) != -1) {
            return false;
        }
    }
    return true;
}


std::set<int> Stage::things_projectile_hits(Coordinate position, int size) {
    std::set<int> things_it_hits;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Coordinate aux(position.x + j, position.y + i);
            things_it_hits.insert(map.get(aux));
        }
    }
    return things_it_hits;
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
            if (value == LIVE_BANANA) {  // una banana que fue activada
                std::shared_ptr<Projectile> banana_per_se =
                        find_projectile_in(aux, Config::get_instance()->bullet_size);
                if (banana_per_se) {

                    Coordinate banana_position = banana_per_se->get_position();
                    banana_per_se->updateNotPosition(banana_position.x, banana_position.y);
                    remove_projectile(banana_per_se);  // se elimina la banana per se
                }
                return LIVE_BANANA;
            }
            if (value != BACKGROUND && value != color) {
                return OCCUPIED;
            }
        }
    }
    return FREE;
}

std::shared_ptr<Projectile> Stage::find_projectile_in(Coordinate init_position, int size) {
    for (auto& projectile: projectiles) {
        Coordinate projectile_position = projectile->get_position();
        std::vector<Coordinate> positions_occupied_by_projectile;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                Coordinate c(projectile_position.x + j, projectile_position.y + i);
                positions_occupied_by_projectile.push_back(c);
            }
        }
        if (count(positions_occupied_by_projectile.begin(), positions_occupied_by_projectile.end(),
                  init_position) > 0) {
            return projectile;
        }
    }
    return nullptr;
}

// TODO: usar templates
std::shared_ptr<MysteryBox> Stage::find_box_in(Coordinate init_position, int size) {
    for (auto& box: boxes) {
        Coordinate box_position = box->get_position();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                Coordinate c(box_position.x + j, box_position.y + i);
                if (c == init_position) {
                    return box;
                }
                Coordinate d(box_position.x - j, box_position.y + i);
                if (d == init_position) {
                    return box;
                }
                Coordinate b(box_position.x - j, box_position.y - i);
                if (b == init_position) {
                    return box;
                }
                Coordinate a(box_position.x + j, box_position.y - i);
                if (a == init_position) {
                    return box;
                }
            }
        }
    }
    return nullptr;
}

void Stage::add_box(std::shared_ptr<MysteryBox> box) {
    Coordinate box_position = box->get_position();
    for (int i = 0; i < BOX_SIZE; i++) {
        for (int j = 0; j < BOX_SIZE; j++) {
            Coordinate c(box_position.x + i, box_position.y + j);
            map.set(c, MYSTERY_BOX);
        }
    }
    boxes.push_back(box);
}

void Stage::add_new_box(std::shared_ptr<MysteryBox> box) { new_boxes.push_back(box); }

void Stage::break_box(Coordinate position) {
    std::shared_ptr<MysteryBox> box = find_box_in(position, BOX_SIZE);
    if (box) {
        Coordinate box_position = box->get_position();
        std::shared_ptr<ProjectileDroppedWeapon> new_weapon = box->destroy_box();
        if (new_weapon) {
            new_weapons.push_back(new_weapon);
        }
        remove_box(box);
        obs.updateOldPos(box_position.x, box_position.y, MYSTERY_BOX);
        draw(BACKGROUND, BOX_SIZE, box_position);
    }
}

std::shared_ptr<Weapon> Stage::pick_weapon(Coordinate position) {
    for (auto& projectile: projectiles) {
        if (ProjectileDroppedWeapon* weaponProjectile =
                    dynamic_cast<ProjectileDroppedWeapon*>(projectile.get())) {
            if (weaponProjectile->get_position() == position) {
                std::shared_ptr new_weapon = (weaponProjectile->get_weapon());
                coordinates_to_delete.push_back(position);
                obs.updateOldPos(position.x, position.y, weaponProjectile->get_id());
                remove_projectile(projectile);
                return new_weapon;
            }
        }
        if (ProjectileThrownWeapon* weaponProjectile =
                    dynamic_cast<ProjectileThrownWeapon*>(projectile.get())) {
            if (weaponProjectile->get_position() == position) {
                if (weaponProjectile->get_id() == LIVE_BANANA) {  // banana activa no es levantable
                    return nullptr;
                }
                std::shared_ptr new_weapon = weaponProjectile->get_weapon();
                coordinates_to_delete.push_back(position);
                obs.updateOldPos(position.x, position.y, weaponProjectile->get_id());
                remove_projectile(projectile);
                return new_weapon;
            }
        }
    }
    return nullptr;
}

void Stage::set_explosion(Coordinate center_position, int radius) {
    explosions.push_back(std::tuple<Coordinate, int>(center_position, radius));
}
void Stage::explode(Coordinate center_position, int radius) {
    obs.update(std::vector<std::pair<uint8_t, uint8_t>>(),
               static_cast<uint8_t>(center_position.x),  // Manda mensaje de explosion
               static_cast<uint8_t>(center_position.y), static_cast<uint8_t>(EXPLOSION), 0,
               0);  // no tiene direccion asi que paso 0,0
    for (int i = 0; i < radius + 1; i++) {
        bool keep_going_horizontally = true;
        Coordinate next_position(center_position.x + i, center_position.y);
        explode_vertically(next_position, radius, 1, keep_going_horizontally);
        explode_vertically(next_position, radius, -1, keep_going_horizontally);
        if (!keep_going_horizontally) {
            break;
        }
    }
    for (int i = 0; i < radius + 1; i++) {
        bool keep_going_horizontally = true;
        Coordinate next_position(center_position.x - i, center_position.y);
        explode_vertically(next_position, radius, 1, keep_going_horizontally);
        explode_vertically(next_position, radius, -1, keep_going_horizontally);
        if (!keep_going_horizontally) {
            break;
        }
    }
}

void Stage::explode_vertically(Coordinate starting_position, int radius, int vertical_direction,
                               bool& keep_going_horizontally) {
    int wall = Config::get_instance()->mapsId["wall"];
    int floor = Config::get_instance()->mapsId["floor"];

    for (int j = 0; j < radius + 1; j++) {
        Coordinate next_tile(starting_position.x, starting_position.y + j * vertical_direction);
        // std::cout << "KABOOM en " << std::to_string(next_tile.x) << " , "
        //           << std::to_string(next_tile.y) << std::endl;
        int content_in_next_tile = map.get(next_tile);
        if (content_in_next_tile == wall || content_in_next_tile == floor) {
            if (j == 0) {
                keep_going_horizontally = false;
            }
            return;
        }
        if (content_in_next_tile > 0 && content_in_next_tile < 5) {  // si toca un jugador, matalo
            std::cout << "el contenido en la tile de arriba es "
                      << std::to_string(content_in_next_tile) << std::endl;
            kill(content_in_next_tile);
            return;
        }
    }
}

void Stage::set(const Coordinate& coor, const int value) {
    map.set(coor, value);
    if (value >= 1) {
        coordinates_to_delete.push_back(coor);
    }
}
int Stage::get(const Coordinate& coor) { return map.get(coor); }
