#ifndef SAVE_MAP_H_
#define SAVE_MAP_H_

#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>
#include "items_ids.h"
#define FLOOR 5
#define BG 0
#define COLUMN 6


/*
    Saves the editor matrix to a YAML file

    The structure por the yaml file is the following:
        ----------------------------------------------------------------
        map_name: "name"

        map_rows: n
        map_columns: m

        map_player_spawn_sites: # only list placed players
            - [x1, y1]
            - [x2, y2]
            - [x3, y3]
            - [x4, y4]
        
        map_weapon_spawn_sites: # only list placed weapons (or armors)
            - [x1, y1, id]
            - [x2, y2, id]
            - [x3, y3, id]
            - [x4, y4, id]
            - ...
        
        map_matrix:
            - [int, int, int, int, int, ...]
            - [int, int, int, int, int, ...]
            - [int, int, int, int, int, ...]
            - [int, int, int, int, int, ...]
            - ...
        ----------------------------------------------------------------

    The spawns will not be placed in the map_matrix even though they are placed in the editor matrix;
    they will be represented in the map_player_spawn_sites and map_weapon_spawn_sites lists.
    
    map_matrix will have only the map tiles [GRASS, ROCK, COLUMN] where grass and rock are represented with the same number;
    each item in the editor matrix will occupy a 6x6 square in the map_matrix.

    The map_matrix will have a two 6x6 tile padding around the actual map

    The weapons and armors lists will have each position plus the uint8_t id of the item defined in generic_msg.h

    The spawn coordinates will be defined as:
        - for the players: the top left corner of the player
        - for the weapons: the top left corner of the weapon

    The file will be placed in the folder maps/ with the name map_name.yaml
*/ 
inline void saveMap(const std::vector<std::vector<int>>& editor_matrix, const std::string& map_name) {
    const int padding = 12; // Padding size (6x6 tiles padding)
    const std::string file_name = "maps/" + map_name + ".yaml";

    int editor_rows = editor_matrix.size();
    int editor_columns = editor_matrix[0].size();

    int map_rows = editor_rows * 6; // Each cell in editor_matrix becomes 6x6 in map_matrix
    int map_columns = editor_columns * 6;

    // New dimensions with padding
    int padded_rows = map_rows + 2 * padding;
    int padded_columns = map_columns + 2 * padding;

    // Initialize padded map_matrix with BG tiles
    std::vector<std::vector<int>> padded_map_matrix(padded_rows, std::vector<int>(padded_columns, BG));

    std::vector<std::tuple<int, int>> player_spawn_sites;
    std::vector<std::tuple<int, int, uint>> weapon_spawn_sites;

    // Fill the map matrix and adjust for padding
    for (int i = 0; i < editor_rows; ++i) {
        for (int j = 0; j < editor_columns; ++j) {
            int cellValue = editor_matrix[i][j];

            if (Id::players.find(cellValue) != Id::players.end()) {
                // Player spawn site
                player_spawn_sites.emplace_back(j * 6 + padding, i * 6 + padding);

            } else if (Id::weapons.find(cellValue) != Id::weapons.end()) {
                // Weapon or armor spawn site
                weapon_spawn_sites.emplace_back(j * 6 + padding, i * 6 + padding, cellValue);
            }

            for (int x = 0; x < 6; ++x) {
                for (int y = 0; y < 6; ++y) {
                    int dest_row = i * 6 + y + padding;
                    int dest_col = j * 6 + x + padding;

                    if (cellValue == Id::GRASS || cellValue == Id::ROCK) {
                        padded_map_matrix[dest_row][dest_col] = FLOOR;
                    } else if (cellValue == Id::COL) {
                        padded_map_matrix[dest_row][dest_col] = COLUMN;
                    } else {
                        padded_map_matrix[dest_row][dest_col] = BG;
                    }
                }
            }
        }
    }

    // Create the YAML file
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "map_name" << YAML::Value << map_name;
    out << YAML::Key << "map_rows" << YAML::Value << padded_rows;
    out << YAML::Key << "map_columns" << YAML::Value << padded_columns;
    out << YAML::Key << "map_player_spawn_sites" << YAML::Value << YAML::BeginSeq;
    for (const auto& spawn : player_spawn_sites) {
        out << YAML::Flow << YAML::BeginSeq << std::get<0>(spawn) << std::get<1>(spawn) << YAML::EndSeq;
    }
    out << YAML::EndSeq;
    out << YAML::Key << "map_weapon_spawn_sites" << YAML::Value << YAML::BeginSeq;
    for (const auto& spawn : weapon_spawn_sites) {
        out << YAML::Flow << YAML::BeginSeq << std::get<0>(spawn) << std::get<1>(spawn) << std::get<2>(spawn) << YAML::EndSeq;
    }
    out << YAML::EndSeq;
    out << YAML::Key << "map_matrix" << YAML::Value << YAML::BeginSeq;
    for (const auto& row : padded_map_matrix) {
        out << YAML::Flow << YAML::BeginSeq;
        for (int cell : row) {
            out << cell;
        }
        out << YAML::EndSeq;
    }
    out << YAML::EndSeq;
    out << YAML::EndMap;

    // Save into the maps/ folder
    std::ofstream file(file_name);
    file << out.c_str();
    file.close();

    std::cout << "Map saved successfully in " << file_name << std::endl;
}

#endif // SAVE_MAP_H_
