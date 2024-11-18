#ifndef PROJECTILE_WEAPON_H
#define PROJECTILE_WEAPON_H

#include <cmath>
#include <memory>
#include <utility>
#include <vector>

#include "../../../config/config.h"
#include "../../../map/spawn_point.h"
#include "../weapon.h"

#include "projectile.h"

// Un monton de codigo repetido aca
class ProjectileThrownWeapon: public Projectile {
private:
    std::shared_ptr<Weapon> weapon;
    int current_angle_index;
    std::vector<double> deviation_angles{};

public:
    ProjectileThrownWeapon(std::shared_ptr<Weapon> weapon, Coordinate initial_position, int speed,
                           int x_direction, int reach, int id):
            Projectile(initial_position, x_direction, reach, speed, M_PI / 1.6, id, false, false),
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
    virtual std::shared_ptr<Weapon> get_weapon() { return std::move(weapon); }

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
            Projectile(initial_position, 1, reach, speed, 0, id, false, false),
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
        //        spawn->free();
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
