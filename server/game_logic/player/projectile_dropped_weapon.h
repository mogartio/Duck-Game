#ifndef PROJECTILE_WEAPON_H
#define PROJECTILE_WEAPON_H

#include <cmath>

#include "projectile.h"
#include "weapon.h"
class ProjectileDroppedWeapon: public Projectile {
private:
    std::unique_ptr<Weapon> weapon;
    int current_angle_index;
    std::vector<double> deviation_angles{};

public:
    ProjectileDroppedWeapon(std::unique_ptr<Weapon> weapon, Coordinate initial_position, int speed,
                            int x_direction, int reach, double):
            Projectile(initial_position, x_direction, reach, speed, M_PI / 1.6, 9),
            weapon(std::move(weapon)),
            current_angle_index(0),
            deviation_angles({M_PI / 4, M_PI / 2, 9 * M_PI / 4}) {}
    void update() override {
        if (static_cast<size_t>(current_angle_index) == deviation_angles.size() - 1) {
            return;
        }
        current_angle_index++;
        deviation_angle =
                deviation_angles[current_angle_index];  // Se ve medio wonky cuando la tira frame 1
    }
};
#endif
