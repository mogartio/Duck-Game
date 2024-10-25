#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <cmath>
#include <cstdlib>
#include "../../../common/coordinate.h"

class Projectile{
protected:
    int speed;
    int x_direction;
    double deviation_angle;
    Coordinate position;
    int reach;
    int distance_covered;
public:
    Projectile(Coordinate& initial_position, int x_direction, int reach, int speed, int deviation_angle): 
        position(initial_position),reach(reach), speed(speed), deviation_angle(deviation_angle), 
        distance_covered(0), x_direction(x_direction){}
    virtual void move(Coordinate new_position){ position = new_position;} 
    virtual void despawn() = 0;
    virtual int get_x_direction() { return x_direction; }
    virtual int get_speed() { return speed; }
    virtual double get_deviation_angle() { return deviation_angle; }
    virtual Coordinate get_position() { return position; }
};

class CowboyBullet :public Projectile {
public:
    CowboyBullet(Coordinate& initial_position, int x_direction, int reach): 
        Projectile(initial_position, x_direction, reach, 15, 0){
        deviation_angle = M_PI / 2;
    }
    void despawn() override {}
};

class MagnumBullet :public Projectile {
public:
    MagnumBullet(Coordinate& initial_position, int x_direction, int reach): 
        Projectile(initial_position, x_direction, reach, 15, 0){
        deviation_angle = M_PI / 1.92;
    }
    void despawn() override {}
};
#endif
