#ifndef ARMOR_H
#define ARMOR_H

#include "../weapon.h"

class Chest: public Weapon {
public:
    explicit Chest(Stage& stage);
    virtual void shoot(int, bool) override;
};

class Helmet: public Weapon {
public:
    explicit Helmet(Stage& stage);
    virtual void shoot(int, bool) override;
};


#endif