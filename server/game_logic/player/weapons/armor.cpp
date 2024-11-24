#include "armor.h"
#include "../player.h"

#include <cmath>
#include <memory>
#include <utility>

Chest::Chest(Stage& stage): Weapon(stage, 1, 20, CHEST) {}

void Chest::shoot(int damage, bool) {
    // Recibe daño
    ammo -= damage;
    if (ammo == 0) {
        // Caso de que se quede sin daño posible, desaparece la armadura
        player->pick_chest(std::make_unique<Unarmed>(stage));
    }
}


Helmet::Helmet(Stage& stage): Weapon(stage, 1, 20, HELMET) {}

void Helmet::shoot(int damage, bool) {
    // Recibe daño
    ammo -= damage;
    if (ammo == 0) {
        // Caso de que se quede sin daño posible, desaparece el casco
        player->pick_helmet(std::make_unique<Unarmed>(stage));
    }
}



