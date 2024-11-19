#ifndef ENUMS_H
#define ENUMS_H

#include <string>
#include "../../../common/messages/generic_msg.h"

enum class WingState { NORMAL, HOLD, FLAPUP, FLAPDOWN };
enum class TileType { COLUMN, GRASS, ROCK };
enum class Helemts { NORMAL, KNIGHT, TINFOIL };
enum class Color { WHITE, YELLOW, ORANGE, GREY };

std::string wingState_to_string(WingState state);
std::string tileType_to_string(TileType type);
std::string helmet_to_string(Helemts helmet);
std::string color_to_string(Color color);
std::string projectile_to_string(ProjectilesId::ProjectileId id);

#endif  // ENUMS_H
