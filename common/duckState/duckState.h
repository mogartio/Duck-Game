#ifndef DUCKSTATE_H
#define DUCKSTATE_H
#include <string>

enum class DuckState { 
    STANDING,
    WALK,
    JUMP,
    FALL,
    SLOW_FALL,
    LAND,
    PLAY_DEAD 
};

std::string duckState_to_string(DuckState state, bool walk = true);  // Declaración

enum Side {
    RIGHT,
    LEFT
};
#endif // DUCKSTATE_H


