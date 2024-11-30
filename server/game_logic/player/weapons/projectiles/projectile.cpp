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
    int bullet_size = Config::get_instance()->bullet_size;
    for (int i = 0; i < speed; i++) {
        if (distance_covered >= reach) {
            return true;
        }
        bool despawned = false;
        Coordinate bullet_position = get_bullet_position(i);
        std::set<int> things_it_hits = stage.things_projectile_hits(bullet_position, bullet_size);
        if (things_it_hits.find(-1) != things_it_hits.end()) {
            if (!trail.empty()) {
                trail.pop_back();
            }
            return true;
        }
        check_if_player_killed(things_it_hits, despawned, stage, bullet_position);
        if (despawned) {
            return is_lethal;
        }
        check_if_stopped(things_it_hits, despawned, stage, bullet_position);
        if (despawned) {
            if ((id == BULLET_PISTOL) || (id == BULLET_SHOTGUN) || (id == LASER)) {
                updateNotPosition(position.x, position.y);
            }
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
        updateNotPosition(position.x, position.y);
        position = bullet_position;
        distance_covered++;
        update();

        if (speed == 0) {
            notify();
        }
    }
    return false;
}

void Projectile::check_if_player_killed(std::set<int>& hit, bool& despawned, Stage& stage,
                                        Coordinate next_position) {
    for (int i = 1; i < 5; i++) {  // si le pego a un jugador con id entre 1 y 4
        if (hit.find(i) != hit.end()) {
            if (is_lethal) {

                // Chequea si el jugador tiene casco o armadura y recibe el daño
                if (stage.take_damage(i)) {
                    despawned = true;
                    return;
                }

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
    if (hit.find(MYSTERY_BOX) != hit.end()) {
        stage.break_box(next_position);
    }
}

void Projectile::check_if_stopped(std::set<int>& hit, bool& despawned, Stage& stage,
                                  Coordinate next_position) {
    if ((hit.find(Config::get_instance()->mapsId["wall"])) != hit.end() ||
        (hit.find(Config::get_instance()->mapsId["floor"])) != hit.end()) {
        if (next_position.x == position.x) {
            speed = 0;
        } else {
            moving_vertically = true;
        }
        moving_vertically = true;
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
    int going_up = -1;
    if (deviation == 1) {
        going_up = 1;
    }
    for (const Observer* obs: observers) {
        obs->update(trail, static_cast<uint8_t>(position.x), static_cast<uint8_t>(position.y),
                    static_cast<uint8_t>(id), x_direction, going_up);
    }
    trail.clear();
}

Coordinate Projectile::get_bullet_position(int offset) {
    Coordinate bullet_position(0, 0);  // se inicializa con basura,se va a settear despues
    if (moving_vertically) {
        bullet_position.y = position.y + offset * y_direction;  // x_direction es para donde miraba
                                                                // el pato. izq = -1, der=1
        if (distance_covered > 0 && deviation != 0 &&
            distance_covered % deviation == 0) {  // si hay desviacion y se cubrio la distancia
                                                  // necesaria para que se desvie, se desvia
            bullet_position.x = position.x + deviation_direction;
        } else {
            bullet_position.x = position.x;
        }

    } else {
        bullet_position.x = position.x + offset * x_direction;
        if (deviation != 0 && distance_covered % deviation == 0) {
            bullet_position.y = position.y + deviation_direction;
        } else {
            bullet_position.y = position.y;
        }
    }
    return bullet_position;
}

bool LaserBullet::ray_trace(Stage& stage) {
    int bullet_size = Config::get_instance()->bullet_size;
    for (int i = 0; i < speed; i++) {
        if (distance_covered >= reach) {
            return true;
        }
        bool despawned = false;

        // se checkea que tiene en la posicion horizontal adyacente
        Coordinate bullet_position(position.x + x_direction, position.y);
        std::set<int> things_it_hits = stage.things_projectile_hits(bullet_position, bullet_size);
        if (things_it_hits.find(-1) != things_it_hits.end()) {
            if (!trail.empty()) {
                trail.pop_back();
            }
            return true;
        }
        check_if_player_killed(things_it_hits, despawned, stage, bullet_position);
        if (despawned) {
            return is_lethal;
        }
        if ((things_it_hits.find(Config::get_instance()->mapsId["wall"])) != things_it_hits.end() ||
            (things_it_hits.find(Config::get_instance()->mapsId["floor"])) !=
                    things_it_hits.end()) {
            x_direction = x_direction * -1;
        }

        // se checkea que tiene en la posicion vertical adyacente
        bullet_position.y += y_direction;
        things_it_hits = stage.things_projectile_hits(bullet_position, bullet_size);
        if (things_it_hits.find(-1) != things_it_hits.end()) {
            if (!trail.empty()) {
                trail.pop_back();
            }
            return true;
        }
        check_if_player_killed(things_it_hits, despawned, stage, bullet_position);
        if (despawned) {
            return is_lethal;
        }
        if ((things_it_hits.find(Config::get_instance()->mapsId["wall"])) != things_it_hits.end() ||
            (things_it_hits.find(Config::get_instance()->mapsId["floor"])) !=
                    things_it_hits.end()) {
            y_direction = y_direction * -1;
        }
        if (i == speed - 1) {
            stage.draw(id, Config::get_instance()->bullet_size, bullet_position);
            if (!trail.empty()) {
                trail.pop_back();
            }
            notify();
            return false;
        }
        // trail.push_back(std::pair<uint8_t, uint8_t>(bullet_position.x, bullet_position.y));
        updateNotPosition(position.x, position.y);
        position = bullet_position;
        distance_covered++;
        update();
    }
    return false;
}

void Projectile::updateNotPosition(uint8_t pos_x, uint8_t pos_y) {
    for (const Observer* obs: observers) {
        obs->updateOldPos(pos_x, pos_y, static_cast<uint8_t>(id));
    }
}
