#include "weapon.h"
#include <memory>
#include "player.h"
#include "projectile.h"
                                                                        //ammo, reach
CowboyGun::CowboyGun(Player& player, Stage& stage): Weapon(player, stage, 6, 20){}

void CowboyGun::shoot(int x_direction){
    if (ammo == 0){
        return;
    }
    Coordinate gun_position(player.get_position().x, player.get_position().y + 1);
    stage.add_projectile(std::move(std::make_unique<CowboyBullet>(gun_position, x_direction, reach)));
    ammo --;
}

Magnum::Magnum(Player& player, Stage& stage): Weapon(player, stage, 6, 20){}

void Magnum::shoot(int x_direction){
    if (ammo == 0){
        return;
    }
    Coordinate gun_position(player.get_position().x, player.get_position().y + 1);
    stage.add_projectile(std::move(std::make_unique<MagnumBullet>(gun_position, x_direction, reach)));
    ammo --;
}


/*Grenade::Grenade(Player& player, Stage& stage): Weapon(player, stage, 1, 5){}

Grenade::shoot(int x_direction){
    if (ammo == 0){
        return;
    }

}*/
