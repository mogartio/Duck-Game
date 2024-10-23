#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "../../../common/coordinate.h"
#include "../map/stage.h"

class Projectile{
protected:
    Stage& stage;
    int speed;
    int direction;
    int deviation_angle;
    Coordinate position;
    int reach;
    int distance_covered;
public:
    Projectile(Stage& stage, Coordinate& initial_position, int direction, int reach, int speed, int deviation_angle): 
        position(initial_position),reach(reach), speed(speed), deviation_angle(deviation_angle), 
        distance_covered(0), direction(direction), stage(stage){}
    virtual void move(){};
    virtual void despawn(){};
};

class CowboyBullet : Projectile {
    CowboyBullet(Stage& stage, Coordinate& initial_position, int& direction, int& reach): 
        Projectile(stage, initial_position, direction, reach, 10, 0){}
    void move() override {
        stage.ray_trace();
    } 
};

#endif
