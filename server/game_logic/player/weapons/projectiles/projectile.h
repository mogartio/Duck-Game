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
    virtual bool ray_trace(Stage& stage);
    virtual void notify() override;
    virtual void check_if_stopped(std::set<int>& hit, bool& despawned, Stage& stage);
    virtual void check_if_player_killed(std::set<int>& hit, bool& despawned, Stage& stage);
};


class CowboyBullet: public Projectile {
public:
    CowboyBullet(Coordinate& initial_position, int x_direction, int y_direction, bool is_aiming_up,
                 int reach):
            Projectile(initial_position, x_direction, y_direction, reach, 6, BULLET_PISTOL, true,
                       true, is_aiming_up) {
        deviation = 20;
    }
};

class MagnumBullet: public Projectile {
public:
    MagnumBullet(Coordinate& initial_position, int x_direction, int y_direction, bool is_aiming_up,
                 int reach):
            Projectile(initial_position, x_direction, y_direction, reach, 6, BULLET_PISTOL, true,
                       true, is_aiming_up) {
        deviation = 12;
        deviation_direction = -1;
    }
};
#endif
