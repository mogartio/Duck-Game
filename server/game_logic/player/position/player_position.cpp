#include "player_position.h"

#include <string>

#include "../../../../common/messages/generic_msg.h"
#include "../player.h"
using namespace ActionsId;

PlayerPosition::PlayerPosition(Coordinate& initial_coordinates, Player& player, Stage& stage):
        position(initial_coordinates),
        player(player),
        stage(stage),
        facing_direction(AIM_RIGHT),
        aiming_up(false),
        state(GROUNDED) {
    air_state = std::move(std::make_unique<Grounded>());
}

void PlayerPosition::move(std::set<int>& directions) {
    int x_offset = 0;
    for (int direction: directions) {
        if (direction == MOVE_LEFT) {  // si direccion es izq...
            facing_direction = AIM_LEFT;
            x_offset = -1;
        } else if (direction == MOVE_RIGHT) {
            facing_direction = AIM_RIGHT;
            x_offset = 1;
            // OBS: si se manda instruccion de izq y der al mismo tiempo, se va a la der
        } else if (direction == JUMP) {
            air_state->jump(*this);
        } else if (direction == 6) {
            aiming_up = true;
        } else {
            continue;
        }
    }
    free_occupied();
    move_horizontally(x_offset);
    move_vertically(air_state->get_offset());
    air_state->update(stage.should_fall(*this), *this);
}
void PlayerPosition::stop_aiming_up() { aiming_up = false; }

bool PlayerPosition::is_aiming_up() { return aiming_up; }

void PlayerPosition::move_horizontally(int offset) {
    Coordinate current(position.x + offset, position.y);
    if (stage.is_valid_position(current, player.get_id())) {
        if (!(position == current)) {  // sobrecargue el == y no el !=, sue me
            player.Notify();
        }
        position = current;
    }
}
void PlayerPosition::released_jump() { air_state->stop_jumping(*this); }
void PlayerPosition::set_state(std::unique_ptr<AirState> new_state, uint8_t state_code) {
    air_state = std::move(new_state);
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
        if (stage.is_valid_position(current, player.get_id())) {
            if (!(position == current)) {  // sobrecargue el == y no el !=, sue me
                player.Notify();
            }
            position = current;
        } else {
            return;
        }
    }
}

void PlayerPosition::occupy(Coordinate& coordinate) { occupied.push_back(coordinate); }
void PlayerPosition::free_occupied() { occupied.clear(); }

std::vector<Coordinate> PlayerPosition::get_occupied() { return occupied; }

Coordinate PlayerPosition::get_position() { return position; }

int PlayerPosition::get_facing_direction() {
    if (facing_direction == 2) {
        return -1;
    }
    return 1;
}  // malisimo, its never been this serious
