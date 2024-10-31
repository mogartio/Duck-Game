#ifndef WEAPON_H
#define WEAPON_H
#include "../map/stage.h"

class Weapon {
protected:
    int ammo;
    int reach;
    Stage& stage;
    Player& player;
    bool stopped_holding_trigger;

public:
    Weapon(Player& player, Stage& stage, int ammo, int reach):
            ammo(ammo), reach(reach), stage(stage), player(player), stopped_holding_trigger(true) {}
    virtual int get_ammo() { return ammo; }
    virtual ~Weapon() = default;
    virtual void shoot(int, bool) {}
    virtual Coordinate get_gun_position(int facing_direction);
    virtual void stop_shooting() { stopped_holding_trigger = true; };
};

class CowboyGun: public Weapon {
public:
    CowboyGun(Player&, Stage&);
    virtual void shoot(int, bool) override;
};

class Magnum: public Weapon {
public:
    Magnum(Player&, Stage&);
    virtual void shoot(int, bool) override;
};

// WIP
class Grenade: public Weapon {
public:
    Grenade(Player&, Stage&);
};

#endif
