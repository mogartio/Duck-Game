// Esto es estupido
// hace que me compile sin warnings
// pero me enoja
#include "config.h"
Config* Config::instance = nullptr;
std::mutex Config::mutex;
