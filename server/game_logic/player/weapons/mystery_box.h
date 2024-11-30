#ifndef MYSTERY_BOX_H
#define MYSTERY_BOX_H

#include <sys/types.h>

#include "../../../../common/coordinate.h"
#include "../../../game_logic/config/config.h"
#include "../../../game_logic/map/spawn_point.h"
#include "../../map/stage.h"
#include "../../player/weapons/armor.h"
#include "../../player/weapons/heavy_weapons.h"
#include "../../player/weapons/lasers.h"
#include "../../player/weapons/pistols.h"
#include "../../player/weapons/projectiles/projectile_dropped_weapon.h"
#include "../../player/weapons/throwables.h"
/*
 * MysteryBox class
 *
 * This class is used to represent a mystery box in the game.
 * When its state changes to 'broken' it will drop a random item from the list of possible items.
 * It is a tile object that can be interacted with by the player.
 */

class MysteryBox {
private:
    bool broken;
    uint item;
    Stage& stage;
    Coordinate pos;


public:
    MysteryBox(Stage& stage, Coordinate position);

    /*
     * This method is called when the mystery box is destroyed.
     * It will set the box as broken and drop a random item from the list of possible items.
     * If the item is an explosion, it will set an explosion in the position.
     * If the item is a weapon, it will spawn the weapon.
     */
    void destroy_box();

    Coordinate get_position() { return pos; }

    /*
     * This method is called when the mystery box drops a weapon.
     * It will spawn the weapon in the position of the mystery box.
     */
    void drop_weapon();

    /*
     * This method is called when the mystery box drops an explosion.
     * It will set an explosion in the position of the mystery box.
     */
    void explode();

    /*
     * This method is called to check if the mystery box is broken.
     * Returns true if the mystery box is broken, false otherwise.
     */
    bool is_broken();

    /*
     * This method is called to get the item that the mystery box dropped.
     * Returns the item that the mystery box dropped.
     */
    uint get_item();
};


#endif  // MYSTERY_BOX_H
