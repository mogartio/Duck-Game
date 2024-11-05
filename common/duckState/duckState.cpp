#include "duckState.h"

std::string duckState_to_string(DuckState state, bool walk1) {
    switch (state) {
        case DuckState::STANDING:   return "standing.png";
        case DuckState::WALK:
            if (walk1) {
                return "walk1.png";
            } else {
                return "walk2.png";
            }
        case DuckState::JUMP:       return "jump.png";
        case DuckState::FALL:       return "fall.png";
        case DuckState::SLOW_FALL:  return "slowFall.png";
        case DuckState::LAND:       return "land.png";
        case DuckState::PLAY_DEAD:  return "playDead.png";
        default:         return "unknown.png";
    }
}

