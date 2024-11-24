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

std::string helmet_to_string(ProjectilesId::ProjectileId helmet) {
    switch (helmet) {
        case ProjectilesId::ProjectileId::HELMET:   return "normal.png";
        case ProjectilesId::ProjectileId::HELMET2:   return "knight.png";
        case ProjectilesId::ProjectileId::HELMET3:  return "tinfoil.png";
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

std::string projectile_to_string(ProjectilesId::ProjectileId id) {
    switch (id) {
        case ProjectilesId::ProjectileId::GRENADE:       return "granada.png";
        case ProjectilesId::ProjectileId::BANANA:        return "banana.png";
        case ProjectilesId::ProjectileId::PEW_PEW_LASER:    return "pewpewlaser.png";
        case ProjectilesId::ProjectileId::LASER_RIFLE:    return "laserRifle.png";
        case ProjectilesId::ProjectileId::AK_47:          return "ak47.png";
        case ProjectilesId::ProjectileId::DUEL_PISTOL:        return "duelos.png";
        case ProjectilesId::ProjectileId::COWBOY_PISTOL:        return "cowboy.png";
        case ProjectilesId::ProjectileId::MAGNUM:        return "magnum.png";
        case ProjectilesId::ProjectileId::SHOTGUN:      return "escopeta.png";
        case ProjectilesId::ProjectileId::SNIPER:        return "sniper.png";
        
        case ProjectilesId::ProjectileId::LASER:         return "bullets/laser.png";
        case ProjectilesId::ProjectileId::BULLET_PISTOL:     return "bullets/pistol.png";
        case ProjectilesId::ProjectileId::BULLET_SHOTGUN:    return "bullets/escopeta.png";
        default:        return "unknown.png";
    }
}
