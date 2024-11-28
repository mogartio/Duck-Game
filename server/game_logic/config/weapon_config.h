#ifndef WEAPON_CONFIG_H
#define WEAPON_CONFIG_H
#include <map>
#include <mutex>
#include <string>

#include <yaml-cpp/yaml.h>

// Patron singleton
class WeaponConfig {
private:
    static WeaponConfig* instance;
    WeaponConfig(const WeaponConfig&) = delete;
    WeaponConfig& operator=(const WeaponConfig&) = delete;
    static std::mutex mutex;
    explicit WeaponConfig(const std::string& file_name) {
        YAML::Node config = YAML::LoadFile(file_name);
        for (const auto& weapon: config["weapons"]) {
            std::string weapon_name = weapon.first.as<std::string>();
            for (const auto& attribute: weapon.second) {
                weapons[weapon_name][attribute.first.as<std::string>()] =
                        attribute.second.as<int>();
            }
        }
    }


public:
    std::map<std::string, std::map<std::string, int>> weapons;
    static WeaponConfig* get_instance() {
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mutex);
            if (instance == nullptr) {
                instance = new WeaponConfig("../server/game_logic/config/weapon_config.yaml");
            }
        }
        return instance;
    }
};
#endif
