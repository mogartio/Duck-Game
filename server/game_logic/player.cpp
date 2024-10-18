#include "player.h"

Player::Player(Coordinate& initial_position): position(initial_position), id(2){
}

Coordinate Player::get_position(){
    return position;
}

void Player::set_position(Coordinate new_position){
    position = new_position;
}
