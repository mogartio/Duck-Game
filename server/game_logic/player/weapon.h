#ifndef WEAPON_H
#define WEAPON_H
#include "../map/stage.h"

class Weapon {
protected:
    int ammo;
    int reach;
    Stage& stage;
    Player& player;

public:
    Weapon(Player& player, Stage& stage, int ammo, int reach):
            ammo(ammo), reach(reach), stage(stage), player(player) {}
    virtual void shoot(int) {}
    virtual int get_ammo() { return ammo; }
    virtual ~Weapon() = default;
};

class CowboyGun: public Weapon {
public:
    CowboyGun(Player&, Stage&);
    virtual void shoot(int) override;
};

class Magnum: public Weapon {
public:
    Magnum(Player&, Stage&);
    virtual void shoot(int) override;
};

// WIP
class Grenade: public Weapon {
public:
    Grenade(Player&, Stage&);
};

#endif
