#include "projectile.h"

#include "../../../config/config.h"
#include "../../../map/stage.h"
#define FLOOR 1
#define BACKGROUND 0

// devuelve true si fue eliminado
bool Projectile::ray_trace(Stage& stage) {
    if (speed == 0) {
        stage.draw(id, Config::get_instance()->bullet_size, position);
    }
    int direction_handler = x_direction;  // para usar el mismo loop sea la direccion 1 o -1
    Coordinate initial_position(position.x, position.y);
    int bullet_size = Config::get_instance()->bullet_size;
    // for (int j = 0; j < bullet_size; j++) {
    for (int i = 0; i < speed; i++) {
        bool despawned = false;
        // Probablemente sea pegarse un tiro en el pie usar trigonometria. no me pude resistir
        Coordinate bullet_position(
                round(initial_position.x + ((i)*sin(deviation_angle)) * direction_handler),
                round(initial_position.y + (i)*cos(deviation_angle)));
        std::set<int> things_it_hits = stage.things_projectile_hits(bullet_position, bullet_size);
        if (things_it_hits.find(-1) != things_it_hits.end()) {
            if (!trail.empty()) {
                trail.pop_back();
            }
            notify();
            return true;
        }
        check_if_player_killed(things_it_hits, despawned, stage);
        if (despawned) {
            return is_lethal;
        }
        check_if_stopped(things_it_hits, despawned, stage);
        if (despawned) {
            return despawns_on_contact;
        }
        if (i == speed - 1) {
            stage.draw(id, Config::get_instance()->bullet_size, bullet_position);
            if (!trail.empty()) {
                trail.pop_back();
            }  // esto es para que no aparezca la posicion actual en el
               // trail. its never been this serious
            notify();
            return false;
        }
        trail.push_back(std::pair<uint8_t, uint8_t>(bullet_position.x, bullet_position.y));
        position = bullet_position;
        // coordinates_to_delete.push_back(bullet_position);
        update();

        if (speed == 0) {
            notify();
        }

        //         int next_tile = stage.get(bullet_position, despawned, stage);
        //         if (next_tile == -1) {
        //             trail.pop_back();  // esto es para que no aparezca la posicion actual en el
        //             trail. notify(); return true;
        //         }
        //         if (next_tile == Config::get_instance()->mapsId["floor"] ||
        //             next_tile == Config::get_instance()->mapsId["wall"]) {
        //             speed = 0;
        //             stage.draw(id, Config::get_instance()->bullet_size, position);
        //             trail.pop_back();  // esto es para que no aparezca la posicion actual en el
        //             trail. notify(); return despawns_on_contact;
        //         }
        //         // si la siguiente tile es un pato
        //         if (next_tile == 1 || next_tile == 2) {
        //             if (is_lethal) {
        //                 stage.kill(next_tile);
        //                 return true;
        //             }
        //             if (!(initial_position == position)) {
        //                 trail.pop_back();  // esto es para que no aparezca la posicion actual en
        //                 el
        //                                    // trail.
        //                 notify();
        //             }
        //         }
        //         if ((next_tile == BACKGROUND || next_tile == id)) {
        //             if (i == speed - 1) {
        //                 stage.draw(id, Config::get_instance()->bullet_size, bullet_position);
        //                 trail.pop_back();  // esto es para que no aparezca la posicion actual en
        //                 el
        //                                    // trail. its never been this serious
        //                 notify();
        //                 return false;
        //             }
        //             trail.push_back(std::pair<uint8_t, uint8_t>(bullet_position.x,
        //             bullet_position.y)); position = bullet_position;
        //             // coordinates_to_delete.push_back(bullet_position);
        //             update();
        //         }
        //     }
    }
    return false;
}
void Projectile::check_if_player_killed(std::set<int>& hit, bool& despawned, Stage& stage) {
    for (int i = 1; i < 5; i++) {
        if (hit.find(i) != hit.end()) {
            if (is_lethal) {
                // AGREGAR CHEST Y HELMET
                // CHEQUEO SI REALMENTE RECIBE DAÑO
                stage.kill(i);
                despawned = true;
                return;
            }
            if (!trail.empty()) {
                trail.pop_back();
            }
            notify();
            return;
        }
    }
}
void Projectile::check_if_stopped(std::set<int>& hit, bool& despawned, Stage& stage) {
    if ((hit.find(Config::get_instance()->mapsId["wall"])) != hit.end() ||
        (hit.find(Config::get_instance()->mapsId["floor"])) != hit.end()) {
        speed = 0;
        stage.draw(id, Config::get_instance()->bullet_size, position);
        if (!trail.empty()) {
            trail.pop_back();
        }
        notify();
        despawned = true;
        return;
    }
}

void Projectile::notify() {

    for (const Observer* obs: observers) {
        // obs->update(static_cast<uint8_t>(position.x), static_cast<uint8_t>(position.y),
        //             static_cast<uint8_t>(id));
        obs->update(trail, static_cast<uint8_t>(position.x), static_cast<uint8_t>(position.y),
                    static_cast<uint8_t>(id));
    }
    trail.clear();
}
