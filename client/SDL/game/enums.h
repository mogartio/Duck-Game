#ifndef ENUMS_H
#define ENUMS_H

#include <string>

enum class WingState { NORMAL, HOLD, FLAPUP, FLAPDOWN };
enum class TileType { COLUMN, GRASS, ROCK };
enum class Helemts { NORMAL, KNIGHT, TINFOIL };
enum class Color { WHITE, GREY, ORANGE, YELLOW };
enum class Weapon { GRANADA, BANANA, PEWPEWLASE, LASERRIFLE, AK47, DUELOS, COWBOY, MAGNUM, ESCOPETA, SNIPER };

std::string wingState_to_string(WingState state);
std::string tileType_to_string(TileType type);
std::string helmet_to_string(Helemts helmet);
std::string color_to_string(Color color);
std::string weapon_to_string(Weapon weapon);

#endif  // ENUMS_H
