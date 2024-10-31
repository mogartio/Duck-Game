#include "weapon.h"

#include <memory>

#include "player.h"
#include "projectile.h"
// ammo, reach

// aim_direction en el eje x
Coordinate Weapon::get_gun_position(int facing_direction) {
    Coordinate player_position = player.get_position();
    if (facing_direction == 1) {
        return Coordinate(player_position.x + 2, player_position.y + 1);
    }
    return Coordinate(player_position.x, player_position.y + 1);
}
CowboyGun::CowboyGun(Player& player, Stage& stage): Weapon(player, stage, 6, 20) {}

void CowboyGun::shoot(int x_direction, bool is_aiming_up) {
    if (ammo == 0) {
        return;
    }
    Coordinate gun_position = get_gun_position(x_direction);
    stage.add_projectile(std::move(
            std::make_unique<CowboyBullet>(gun_position, x_direction, is_aiming_up, reach)));
    ammo--;
}

Magnum::Magnum(Player& player, Stage& stage): Weapon(player, stage, 6, 20) {}

void Magnum::shoot(int x_direction, bool is_aiming_up) {
    if (ammo == 0) {
        return;
    }
    Coordinate gun_position = get_gun_position(x_direction);
    stage.add_projectile(std::move(
            std::make_unique<MagnumBullet>(gun_position, x_direction, is_aiming_up, reach)));
    ammo--;
}


/*Grenade::Grenade(Player& player, Stage& stage): Weapon(player, stage, 1, 5){}

Grenade::shoot(int x_direction){
    if (ammo == 0){
        return;
    }

}*/
