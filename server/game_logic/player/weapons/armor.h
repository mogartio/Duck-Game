#ifndef ARMOR_H
#define ARMOR_H

#include "weapon.h"

class Chest: public Weapon {
public:
    explicit Chest(Stage&);
    // Reimplementacion de shoot para que reciba daño
    virtual void shoot(int, bool) override;
};

class Helmet: public Weapon {
public:
    explicit Helmet(Stage&, int id);
    // Reimplementacion de shoot para que reciba daño
    virtual void shoot(int, bool) override;
};


#endif
