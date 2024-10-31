#ifndef WINGSTATE_H
#define WINGSTATE_H

#include <string>

enum class WingState { NORMAL, HOLD, FLAPUP, FLAPDOWN };

std::string wingState_to_string(WingState state);  // Declaración

#endif  // WINGSTATE_H
