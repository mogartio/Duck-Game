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
            is_lethal(is_lethal) {}
    virtual void move(Coordinate new_position) { position = new_position; }
    virtual int get_x_direction() { return x_direction; }
    virtual int get_speed() { return speed; }
    virtual double get_deviation_angle() { return deviation_angle; }
    virtual Coordinate get_position() { return position; }
    virtual ~Projectile() = default;
    virtual int get_id() { return id; }
    virtual void update() {}
    virtual bool ray_trace(Stage& stage);
    virtual void notify() override;
};


class CowboyBullet: public Projectile {
public:
    CowboyBullet(Coordinate& initial_position, int x_direction, bool is_aiming_up, int reach):
            Projectile(initial_position, x_direction, reach, 15, 0, BULLET_PISTOL, true, true) {
        deviation_angle = M_PI / 2 + (M_PI / 2 * is_aiming_up);
    }
};

class MagnumBullet: public Projectile {
public:
    MagnumBullet(Coordinate& initial_position, int x_direction, bool is_aiming_up, int reach):
            Projectile(initial_position, x_direction, reach, 15, 0, BULLET_PISTOL, true, true) {

        deviation_angle = M_PI / 1.92 + (M_PI / 2 * is_aiming_up);
    }
};
#endif
