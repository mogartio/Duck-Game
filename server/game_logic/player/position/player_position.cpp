#include "player_position.h"

#include <string>

#include "../../../../common/messages/generic_msg.h"
#include "../player.h"
#define FREE 0
#define OCCUPIED 1
#define DEATH -1
using namespace ActionsId;

PlayerPosition::PlayerPosition(Coordinate& initial_coordinates, Player& player, Stage& stage):
        position(initial_coordinates),
        player(player),
        stage(stage),
        facing_direction(AIM_RIGHT),
        aiming_direction(-1),
        aiming_up(false),
        state(GROUNDED) {
    air_state = std::move(std::make_unique<Grounded>(true));
}

void PlayerPosition::move(const std::set<int>& directions, bool should_change_facing_direction) {
    int x_offset = 0;
    if (state == TRIPPING) {
        free_occupied();
        move_horizontally(air_state->get_x_offset());
        move_horizontally(air_state->get_x_offset());
        move_vertically(air_state->get_offset());
        air_state->update(stage.should_fall(*this), *this);
        return;
    }
    bool let_movment = true;
    for (int direction: directions) {
        if (direction == MOVE_LEFT) {  // si direccion es izq...
            if (should_change_facing_direction) {
                facing_direction = AIM_LEFT;
                aiming_direction = -1;
            }
            x_offset = -1;
        } else if (direction == MOVE_RIGHT) {
            if (should_change_facing_direction) {
                facing_direction = AIM_RIGHT;
                aiming_direction = AIM_RIGHT;
            }
            x_offset = 1;
            // OBS: si se manda instruccion de izq y der al mismo tiempo, se va a la der
        } else if (direction == JUMP) {
            air_state->jump(*this);

        } else if (direction == PLAY_DEAD && state == GROUNDED) {
            set_state(std::make_unique<PlayingDead>(), PLAYING_DEAD);
            let_movment = false;

        } else if (direction == 6) {
            if (should_change_facing_direction) {
                facing_direction = AIM_UP;
                aiming_up = true;
                player.Notify();
            }
        } else {
            continue;
        }
    }
    free_occupied();
    if (let_movment) {
        move_horizontally(x_offset);
    }
    move_vertically(air_state->get_offset());
    air_state->update(stage.should_fall(*this), *this);
}
void PlayerPosition::stop_aiming_up() { aiming_up = false; }

bool PlayerPosition::is_aiming_up() { return aiming_up; }

void PlayerPosition::move_horizontally(int offset) {
    Coordinate current(position.x + offset, position.y);
    int next_position = stage.is_valid_position(current, player.get_id());
    if (next_position == DEATH) {
        player.die();
    } else if (next_position == OCCUPIED) {
        if (state == TRIPPING) {
            set_state(std::make_shared<Grounded>(true), GROUNDED);
        }
        return;
    } else if (next_position == LIVE_BANANA) {
        std::shared_ptr<AirState> new_state = std::make_shared<Tripping>(offset);
        set_state(new_state, TRIPPING);
        // move_horizontally(offset * 4);
    } else {
        if (!(position == current)) {  // sobrecargue el == y no el !=, sue me
            player.Notify();
        }
        position = current;
    }
}

void PlayerPosition::released_jump() { air_state->stop_jumping(*this); }
void PlayerPosition::set_state(std::shared_ptr<AirState> new_state, uint8_t state_code) {
    if (new_state != nullptr) {
        air_state = std::move(new_state);
    }
    state = state_code;
    player.Notify();
}

void PlayerPosition::move_vertically(int offset) {
    int direction_handler = 1;
    if (offset < 0) {
        direction_handler = -1;
    }
    for (int i = 0; i < offset * direction_handler; i++) {
        Coordinate current(position.x, position.y + direction_handler);
        int next_position = stage.is_valid_position(current, player.get_id());
        if (next_position == DEATH) {
            player.die();
        } else if (next_position == OCCUPIED) {
            return;
        } else {
            if (!(position == current)) {  // sobrecargue el == y no el !=, sue me
                player.Notify();
            }
            position = current;
        }
    }
}

void PlayerPosition::occupy(Coordinate& coordinate) { occupied.push_back(coordinate); }
void PlayerPosition::free_occupied() { occupied.clear(); }

std::vector<Coordinate> PlayerPosition::get_occupied() { return occupied; }

Coordinate PlayerPosition::get_position() { return position; }

int PlayerPosition::get_aiming_direction() { return aiming_direction; }
int PlayerPosition::get_facing_direction() { return facing_direction; }  // TODO: arreglar esto
