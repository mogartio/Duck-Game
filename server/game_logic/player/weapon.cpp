#include "weapon.h"
#include "player.h"

CowboyGun::CowboyGun(Player& player, Stage& stage): Weapon(player, stage, 6, 20){}

void CowboyGun::shoot(int direction){
    if (ammo == 0){
        return;
    }
    Coordinate gun_position(player.get_position().x, player.get_position().y + 1);
    stage.ray_trace(direction, reach, gun_position);
}
