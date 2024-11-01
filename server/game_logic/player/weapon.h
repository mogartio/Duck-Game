#ifndef WEAPON_H
#define WEAPON_H
#include "../map/stage.h"

class Weapon {
protected:
    int ammo;
    int reach;
    Stage& stage;
    Player* player;
    bool stopped_holding_trigger;
    bool throw_started;
    int throw_reach;

public:
    Weapon(Stage& stage, int ammo, int reach):
            ammo(ammo),
            reach(reach),
            stage(stage),
            player(nullptr),
            stopped_holding_trigger(true) {}
    virtual int get_ammo() { return ammo; }
    virtual ~Weapon() = default;
    virtual void shoot(int, bool) {}
    virtual Coordinate get_gun_position(int facing_direction);
    virtual void stop_shooting() { stopped_holding_trigger = true; }
    virtual void start_throw();
    virtual void finish_throw(int, bool, std::unique_ptr<Weapon>);
    virtual void set_player(Player* new_player) { player = new_player; }
    virtual void deset_player() { player = nullptr; }
};

class CowboyGun: public Weapon {
public:
    CowboyGun(Stage&);
    virtual void shoot(int, bool) override;
};

class Magnum: public Weapon {
public:
    Magnum(Stage&);
    virtual void shoot(int, bool) override;
};

class Grenade: public Weapon {
public:
    Grenade(Stage&);
};

#endif
