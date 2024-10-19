#include "player.h"

Player::Player(Coordinate& initial_position): position(initial_position), id(2), is_alive(true),
    is_falling(false), is_jumping(false), jumps_left(0), falling_speed(2){
}

Coordinate Player::get_position(){
    return position;
}


void Player::set_position(Coordinate new_position){
    if (is_falling){
        Coordinate updated(new_position.x, new_position.y + falling_speed);
        position = updated;
        falling_speed = 2; // reinicio la variable por si habia disminuido
        return;
    }
    if (is_jumping){
        jumps_left --;
        if (jumps_left == 0){
            is_jumping = false;
            is_falling = true;
        }
        Coordinate updated(new_position.x, new_position.y - 2);
        position = updated;
        return;
    }
    position = new_position;
}

void Player::fall(){ is_falling = true;}
void Player::stop_fall(){ is_falling = false;}
void Player::die(){ is_alive = false;}
void Player::occupy(Coordinate coordinate){
    occupied.push_back(coordinate);
}
void Player::free_occupied(){
    occupied.clear();
}
bool Player::currently_jumping(){ return is_jumping;}

std::vector<Coordinate> Player::get_occupied(){
    return occupied;
}

void Player::jump(){
    if (is_falling){
        falling_speed = 1;
        return;
    }
    if (!is_jumping && !is_falling){
        is_jumping = true;
        jumps_left = 3;
        return;
    }
    if (jumps_left == 0){
        is_jumping = false;
        falling_speed = 1;
        return;
    }
}
