#ifndef PROJECTILE_WEAPON_H
#define PROJECTILE_WEAPON_H

#include <cmath>
#include <memory>
#include <utility>
#include <vector>

#include "../../../config/config.h"
#include "../../../map/spawn_point.h"
#include "../weapon.h"
#define UP_DIRECTION -1
#define DOWN_DIRECTION 1

#include "projectile.h"

// Un monton de codigo repetido aca
class ProjectileThrownWeapon: public Projectile {
protected:
    std::vector<int> deviations;
    std::vector<int> deviations_direction;
    int deviations_index;
    std::shared_ptr<Weapon> weapon;

public:
    ProjectileThrownWeapon(std::shared_ptr<Weapon> weapon, Coordinate initial_position, int speed,
                           int x_direction, int reach, int id):
            Projectile(initial_position, x_direction, 1, reach, speed, id, false, false, false),
            deviations_index(-1),
            weapon(std::move(weapon)) {  // Initialize deviations_index
        for (int i = 0; i < speed; i++) {
            deviations.push_back(3);
            deviations_direction.push_back(UP_DIRECTION);
            deviations.push_back(5);
            if (i < speed / 2) {
                deviations_direction.push_back(UP_DIRECTION);
            } else {
                deviations_direction.push_back(DOWN_DIRECTION);
            }
        }
        deviations.push_back(3);
        deviations_direction.push_back(DOWN_DIRECTION);
    }

    ProjectileThrownWeapon(std::shared_ptr<Grenade> weapon, Coordinate initial_position, int speed,
                           int x_direction, int reach, int id):
            Projectile(initial_position, x_direction, 1, reach, speed, id, false, false, false),
            deviations_index(-1),
            weapon(std::move(weapon)) {  // Initialize deviations_index
        for (int i = 0; i < speed; i++) {
            deviations.push_back(3);
            deviations_direction.push_back(UP_DIRECTION);
            deviations.push_back(5);
            if (i < speed / 2) {
                deviations_direction.push_back(UP_DIRECTION);
            } else {
                deviations_direction.push_back(DOWN_DIRECTION);
            }
        }
        deviations.push_back(3);
        deviations_direction.push_back(DOWN_DIRECTION);
    }

    virtual std::shared_ptr<Weapon> get_weapon() { return std::move(weapon); }

    bool update() override {

        if (weapon->get_id() == GRENADE) {
            if (weapon->is_dead()) {
                updateNotPosition(position.x, position.y);
                return true;
            }
            weapon->update(position);
        }
        if (static_cast<size_t>(deviations_index) == deviations.size() - 1) {
            return false;
        }
        deviations_index++;
        deviation = deviations[deviations_index];
        deviation_direction = deviations_direction[deviations_index];
        return false;
    }


    void notify() override {
        for (const Observer* obs: observers) {
            obs->update(std::vector<std::pair<uint8_t, uint8_t>>(),  // se envia el trail vacio
                        static_cast<uint8_t>(position.x), static_cast<uint8_t>(position.y),
                        static_cast<uint8_t>(id));
        }
    }
};

class ProjectileDroppedWeapon: public Projectile {
private:
    std::shared_ptr<Weapon> weapon;
    WeaponSpawnPoint* spawn;

public:
    ProjectileDroppedWeapon(std::shared_ptr<Weapon> weapon, Coordinate initial_position, int speed,
                            int reach, int id, WeaponSpawnPoint* spawn):
            Projectile(initial_position, 1, 1, reach, speed, id, false, false, true),
            weapon(std::move(weapon)),
            spawn(spawn) {}

    void notify() override {
        for (const Observer* obs: observers) {
            obs->update(std::vector<std::pair<uint8_t, uint8_t>>(),  // se envia el trail vacio
                        static_cast<uint8_t>(position.x), static_cast<uint8_t>(position.y),
                        static_cast<uint8_t>(id));
        }
    }
    virtual std::shared_ptr<Weapon> get_weapon() {
        spawn->free();
        return std::move(weapon);
    }
};

#endif
