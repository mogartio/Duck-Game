#include "projectile.h"

#include "../map/stage.h"
#define FLOOR 1
#define BACKGROUND 0

// devuelve true si fue eliminado
bool Projectile::ray_trace(Stage& stage) {
    int direction_handler = x_direction;  // para usar el mismo loop sea la direccion 1 o -1
    for (int i = 0; i < speed; i++) {

        // Probablemente sea pegarse un tiro en el pie usar trigonometria. no me pude resistir
        Coordinate bullet_position(
                round(position.x + ((i)*sin(deviation_angle)) * direction_handler),
                round(position.y + (i)*cos(deviation_angle)));

        int next_tile = stage.get(bullet_position);
        if (next_tile == -1 || next_tile == FLOOR) {
            return true;
        }
        if ((next_tile == BACKGROUND || next_tile == id || next_tile == 4) && i == speed - 1) {
            stage.set(bullet_position, id);
            move(bullet_position);
            // coordinates_to_delete.push_back(bullet_position);
            update();
        }
    }
    return false;
}
