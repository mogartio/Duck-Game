#include "map_manager.h"

MapManager::MapManager() { load_maps(); }

void MapManager::load_maps() {
    std::string maps_folder_path = "../maps";
    // for each .yaml found in "maps" folder, extract the info and create a Map instance to add to
    // the maps vector
    for (const auto& entry: std::filesystem::directory_iterator(maps_folder_path)) {
        std::string file_name = entry.path().filename().string();

        // if the file is not a yaml file, skip it
        if (file_name.find(".yaml") == std::string::npos) {
            continue;
        }

        // load file
        YAML::Node config = YAML::LoadFile(entry.path().string());

        // extract data
        std::string new_map_name = config["map_name"].as<std::string>();
        int rows = config["map_rows"].as<int>();
        int columns = config["map_columns"].as<int>();
        std::vector<std::tuple<Coordinate>> players_spawn_sites;
        std::vector<std::tuple<Coordinate, int>> items_spawn_sites;
        std::vector<std::vector<int>> matrix;

        // extract player spawn sites
        for (const auto& spawn: config["players_spawn_sites"]) {
            Coordinate spawn_point = Coordinate(spawn[0].as<int>(), spawn[1].as<int>());
            players_spawn_sites.push_back(std::make_tuple(spawn_point));
        }

        // extract item spawn sites
        for (const auto& spawn: config["items_spawn_sites"]) {
            Coordinate spawn_point = Coordinate(spawn[0].as<int>(), spawn[0].as<int>());
            int item_id = spawn[2].as<uint>();
            items_spawn_sites.push_back(std::make_tuple(spawn_point, item_id));
        }

        // extract map matrix
        for (const auto& row: config["map_matrix"]) {
            std::vector<int> row_vector;
            for (const auto& cell: row) {
                row_vector.push_back(cell.as<int>());
            }
            matrix.push_back(row_vector);
        }

        // create map instance
        Map new_map =
                Map(new_map_name, rows, columns, matrix, players_spawn_sites, items_spawn_sites);
        maps.push_back(std::make_tuple(new_map_name, new_map));
    }
}


Map& MapManager::get_random_map() {
    int random_index = rand() % maps.size();
    return std::get<1>(maps[random_index]);
}
