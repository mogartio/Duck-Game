#include <string>

enum WingState {
    NORMAL,
    HOLD,
    FLAPUP,
    FLAPDOWN
};

std::string to_string(WingState state) {
    switch (state) {
        case NORMAL:    return "wing/normal.png";
        case HOLD:      return "wing/hold.png";
        case FLAPUP:    return "wing/flapUp.png";
        case FLAPDOWN:  return "wing/flapDown.png";
        default:        return "unknown.png";
    }
}

