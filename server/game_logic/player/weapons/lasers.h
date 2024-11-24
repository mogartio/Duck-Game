#ifndef LASERS_H
#define LASERS_H

#include "weapon.h"

class PewLaser: public Weapon {
public:
    explicit PewLaser(Stage&);
    virtual void shoot(int, bool) override;
    virtual void stop_shooting() override;
};
#endif
