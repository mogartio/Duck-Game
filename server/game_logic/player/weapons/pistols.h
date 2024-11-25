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

class DuelPistol: public Weapon {
public:
    explicit DuelPistol(Stage&);
    virtual void shoot(int, bool) override;
};
#endif
