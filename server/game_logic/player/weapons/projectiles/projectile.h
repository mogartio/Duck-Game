#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <cmath>
#include <cstdlib>
#include <memory>
#include <utility>

#include "../../../../../common/coordinate.h"
#include "../../../../../common/messages/generic_msg.h"
#include "../../../config/weapon_config.h"
#include "../../subject.h"
class Weapon;
class Stage;
using namespace ProjectilesId;


class Projectile: public ProjectileSubject {
protected:
    int speed;
    int x_direction;
    int y_direction;
    int deviation;            // cada cuantas tiles horizontales se desvia verticalmente
    int deviation_direction;  // si se desvia para abajo o para arriba. puede ser 1 o -1
    Coordinate position;
    int reach;
    int distance_covered;
    int id;
    bool despawns_on_contact;
    bool is_lethal;
    std::vector<std::pair<uint8_t, uint8_t>> trail;
    bool moving_vertically;

    Coordinate get_bullet_position(int offset);

public:
    Projectile(Coordinate& initial_position, int x_direction, int y_direction, int reach, int speed,
               int id, bool despawns_on_contact, bool is_lethal, bool moving_vertically):
            speed(speed),
            x_direction(x_direction),
            y_direction(y_direction),
            position(initial_position),
            reach(reach),
            distance_covered(0),
            id(id),
            despawns_on_contact(despawns_on_contact),
            is_lethal(is_lethal),
            trail(),
            moving_vertically(moving_vertically) {}
    virtual void move(Coordinate new_position) { position = new_position; }
    virtual Coordinate get_position() { return position; }
    virtual ~Projectile() = default;
    virtual int get_id() { return id; }
    virtual void update() {}
    virtual void updateNotPosition(uint8_t, uint8_t);
    virtual bool ray_trace(Stage& stage);
    virtual void notify() override;
    virtual void check_if_stopped(std::set<int>& hit, bool& despawned, Stage& stage);
    virtual void check_if_player_killed(std::set<int>& hit, bool& despawned, Stage& stage);
};


class CowboyBullet: public Projectile {
public:
    CowboyBullet(Coordinate& initial_position, int x_direction, int y_direction, bool is_aiming_up,
                 int reach):
            Projectile(initial_position, x_direction, y_direction, reach,
                       WeaponConfig::get_instance()->weapons["cowboy"]["speed"], BULLET_PISTOL,
                       true, true, is_aiming_up) {
        deviation = WeaponConfig::get_instance()->weapons["cowboy"]["deviation"];
    }

    void updateNotPosition(uint8_t pos_x, uint8_t pos_y) override {
        for (const Observer* obs: observers) {
            obs->updateOldPos(pos_x, pos_y, static_cast<uint8_t>(id));
        }
    }
};

class MagnumBullet: public Projectile {
public:
    MagnumBullet(Coordinate& initial_position, int x_direction, int y_direction, bool is_aiming_up,
                 int reach):
            Projectile(initial_position, x_direction, y_direction, reach,
                       WeaponConfig::get_instance()->weapons["magnum"]["speed"], BULLET_PISTOL,
                       true, true, is_aiming_up) {
        deviation = WeaponConfig::get_instance()->weapons["magnum"]["deviation"];
        deviation_direction = -1;
    }
};
class DuelBullet: public Projectile {
public:
    DuelBullet(Coordinate& initial_position, int x_direction, int y_direction, bool is_aiming_up,
               int reach):
            Projectile(initial_position, x_direction, y_direction, reach,
                       WeaponConfig::get_instance()->weapons["duel"]["speed"], BULLET_PISTOL, true,
                       true, is_aiming_up) {
        deviation = WeaponConfig::get_instance()->weapons["duel"]["deviation"];
    }
};

class Ak47Bullet: public Projectile {
public:
    Ak47Bullet(Coordinate& initial_position, int x_direction, int y_direction, bool is_aiming_up,
               int reach, int bullet_number):
            Projectile(initial_position, x_direction, y_direction, reach,
                       WeaponConfig::get_instance()->weapons["ak47"]["speed"], BULLET_PISTOL, true,
                       true, is_aiming_up) {

        int init_deviation = WeaponConfig::get_instance()->weapons["ak47"]["deviation"];
        deviation = std::max(3, init_deviation - 2 * bullet_number);  // la desviacion a lo sumo 3
        deviation_direction = 1 - 2 * (bullet_number % 2);  // va intercalando arriba o abajo
    }
};

class ShotgunBullet: public Projectile {
public:
    ShotgunBullet(Coordinate& initial_position, int x_direction, int y_direction, bool is_aiming_up,
                  int reach, int new_deviation, int new_deviation_direction):
            Projectile(initial_position, x_direction, y_direction, reach,
                       WeaponConfig::get_instance()->weapons["shotgun"]["speed"], BULLET_SHOTGUN,
                       true, true, is_aiming_up) {
        deviation = new_deviation;
        deviation_direction = new_deviation_direction;
    }
};

class SniperBullet: public Projectile {
public:
    SniperBullet(Coordinate& initial_position, int x_direction, int y_direction, bool is_aiming_up,
                 int reach):
            Projectile(initial_position, x_direction, y_direction, reach,
                       WeaponConfig::get_instance()->weapons["sniper"]["speed"], BULLET_PISTOL,
                       true, true, is_aiming_up) {}
};

class PewLaserBullet: public Projectile {
public:
    PewLaserBullet(Coordinate& initial_position, int x_direction, int y_direction,
                   bool is_aiming_up, int reach, int new_deviation, int new_deviation_direction):
            Projectile(initial_position, x_direction, y_direction, reach,
                       WeaponConfig::get_instance()->weapons["pewpew"]["speed"], LASER, true, true,
                       is_aiming_up) {
        deviation = new_deviation;
        deviation_direction = new_deviation_direction;
    }
};

class LaserBullet: public Projectile {
public:
    LaserBullet(Coordinate& initial_position, int x_direction, int y_direction, bool is_aiming_up,
                int reach):
            Projectile(initial_position, x_direction, y_direction, reach,
                       WeaponConfig::get_instance()->weapons["laser_rifle"]["speed"], LASER, true,
                       true, is_aiming_up) {}
    bool ray_trace(Stage& stage) override;
};
#endif
