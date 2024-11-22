#include "map.h"

#include <algorithm>
#include <iostream>

#define MIN_ZOOM 1000
#define VELOCIDAD_ZOOM 2
#define TILES_PATIÑOS 3


Map::Map(SDL_Renderer* rend, uint tiles, uint width_window, uint height_window):
        rend(rend),
        mapTexture(nullptr),
        parentTexture(nullptr),
        tiles(tiles),
        width_window(width_window),
        height_window(height_window),
        tilesImages(3, nullptr) {
    // Deberia llegarme la info del fondo
    background.initialize(rend, "assets/game_assets/background/day.png");

    for (int i = int(ProjectilesId::ProjectileId::GRENADE);
         i <= int(ProjectilesId::ProjectileId::BULLET_SHOTGUN); i++) {
        ProjectilesId::ProjectileId weapon = static_cast<ProjectilesId::ProjectileId>(i);
        makeWeapon(weapon);
    }

    for (int i = int(Helemts::NORMAL); i <= int(Helemts::TINFOIL); i++) {
        Helemts helmet = static_cast<Helemts>(i);
        makeHelmet(helmet);
    }

    makeArmor();

    for (int i = int(TileType::COLUMN); i <= int(TileType::ROCK); i++) {
        TileType tileType = static_cast<TileType>(i);
        makeTile(tileType);
    }

    parentTexture = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                                      width_window, height_window);
}

// ----------------- Initialize Images -----------------

void Map::makeWeapon(ProjectilesId::ProjectileId id) {
    if ((id == ProjectilesId::ProjectileId::HELMET) || (id == ProjectilesId::ProjectileId::CHEST) ||
        (id == ProjectilesId::ProjectileId::UNARMED)) {
        return;
    }
    Image* weaponImage = new Image();
    std::string path = "assets/game_assets/weapons/";
    path += projectile_to_string(id);
    weaponImage->initialize(rend, path);
    weaponImage->queryTexture();
    if ((id == ProjectilesId::ProjectileId::GRENADE) ||
        (id == ProjectilesId::ProjectileId::DUEL_PISTOL)) {
        weaponImage->defineSize(1 * tiles, 1 * tiles);
    } else {
        weaponImage->defineSize(2 * tiles, 3 * tiles);
    }
    weapons[id] = weaponImage;
}

void Map::makeHelmet(Helemts helmet) {
    // Creo casco de mapa
    Image* mapHelmet = new Image();
    std::string mapPath = "assets/game_assets/map/";
    mapPath += helmet_to_string(helmet);
    mapHelmet->initialize(rend, mapPath);
    mapHelmet->queryTexture();
    mapHelmet->defineSize(2 * tiles, 2 * tiles);
    helmetsMap[mapHelmet] = std::vector<std::pair<int, int>>();

    // Creo casco de inventario
    Image* helmetImage = new Image();
    std::string path = "assets/game_assets/helmets/";
    path += helmet_to_string(helmet);
    helmetImage->initialize(rend, path);
    helmetImage->queryTexture();
    helmetImage->defineSize(3 * tiles, 3 * tiles);  // mismo tamaño que el pato
    helmets.push_back(helmetImage);
}

void Map::makeArmor() {
    // Creo armadura de mapa
    armorOnMap.initialize(rend, "assets/game_assets/map/armor.png");
    armorOnMap.queryTexture();
    armorOnMap.defineSize(2 * tiles, 2 * tiles);

    // Creo armadura de inventario
    armor.initialize(rend, "assets/game_assets/armor/armor4.png");
    armor.queryTexture();
    armor.defineSize(3 * tiles, 3 * tiles);  // mismo tamaño que el pato

    hombro.initialize(rend, "assets/game_assets/armor/hombro4.png");
    hombro.queryTexture();
    hombro.defineSize(3 * tiles, 3 * tiles);  // mismo tamaño q el pato
}

void Map::makeTile(TileType tileType) {
    Image* tile = new Image();
    std::string path =
            "assets/game_assets/tiles/dayTiles/";  // esto dsp se cambia a aceptar el tipo de tile q
                                                   // me mande el server (dia, noche)
    path += tileType_to_string(tileType);
    tile->initialize(rend, path);
    tile->queryTexture();
    tile->defineSize(1 * tiles, 1 * tiles);
    tile->position(0, 0);
    tilesImages[int(tileType)] = tile;
}

void Map::makeMap(int columnas, int filas, std::vector<uint16_t> mapa) {
    // Limpiar mapa
    tilesPlace.clear();
    weaponsPos.clear();
    helmetsMap.clear();
    armorMap.clear();
    playersNamesAlive.clear();
    if (mapTexture != nullptr) {
        SDL_DestroyTexture(mapTexture);
    }
    mapTexture = nullptr;

    for (const auto& pair: players) {
        pair.second->dropEverithing();
        playersNamesAlive.push_back(pair.first);
    }

    this->columnas = columnas;
    this->filas = filas;

    std::vector<std::vector<int>> matriz(filas, std::vector<int>(columnas, 0));

    int filaActual = 0;
    int columnaActual = 0;
    for (uint16_t i: mapa) {
        if (columnaActual >= columnas) {
            columnaActual = 0;
            filaActual++;
        }

        if (filaActual >= filas) {
            break;
        }

        switch (i) {
            case 5:  // piso
                matriz[filaActual][columnaActual] = i;
                if (filaActual == 0) {
                    tilesPlace[TileType::ROCK].push_back(std::pair(columnaActual, filaActual));
                } else if (matriz[filaActual - 1][columnaActual] == i) {
                    tilesPlace[TileType::ROCK].push_back(std::pair(columnaActual, filaActual));
                } else {
                    tilesPlace[TileType::GRASS].push_back(std::pair(columnaActual, filaActual));
                }
                break;
            case 6:                                     // pared
                matriz[filaActual][columnaActual] = i;  // este proximamente va a servir para cuando
                                                        // las columnas tengan tope inferior
                tilesPlace[TileType::COLUMN].push_back(std::pair(columnaActual, filaActual));
                break;
            case 13:  // caja
            case 14:  // caja rota
                break;
            default:
                break;
        }
        columnaActual++;
    }
}

// ----------------- Player -----------------

void Map::addPlayer(int columnaActual, int filaActual, int color, std::string name) {
    Player* player = new Player(rend, Color(color));
    player->defineSize(6 * tiles, 6 * tiles);
    player->update(columnaActual * tiles, filaActual * tiles, DuckState::STANDING, RIGHT);
    // player->armor(&armor, &hombro);
    // player->weapon(weapons[Weapon::MAGNUM]);
    // player->helmet(helmets[int(Helemts::TINFOIL)]);
    players[name] = player;
    playersNamesAlive.push_back(name);
}

void Map::remove(std::string playerName) { playersNamesAlive.remove(playerName); }

void Map::update(std::string player, int x, int y, DuckState state, Side side) {
    players[player]->update(x * tiles, y * tiles, state, side);
}

void Map::allStanding() {
    for (std::string name: playersNamesAlive) {
        players[name]->standing();
    }
}

// ----------------- Weapon -----------------

void Map::newWeapon(int x, int y, ProjectilesId::ProjectileId id) {
    // weaponsMap[id].push_back(std::pair(x, y));
    weaponsPos[id] = std::pair(x, y);
}

void Map::newWeapon(int x, int y, ProjectilesId::ProjectileId id,
                    std::vector<std::pair<uint8_t, uint8_t>> trail) {
    laser.push_back(std::pair(x, y));
}

void Map::weaponPlayer(ProjectilesId::ProjectileId id, std::string playerName) {
    // Si el jugador ya tiene un arma, entonces la suelta
    if (id == ProjectilesId::ProjectileId::UNARMED) {
        players[playerName]->dropWeapon();
        return;
    }
    players[playerName]->weapon(weapons[id]);
    weaponsPos[id] = std::pair(-1, -1);
}

void Map::dropWeapon(std::string playerName) { players[playerName]->dropWeapon(); }

// ----------------- Helmet -----------------

void Map::newHelmet(int x, int y, Helemts newHelmet) {
    helmetsMap[helmets[int(newHelmet)]].push_back(std::pair(x, y));
}

void Map::helmetPlayer(Helemts helmet, std::string playerName) {
    players[playerName]->helmet(helmets[int(helmet)]);
}

// ----------------- Armor -----------------

void Map::newArmor(int x, int y) { armorMap.push_back(std::pair(x, y)); }

void Map::armorPlayer(std::string playerName) { players[playerName]->armor(&armor, &hombro); }

// ----------------- Pre-fill -----------------

SDL_Rect Map::adjustMapZoom() {
    SDL_Rect zoomRect;
    int max_x = 0;
    int max_y = 0;
    int min_x = 0;
    int min_y = 0;
    for (const auto& pair: players) {
        std::pair<int, int> position = pair.second->getPosition();
        // seteamos los valores maximos de x e y
        max_x < position.first ? max_x = position.first + TILES_PATIÑOS * tiles : max_x;
        max_y < position.second ? max_y = position.second + TILES_PATIÑOS * tiles : max_y;

        // seteamos los valores minimos de x e y
        if (position.first < min_x || min_x == 0) {
            min_x = position.first;
        }
        if (position.second < min_y || min_y == 0) {
            min_y = position.second;
        }
    }

    int new_width = std::max((max_x - min_x) * VELOCIDAD_ZOOM, MIN_ZOOM);
    int new_height = (max_y - min_y) * VELOCIDAD_ZOOM;
    int centro_x = (min_x + max_x) / 2;
    int centro_y = (min_y + max_y) / 2;

    float proportion_width = float(width_window) / float(new_width);
    float proportion_height = float(height_window) / float(new_height);
    float proportion = 1 / std::min(proportion_width, proportion_height);

    new_width = proportion * width_window;
    new_height = proportion * height_window;
    min_x = centro_x - new_width / 2;
    min_y = centro_y - new_height / 2;

    zoomRect = {min_x, min_y, new_width, new_height};
    return zoomRect;
}

// ----------------- Fill -----------------

void Map::fill() {  // Dibuja de atras para adelante

    // Cambiamos el render target al parentTexture
    SDL_SetRenderTarget(rend, parentTexture);
    // Limpiamos el parentTexture por si tenia algo
    SDL_RenderClear(rend);

    if (mapTexture == nullptr) {
        // Creamos el mapTexture
        mapTexture = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                                       width_window, height_window);

        // Cambiamos el render target al mapTexture
        SDL_SetRenderTarget(rend, mapTexture);
        // Limpiamos el mapTexture por si tenia algo
        SDL_RenderClear(rend);

        // Dibujamos el fondo
        background.fill(true);

        // Dibujamos el mapa
        for (const auto& tilePair: tilesPlace) {
            if (tilesImages[int(tilePair.first)] != nullptr) {
                for (const auto& pair: tilePair.second) {
                    tilesImages[int(tilePair.first)]->position(pair.first * tiles,
                                                               pair.second * tiles);
                    tilesImages[int(tilePair.first)]->fill();
                }
            }
        }
        // Cambiamos el render target al parentTexture de nuevo
        SDL_SetRenderTarget(rend, parentTexture);
    }

    // Dibujamos el mapa
    SDL_RenderCopy(rend, mapTexture, nullptr, nullptr);


    for (const auto& pair: helmetsMap) {
        for (const auto& helmet: pair.second) {
            pair.first->position(helmet.first * tiles, helmet.second * tiles);
            pair.first->fill();
        }
    }

    for (std::pair armorPos: armorMap) {
        armorOnMap.position(armorPos.first * tiles, armorPos.second * tiles);
        armorOnMap.fill();
    }

    // for (const auto& pair : weaponsMap) {
    //     for (const auto& weapon: pair.second) {
    //         weapons[pair.first]->position(weapon.first * tiles, weapon.second * tiles);
    //         weapons[pair.first]->fill();
    //     }
    // }

    for (const auto& w: weaponsPos) {
        if (w.second.first == -1) {
            continue;
        }
        weapons[w.first]->position(w.second.first * tiles, w.second.second * tiles);
        weapons[w.first]->fill(SDL_FLIP_NONE);
        if (int(w.first) >= int(ProjectilesId::ProjectileId::LASER)) {
            weaponsPos[w.first] = std::pair(-1, -1);
        }
    }

    for (std::string playerName: playersNamesAlive) {
        players[playerName]->fill();
    }

    for (std::pair laserPos: laser) {
        weapons[ProjectilesId::ProjectileId::LASER]->position(laserPos.first * tiles,
                                                              laserPos.second * tiles);
        weapons[ProjectilesId::ProjectileId::LASER]->fill();
    }

    // Cambiamos el render target al renderer
    SDL_SetRenderTarget(rend, nullptr);

    // Usando zoom
    // Generamos el rectangulo de zoom
    SDL_Rect zoomRect = adjustMapZoom();

    // Dibujamos el parentTexture
    SDL_RenderCopy(rend, parentTexture, &zoomRect, nullptr);

    laser.clear();
    /*
    // Sin usar zoom
    // Dibujamos el parentTexture
    SDL_RenderCopy(rend, parentTexture, nullptr, nullptr);
    */
}

// ----------------- Destructor -----------------

Map::~Map() {

    if (parentTexture != nullptr) {
        SDL_DestroyTexture(parentTexture);
    }

    if (mapTexture != nullptr) {
        SDL_DestroyTexture(mapTexture);
    }

    for (Image* piso: tilesImages) {
        delete piso;
    }

    for (const auto& pair: weapons) {
        delete pair.second;
    }

    for (Image* helmet: helmets) {
        delete helmet;
    }

    for (const auto& pair: helmetsMap) {
        delete pair.first;
    }

    for (const auto& pair: players) {
        delete pair.second;
    }
}
