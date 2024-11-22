#ifndef PISTOLS_H
#define PISTOLS_H

#include "weapon.h"
class CowboyGun: public Weapon {
public:
    explicit CowboyGun(Stage&);
    virtual void shoot(int, bool) override;
};

class Magnum: public Weapon {
public:
    explicit Magnum(Stage&);
    virtual void shoot(int, bool) override;
};

class Chest: public Weapon {
public:
    explicit Chest(Stage&);
    // Reimplementacion de shoot para que reciba daño
    virtual void shoot(int, bool) override;
};

class Helmet: public Weapon {
public:
    explicit Helmet(Stage&);
    // Reimplementacion de shoot para que reciba daño
    virtual void shoot(int, bool) override;
};

#endif
