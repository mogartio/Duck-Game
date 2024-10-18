#include "player.h"

Player::Player(Coordinate& initial_position): position(initial_position), id(2), is_alive(true), is_falling(false){
}

Coordinate Player::get_position(){
    return position;
}

void Player::set_position(Coordinate new_position){
    if (is_falling){
        Coordinate updated(new_position.x, new_position.y + 1);
        position = updated;
        return;
    }
    position = new_position;
}
void Player::fall(){ is_falling = true;}
void Player::die(){ is_alive = false;}
void Player::occupy(Coordinate coordinate){
    occupied.push_back(coordinate);
}
void Player::free_occupied(){
    occupied.clear();
}

std::vector<Coordinate> Player::get_occupied(){
    return occupied;
}

