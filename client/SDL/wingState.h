#include <string>

enum WingState {
    NORMAL,
    HOLD,
    FLAPUP,
    FLAPDOWN
};

std::string to_string(WingState state) {
    switch (state) {
        case NORMAL:    return "normal.png";
        case HOLD:      return "hold.png";
        case FLAPUP:    return "flapUp.png";
        case FLAPDOWN:  return "flapDown.png";
        default:        return "unknown.png";
    }
}

