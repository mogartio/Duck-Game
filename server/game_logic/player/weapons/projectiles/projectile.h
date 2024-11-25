#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <cmath>
#include <cstdlib>
#include <memory>
#include <utility>

#include "../../../../../common/coordinate.h"
#include "../../../../../common/messages/generic_msg.h"
#include "../../subject.h"
class Weapon;
class Stage;
using namespace ProjectilesId;


class Projectile: public ProjectileSubject {
protected:
    int speed;
    int x_direction;
    double deviation_angle;
    Coordinate position;
    int reach;
    int distance_covered;
    int id;
    bool despawns_on_contact;
    bool is_lethal;
    std::vector<std::pair<uint8_t, uint8_t>> trail;

public:
    Projectile(Coordinate& initial_position, int x_direction, int reach, int speed,
               double deviation_angle, int id, bool despawns_on_contact, bool is_lethal):
            speed(speed),
            x_direction(x_direction),
            deviation_angle(deviation_angle),
            position(initial_position),
            reach(reach),
            distance_covered(0),
            id(id),
            despawns_on_contact(despawns_on_contact),
            is_lethal(is_lethal),
            trail() {}
    virtual void move(Coordinate new_position) { position = new_position; }
    virtual Coordinate get_position() { return position; }
    virtual ~Projectile() = default;
    virtual int get_id() { return id; }
    virtual void update() {}
    virtual void updateNotPosition(uint8_t, uint8_t) {}
    virtual bool ray_trace(Stage& stage);
    virtual void notify() override;
    virtual void check_if_stopped(std::set<int>& hit, bool& despawned, Stage& stage);
    virtual void check_if_player_killed(std::set<int>& hit, bool& despawned, Stage& stage);
};


class CowboyBullet: public Projectile {
public:
    CowboyBullet(Coordinate& initial_position, int x_direction, bool is_aiming_up, int reach):
            Projectile(initial_position, x_direction, reach, 6, 0, BULLET_PISTOL, true, true) {
        deviation_angle = M_PI / 2 + (M_PI / 2 * is_aiming_up);
    }

    void updateNotPosition(uint8_t pos_x, uint8_t pos_y) override {
        for (const Observer* obs: observers) {
            obs->updateOldPos(pos_x, pos_y, static_cast<uint8_t>(id));
        }
    }
};

class MagnumBullet: public Projectile {
public:
    MagnumBullet(Coordinate& initial_position, int x_direction, bool is_aiming_up, int reach):
            Projectile(initial_position, x_direction, reach, 6, 0, BULLET_PISTOL, true, true) {

        deviation_angle = M_PI / 1.92 + (M_PI / 2 * is_aiming_up);
    }
    void updateNotPosition(uint8_t pos_x, uint8_t pos_y) override {
        for (const Observer* obs: observers) {
            obs->updateOldPos(pos_x, pos_y, static_cast<uint8_t>(id));
        }
    }
};
#endif
