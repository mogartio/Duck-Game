#include "weapon_config.h"
WeaponConfig* WeaponConfig::instance = nullptr;
std::mutex WeaponConfig::mutex;
