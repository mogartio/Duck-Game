#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include <vector>
#include "map.h"
#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <vector>
#include <tuple>
#include <filesystem>
#include "../../../common/coordinate.h"


/*
* For each map it finds in the maps folder, it will read the information of each yaml, 
* create a Map instance for each one and store it in a maps vector.
*/
class MapManager {
private:
    std::vector<std::tuple<std::string, Map>> maps;

public:
    MapManager();

    /**
     * @brief Loads all the maps from the maps folder.
     */
    void load_maps();

    /**
     * @brief Returns a random map from the maps vector.
     */
    Map& get_random_map();

};

#endif // MAP_MANAGER_H
