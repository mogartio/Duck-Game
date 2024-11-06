
#include "air_state.h"

#include <memory>

#include "../config/config.h"

#include "observer.h"
#include "player_position.h"

using namespace PlayerInfoId;

void Grounded::jump(PlayerPosition& player) {
    player.set_state(std::make_unique<Jumping>(), JUMPING);
}
int Grounded::get_offset() { return 0; }
void Grounded::update(bool could_fall, PlayerPosition& player) {
    if (could_fall) {
        player.set_state(std::make_unique<Falling>(), FALLING);
    }
}

void Jumping::stop_jumping(PlayerPosition& player) {
    player.set_state(std::make_unique<Falling>(), FALLING);
}
void Jumping::jump(PlayerPosition&) { keeps_jumping = true; }
void Jumping::update(bool could_fall, PlayerPosition& player) {
    if (!keeps_jumping) {
        jumps_left = 0;
    }
    jumps_left--;
    if (jumps_left <= 0) {
        if (could_fall) {
            player.set_state(std::make_unique<Falling>(), FALLING);
            return;
        }
        player.set_state(std::make_unique<Grounded>(), GROUNDED);
        return;
    }
    keeps_jumping = false;
}
int Jumping::get_offset() { return -2; }


int Falling::get_offset() { return falling_speed; }
void Falling::jump(PlayerPosition&) { falling_speed = 1; }
void Falling::update(bool could_fall, PlayerPosition& player) {
    if (!could_fall) {
        player.set_state(std::make_unique<Grounded>(), GROUNDED);
        return;
    }
    falling_speed = Config::get_instance()->player_falling_speed;
}
