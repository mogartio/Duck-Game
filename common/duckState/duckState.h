#ifndef DUCKSTATE_H
#define DUCKSTATE_H
#include <string>

enum class DuckState { 
    STANDING,
    WALK,
    JUMP,
    FALL,
    SLOW_FALL,
    PLAY_DEAD 
};

std::string duckState_to_string(DuckState state);  // Declaración

enum Side {
    RIGHT,
    LEFT,
    UP
};
#endif // DUCKSTATE_H


