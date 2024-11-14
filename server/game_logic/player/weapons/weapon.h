#ifndef WEAPON_H
#define WEAPON_H
#include <memory>

#include "../../map/stage.h"

class Weapon {
protected:
    int ammo;
    int reach;
    Stage& stage;
    Player* player;
    bool stopped_holding_trigger;
    bool throw_started;
    int throw_reach;
    int id;

public:
    Weapon(Stage& stage, int ammo, int reach, int id):
            ammo(ammo),
            reach(reach),
            stage(stage),
            player(nullptr),
            stopped_holding_trigger(false),
            throw_started(false),
            throw_reach(0),
            id(id) {}
    virtual int get_ammo() { return ammo; }
    virtual ~Weapon() = default;
    virtual void shoot(int, bool) {}
    virtual Coordinate get_gun_position(int facing_direction);
    virtual void stop_shooting() { stopped_holding_trigger = true; }
    virtual void start_throw();
    virtual void finish_throw(int, bool, std::unique_ptr<Weapon>);
    virtual void set_player(Player* new_player) { player = new_player; }
    virtual void deset_player() { player = nullptr; }
    virtual void update() {}
    virtual uint8_t get_id() { return id; }
};

class Unarmed: public Weapon {
public:
    explicit Unarmed(Stage&);
    virtual void shoot(int, bool) override;
    virtual Coordinate get_gun_position(int) override;
};

#endif
