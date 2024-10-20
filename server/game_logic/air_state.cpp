#include "air_state.h"
#include <algorithm>
#include <memory>
#include "player.h"


void Grounded::jump(Player& player){
    player.set_state(std::make_unique<Jumping>());
}
int Grounded::get_offset(){return 0;}
void Grounded::update(bool could_fall, Player& player){
    if (could_fall){
        player.set_state(std::make_unique<Falling>());
    }
}


void Jumping::jump(Player&){ keeps_jumping = true;} 
void Jumping::update(bool could_fall, Player& player){
    if (!keeps_jumping){
        jumps_left = 0;
    }
    jumps_left --;
    if (jumps_left <= 0){
        if (could_fall){
            player.set_state(std::make_unique<Falling>());
            return;
        }
        player.set_state(std::make_unique<Grounded>());
        return;
    }
} 
int Jumping::get_offset() { return -2; }


int Falling::get_offset() { return falling_speed; }
void Falling::jump(Player&) { falling_speed = 1; }
void Falling::update(bool could_fall, Player& player) { 
    if (!could_fall){
        player.set_state(std::make_unique<Grounded>());
        return;
    }
    falling_speed = NORMAL_FALLING_SPEED; 
}
