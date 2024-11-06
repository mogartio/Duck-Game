#ifndef THROWABLES_H
#define THROWABLES_H

#include "weapon.h"
class Grenade: public Weapon {
protected:
    int counter = 0;
    bool turned_on;

public:
    explicit Grenade(Stage&);
    virtual void shoot(int, bool) override;
    virtual void finish_throw(int, bool, std::unique_ptr<Weapon>) override;
    virtual void update() override;
};
#endif
