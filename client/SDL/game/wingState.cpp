#include "wingState.h"

std::string wingState_to_string(WingState state) {
    switch (state) {
        case WingState::NORMAL:    return "wing/normal.png";
        case WingState::HOLD:      return "wing/hold.png";
        case WingState::FLAPUP:    return "wing/flapUp.png";
        case WingState::FLAPDOWN:  return "wing/flapDown.png";
        default:        return "unknown.png";
    }
}
