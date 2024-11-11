#include "projectile.h"

#include "../../../config/config.h"
#include "../../../map/stage.h"
#define FLOOR 1
#define BACKGROUND 0

// devuelve true si fue eliminado
bool Projectile::ray_trace(Stage& stage) {
    if (speed == 0) {
        stage.set(position, id);
    }
    int direction_handler = x_direction;  // para usar el mismo loop sea la direccion 1 o -1
    Coordinate initial_position(position.x, position.y);
    for (int i = 0; i < speed; i++) {

        // Probablemente sea pegarse un tiro en el pie usar trigonometria. no me pude resistir
        Coordinate bullet_position(
                round(initial_position.x + ((i)*sin(deviation_angle)) * direction_handler),
                round(initial_position.y + (i)*cos(deviation_angle)));

        int next_tile = stage.get(bullet_position);
        if (next_tile == -1) {
            return true;
        }
        if (next_tile == Config::get_instance()->mapsId["floor"] ||
            next_tile == Config::get_instance()->mapsId["wall"]) {
            speed = 0;
            stage.set(position, id);
            return despawns_on_contact;
        }
        if (next_tile == 1 || next_tile == 2) {
            if (is_lethal) {
                stage.kill(next_tile);
            }
            return is_lethal;
        }
        if ((next_tile == BACKGROUND || next_tile == id || next_tile == 4)) {
            if (i == speed - 1) {
                stage.set(bullet_position, id);
                return false;
            }
            position = bullet_position;
            // coordinates_to_delete.push_back(bullet_position);
            notify();
            update();
        }
        trail.push_back(std::pair<uint16_t, uint16_t>(bullet_position.x, bullet_position.y));
    }
    notify();
    return false;
}

void Projectile::notify() {

    for (Observer* obs: observers) {
        obs->update(trail, std::pair<uint16_t, uint16_t>(position.x, position.y));
    }
    trail.clear();
}
