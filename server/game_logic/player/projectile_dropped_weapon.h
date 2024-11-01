#ifndef PROJECTILE_WEAPON_H
#define PROJECTILE_WEAPON_H

#include "projectile.h"
#include "weapon.h"
class ProjectileDroppedWeapon: public Projectile {
    std::unique_ptr<Weapon>& weapon;
    ProjectileDroppedWeapon(std::unique_ptr<Weapon>& weapon, Coordinate initial_position, int speed,
                            int x_direction, int reach, int deviation_angle):
            weapon(weapon),
            Projectile(initial_position, x_direction, reach, speed, deviation_angle) {}
};
#endif
