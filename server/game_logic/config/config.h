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
        player_falling_speed = config["player_falling_speed"].as<int>();
        player_jumping_height = config["player_jumping_height"].as<int>();
        armor_strength = config["armor_strength"].as<int>();
        explosion_counter = config["explosion_counter"].as<int>();
        explosion_range = config["explosion_range"].as<int>();
        bullet_size = config["bullet_size"].as<int>();
        throw_speed = config["throw_speed"].as<int>();
        rounds_per_cycle = config["rounds_per_cycle"].as<int>();
        stun_duration = config["stun_duration"].as<int>();
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
    int stun_duration;
    int player_falling_speed;
    int player_jumping_height;
    int armor_strength;
    int rounds_per_cycle;
    int throw_speed;
    std::map<std::string, uint16_t> mapsId;
    int explosion_counter;
    int explosion_range;
    int bullet_size;
    static Config* get_instance() {
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mutex);
            if (instance == nullptr) {
                instance = new Config("../server/game_logic/config/config.yaml");
            }
        }
        return instance;
    }
};
#endif
