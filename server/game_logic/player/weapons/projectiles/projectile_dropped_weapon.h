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
private:
    std::shared_ptr<Weapon> weapon;
    std::vector<int> deviations;
    std::vector<int> deviations_direction;
    int deviations_index;

public:
    ProjectileThrownWeapon(std::shared_ptr<Weapon> weapon, Coordinate initial_position, int speed,
                           int x_direction, int reach, int id):
            Projectile(initial_position, x_direction, 1, reach, speed, id, false, false, false),
            weapon(std::move(weapon)) {
        for (int i = 0; i < speed; i++) {
            deviations.push_back(3);
            deviations_direction.push_back(UP_DIRECTION);
            deviations.push_back(5);
            if (i > speed / 2) {
                deviations_direction.push_back(UP_DIRECTION);
            } else {
                deviations_direction.push_back(DOWN_DIRECTION);
            }
        }
        deviations.push_back(3);
        deviations_direction.push_back(DOWN_DIRECTION);
    }

    virtual std::shared_ptr<Weapon> get_weapon() { return std::move(weapon); }
    void update() override {

        if (static_cast<size_t>(deviations_index) == deviations.size() - 1) {
            return;
        }
        deviations_index++;
        deviation = deviations[deviations_index];
        deviation_direction = deviations_direction[deviations_index];
    }

    void updateNotPosition(uint8_t pos_x, uint8_t pos_y) override {
        for (const Observer* obs: observers) {
            obs->updateOldPos(pos_x, pos_y, static_cast<uint8_t>(id));
        }
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

    void updateNotPosition(uint8_t pos_x, uint8_t pos_y) override {
        for (const Observer* obs: observers) {
            obs->updateOldPos(pos_x, pos_y, static_cast<uint8_t>(id));
        }
    }

    virtual std::shared_ptr<Weapon> get_weapon() {
        spawn->free();
        return std::move(weapon);
    }
};

class GrenadeProjectile: public ProjectileThrownWeapon {
    int counter;
    Stage& stage;

public:
    GrenadeProjectile(std::shared_ptr<Weapon> weapon, Coordinate initial_position, int speed,
                      int x_direction, int reach, int counter, Stage& stage, int id):
            ProjectileThrownWeapon(std::move(weapon), initial_position, speed, x_direction, reach,
                                   id),
            counter(counter),
            stage(stage) {}
    void update() override {
        ProjectileThrownWeapon::update();
        counter++;
        if (counter == Config::get_instance()->explosion_counter) {
            stage.set_explosion(position, Config::get_instance()->explosion_range);
        }
    }
};
#endif
