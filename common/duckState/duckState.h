
enum DuckState {
    STANDING,
    WALK,
    JUMP,
    FALL,
    SLOW_FALL,
    LAND,
    PLAY_DEAD
};

std::string to_string(DuckState state, bool walk1 = true) {
    switch (state) {
        case STANDING:   return "standing.png";
        case WALK:
            if (walk1) {
                return "walk1.png";
            } else {
                return "walk2.png";
            }
        case JUMP:       return "jump.png";
        case FALL:       return "fall.png";
        case SLOW_FALL:  return "slowFall.png";
        case LAND:       return "land.png";
        case PLAY_DEAD:  return "playDead.png";
        default:         return "unknown.png";
    }
}

enum Side {
    LEFT,
    RIGHT
};

