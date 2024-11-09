#include "enums.h"

std::string wingState_to_string(WingState state) {
    switch (state) {
        case WingState::NORMAL:    return "wing/normal.png";
        case WingState::HOLD:      return "wing/hold.png";
        case WingState::FLAPUP:    return "wing/flapUp.png";
        case WingState::FLAPDOWN:  return "wing/flapDown.png";
        default:        return "unknown.png";
    }
}

std::string tileType_to_string(TileType type) {
    switch (type) {
        case TileType::COLUMN: return "column.png";
        case TileType::GRASS:  return "grass.png";
        case TileType::ROCK:   return "rock.png";
        default:        return "middle.png";
    }
}

std::string helmet_to_string(Helemts helmet) {
    switch (helmet) {
        case Helemts::NORMAL:   return "helmet/normal.png";
        case Helemts::KNIGHT:   return "helmet/knight.png";
        case Helemts::TINFOIL:  return "helmet/tinfoil.png";
        default:        return "unknown.png";
    }
}

std::string color_to_string(Color color) {
    switch (color) {
        case Color::WHITE:  return "white/";
        case Color::GREY:   return "grey/";
        case Color::ORANGE: return "orange/";
        case Color::YELLOW: return "yellow/";
        default:        return "unknown";
    }
}

std::string weapon_to_string(Weapon weapon) {
    switch (weapon) {
        case Weapon::GRANADA:       return "weapon/granada.png";
        case Weapon::BANANA:        return "weapon/banana.png";
        case Weapon::PEWPEWLASE:    return "weapon/pewpewlase.png";
        case Weapon::LASERRIFLE:    return "weapon/laserRifle.png";
        case Weapon::AK47:          return "weapon/ak47.png";
        case Weapon::DUELOS:        return "weapon/duelos.png";
        case Weapon::COWBOY:        return "weapon/cowboy.png";
        case Weapon::MAGNUM:        return "weapon/magnum.png";
        case Weapon::ESCOPETA:      return "weapon/escopeta.png";
        case Weapon::SNIPER:        return "weapon/sniper.png";
        default:        return "unknown.png";
    }
}
