#include "weapon.h"
#include <memory>
#include "player.h"
#include "projectile.h"
                                                                        //ammo, reach
CowboyGun::CowboyGun(Player& player, Stage& stage): Weapon(player, stage, 6, 20){}

void CowboyGun::shoot(int direction){
    if (ammo == 0){
        return;
    }
    Coordinate gun_position(player.get_position().x, player.get_position().y + 1);
    stage.add_projectile(std::move(std::make_unique<CowboyBullet>(gun_position, direction, reach)));
    ammo --;
}

/*Grenade::Grenade(Player& player, Stage& stage): Weapon(player, stage, 1, 5){}

Grenade::shoot(int direction){
    if (ammo == 0){
        return;
    }

}*/
