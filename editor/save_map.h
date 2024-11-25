#ifndef SAVE_MAP_H_
#define SAVE_MAP_H_

#include <yaml-cpp/yaml.h>
#include "../common/messages/generic_msg.h"
#include <iostream>


// Save the editor matrix to a YAML file
inline void saveMap(const std::vector<std::vector<int>>& editor_matrix, const std::string& filename) {
    std::cout << "Saving map to " << filename << std::endl;
    // YAML::Emitter out;
    // out << YAML::BeginMap;
    // out << YAML::Key << "map";
    // out << YAML::Value << YAML::BeginSeq;
    // for (const auto& row : editor_matrix) {
    //     out << YAML::Flow << row;
    // }
    // out << YAML::EndSeq;
    // out << YAML::EndMap;

    // std::ofstream file(filename);
    // file << out.c_str();
}

#endif // SAVE_MAP_H_
