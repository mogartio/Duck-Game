#include "duckState.h"

std::string duckState_to_string(DuckState state) {
    switch (state) {
        case DuckState::STANDING:   return "standing.png";
        case DuckState::WALK:       return "walk";
        case DuckState::JUMP:       return "jump.png";
        case DuckState::FALL:       return "fall.png";
        case DuckState::SLOW_FALL:  return "slowFall.png";
        case DuckState::PLAY_DEAD:  return "playDead.png";
        default:         return "standing.png";
    }
}

