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
    Weapon(Player& player, Stage& stage,int ammo, int reach):
        player(player), stage(stage), ammo(ammo), reach(reach) {};
    virtual void shoot(int){};
    virtual int get_ammo() { return ammo; };
};

class CowboyGun : public Weapon{
public:
    CowboyGun(Player&, Stage&);
    virtual void shoot(int) override;
};

class Magnum : public Weapon {
public:
    Magnum(Player&, Stage&);
    virtual void shoot(int) override;
};

//WIP
class Grenade : public Weapon {
public:
    Grenade(Player&, Stage&);
};

#endif
