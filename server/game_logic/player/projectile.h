#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "../../../common/coordinate.h"

class Projectile{
protected:
    int speed;
    int direction;
    int deviation_angle;
    Coordinate position;
    int reach;
    int distance_covered;
public:
    Projectile(Coordinate& initial_position, int direction, int reach, int speed, int deviation_angle): 
        position(initial_position),reach(reach), speed(speed), deviation_angle(deviation_angle), 
        distance_covered(0), direction(direction){}
    virtual void move() = 0;
    virtual void despawn() = 0;
    virtual int get_direction() { return direction; }
    virtual int get_speed() { return speed; }
    virtual Coordinate get_position() { return position; }
};

class CowboyBullet :public Projectile {
public:
    CowboyBullet(Coordinate& initial_position, int direction, int reach): 
        Projectile(initial_position, direction, reach, 10, 0){}

    void move() override {
        position.x += speed * direction;
    } 

    void despawn() override {}
};

#endif
