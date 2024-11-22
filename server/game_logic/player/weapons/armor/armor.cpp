#include "armor.h"
#include "../../player.h"

Chest::Chest(Stage& stage): Weapon(stage, 1, 0, CHEST) {}

void Chest::shoot(int, bool) {
    // Recibe daño
    ammo--;
    if (ammo == 0) {
        player->pick_chest(std::make_unique<Unarmed>(stage));
    }
}


Helmet::Helmet(Stage& stage): Weapon(stage, 1, 0, HELMET) {}

void Helmet::shoot(int, bool) {
    // Recibe daño
    ammo--;
    if (ammo == 0) {
        player->pick_helmet(std::make_unique<Unarmed>(stage));
    }
}

