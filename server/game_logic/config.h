#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <set>
#include <string>

#include <yaml-cpp/yaml.h>

class Config {
private:
    std::map<std::string, int> weapons_reach;
    std::map<std::string, int> weapons_init_ammo;
    int player_falling_speed;
    int player_jumping_height;
    int armor_strength;
    std::set<std::tuple<int, int>> weapon_spawn_sites;

public:
    Config(std::string file_name) {
        YAML::Node config = YAML::LoadFile(file_name);

        for (const auto& item: config["weapons_reach"]) {
            weapons_reach[item.first.as<std::string>()] = item.second.as<int>();
        }

        for (const auto& item: config["weapons_init_ammo"]) {
            weapons_init_ammo[item.first.as<std::string>()] = item.second.as<int>();
        }

        player_falling_speed = config["player_falling_speed"].as<int>();
        player_jumping_height = config["player_jumping_height"].as<int>();
        armor_strength = config["armor_strength"].as<int>();

        for (const auto& coords: config["weapon_spawn_sites"]) {
            weapon_spawn_sites.emplace(coords[0].as<int>(), coords[1].as<int>());
        }
    }
};

#endif
