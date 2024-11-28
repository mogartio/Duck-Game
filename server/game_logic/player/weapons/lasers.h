#ifndef LASERS_H
#define LASERS_H
#include <memory>
#include <utility>

#include "weapon.h"

class PewLaser: public Weapon {
public:
    explicit PewLaser(Stage&);
    virtual void shoot(int, bool) override;
    virtual void stop_shooting() override;
};
class LaserRifle: public Weapon {
public:
    explicit LaserRifle(Stage&);
    virtual void shoot(int, bool) override;
};
#endif
