#ifndef CONFIG_H
#define CONFIG_H

#include <filesystem>
#include <iostream>
#include <map>
#include <mutex>
#include <set>
#include <string>
#include <tuple>
#include <vector>

#include <limits.h>
#include <unistd.h>
#include <yaml-cpp/yaml.h>

// Patron singleton
class Config {
private:
    static Config* instance;
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
    static std::mutex mutex;
    explicit Config(const std::string& file_name) {
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
        columns_map = config["columns_map"].as<uint16_t>();
        rows_map = config["rows_map"].as<uint16_t>();
        explosion_counter = config["explosion_counter"].as<int>();
        explosion_range = config["explosion_range"].as<int>();
        for (const auto& coords: config["weapon_spawn_sites"]) {
            weapon_spawn_sites.push_back(
                    std::tuple<int, int>(coords[0].as<int>(), coords[1].as<int>()));
        }
        for (const auto& coords: config["player_spawn_sites"]) {
            player_spawn_sites.push_back(
                    std::tuple<int, int>(coords[0].as<int>(), coords[1].as<int>()));
        }
        int counter = 0;
        for (const auto& ids: config["mapId"]) {
            mapsId[ids.as<std::string>()] = counter;
            counter++;
        }
    }

public:
    // todos los atributos son publicos, viola el encapsulamiento y no me importa
    std::map<std::string, int> weapons_reach;
    std::map<std::string, int> weapons_init_ammo;
    int player_falling_speed;
    int player_jumping_height;
    int armor_strength;
    uint16_t columns_map;
    uint16_t rows_map;
    std::map<std::string, uint16_t> mapsId;
    std::vector<std::tuple<int, int>> weapon_spawn_sites;
    std::vector<std::tuple<int, int>> player_spawn_sites;
    int explosion_counter;
    int explosion_range;
    static Config* get_instance() {
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mutex);
            if (instance == nullptr) {
                instance = new Config("../server/game_logic/config.yaml");
            }
        }
        return instance;
    }
};
#endif
