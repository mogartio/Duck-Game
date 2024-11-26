#ifndef THROWABLES_H
#define THROWABLES_H

#include "weapon.h"
class Grenade: public Weapon {
protected:
    int counter = 0;
    bool turned_on;
    bool dead;

public:
    explicit Grenade(Stage&);
    virtual void shoot(int, bool) override;
    // virtual void finish_throw(int, bool, std::shared_ptr<Weapon>) override;
    virtual void update() override;
    void update(Coordinate) override;
    bool exploded() override;
};
#endif
