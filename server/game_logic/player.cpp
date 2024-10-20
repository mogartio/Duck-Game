#include "player.h"
#include <algorithm>
#include <cstdlib>
#include "air_state.h"

Player::Player(Coordinate& initial_position, Stage& stage): position(initial_position), id(2), is_alive(true),
stage(stage){
    air_state = std::move(std::make_unique<Grounded>());
}

Coordinate Player::get_position(){
    return position;
}

void Player::move(std::string& direction){
    int x_offset = 0;
    if (direction.compare("a") == 0){
        x_offset = -1;
    } else if (direction.compare("d") == 0) {
        x_offset = 1;
    } else if (direction.compare("w") == 0){
        air_state->jump(*this);
    }
    move_horizontally(x_offset);
    move_vertically(air_state->get_offset());
    stage.delete_player_from_stage(*this); //player no deberia llamar a esto. supongo que el juego podria tener un observador sobre el jugador que sepa si se movio y le pida al stage que actualice su pocision en ese caso.
    //
    stage.draw_player(*this);
    air_state->update(stage.should_fall(*this), *this);
}
void Player::set_state(std::unique_ptr<AirState> new_state){
    air_state = std::move(new_state);
}

void Player::move_horizontally(int offset){
    Coordinate current(position.x + offset, position.y);
    if (stage.is_valid_position(*this, current)){
        position = current;
    }
}

void Player::move_vertically(int offset){
    if (offset < 0){
        move_up(offset);
    } else {
        move_down(offset);
    }
}

void Player::move_up(int offset){
    Coordinate initial_position = position;
    for (int i=0 ; i > offset; i --){
        Coordinate current(position.x, initial_position.y + i - 1);
        if (stage.is_valid_position(*this, current)){
            position = current;
        } else{
            return;
        }
    }
}

void Player::move_down(int offset){
    Coordinate initial_position = position;
    for (int i=0 ; i < offset; i ++){
        Coordinate current(position.x, initial_position.y + i + 1);
        if (stage.is_valid_position(*this, current)){
            position = current;
        } else{
            return;
        }
    }
}

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

