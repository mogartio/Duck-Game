#include "map.h"

#include <algorithm>
#include <cmath>
#include <iostream>

#define PROPORCION_AÑADIDA 1.8
#define VELOCIDAD_DE_REACCION_ZOOM 5.0
#define MIN_ZOOM 0.75
#define TILES_PATIÑOS 6


Map::Map(SDL_Renderer* rend, uint tiles, uint width_window, uint height_window):
        rend(rend),
        mapTexture(nullptr),
        parentTexture(nullptr),
        tiles(tiles),
        width_window(width_window),
        height_window(height_window),
        tilesImagesDay(3, nullptr),
        tilesImagesNight(3, nullptr),
        currentZoom(1.0f) {

    // inicializo las imagenes
    armor = std::make_shared<Image>();
    hombro = std::make_shared<Image>();
    armorOnMap = std::make_shared<Image>();
    background = std::make_shared<Image>();
    prueba = std::make_shared<Image>();

    // Deberia llegarme la info del fondo
    setTheme(theme);

    for (int i = int(ProjectilesId::ProjectileId::AK_47);
         i <= int(ProjectilesId::ProjectileId::BULLET_SHOTGUN); i++) {
        ProjectilesId::ProjectileId weapon = static_cast<ProjectilesId::ProjectileId>(i);
        makeWeapon(weapon);
    }

    makeExplosion();

    for (int i = int(ProjectilesId::ProjectileId::HELMET);
         i <= int(ProjectilesId::ProjectileId::HELMET3); i++) {
        ProjectilesId::ProjectileId helmet = static_cast<ProjectilesId::ProjectileId>(i);
        makeHelmet(helmet);
    }

    makeArmor();

    for (int i = int(TileType::COLUMN); i <= int(TileType::ROCK); i++) {
        TileType tileType = static_cast<TileType>(i);
        makeTile(tileType);
    }

    makeBoxes();

    parentTexture = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                                      width_window, height_window);
}

// ----------------- Initialize Images -----------------

void Map::setTheme(uint theme) {
    // clean shared_ptr
    this->theme = theme;
    background.reset();
    background = std::make_shared<Image>();

    if (theme == GenericMsg::Theme::DAY) {
        background->initialize(rend, "assets/game_assets/background/day.png");
    } else if (theme == GenericMsg::Theme::NIGHT) {
        background->initialize(rend, "assets/game_assets/background/night.png");
    }
}

void Map::makeWeapon(ProjectilesId::ProjectileId id) {
    if (id == ProjectilesId::ProjectileId::UNARMED) {
        return;
    }
    std::shared_ptr<Image> weaponImage = std::make_shared<Image>();
    std::string path = "assets/game_assets/weapons/";
    path += projectile_to_string(id);
    weaponImage->initialize(rend, path);
    weaponImage->queryTexture();
    if ((id == ProjectilesId::ProjectileId::GRENADE) ||
        (id == ProjectilesId::ProjectileId::DUEL_PISTOL)) {
        weaponImage->defineSize(2 * tiles, 2 * tiles);
    } else {
        weaponImage->defineSize(2 * tiles, 3 * tiles);
    }
    weapons[id] = weaponImage;
}

void Map::makeExplosion() {
    for (int i = 1; i <= 7; i++) {
        std::shared_ptr<Image> explosion = std::make_shared<Image>();
        std::string path = "assets/game_assets/weapons/bullets/explosion";
        path += std::to_string(i);
        path += ".png";
        explosion->initialize(rend, path);
        explosion->queryTexture();
        explosion->defineSize(6 * tiles, 6 * tiles);
        explosions.push_back(explosion);
    }
}

void Map::makeHelmet(ProjectilesId::ProjectileId helmet) {
    // Creo casco de mapa
    std::shared_ptr<Image> mapHelmet = std::make_shared<Image>();
    std::string mapPath = "assets/game_assets/map/";
    mapPath += helmet_to_string(helmet);
    mapHelmet->initialize(rend, mapPath);
    mapHelmet->queryTexture();
    mapHelmet->defineSize(2 * tiles, 2 * tiles);

    helmetsMap[helmet] = mapHelmet;
    helmetsPos[helmet] = std::vector<std::pair<int, int>>();

    // Creo casco de inventario
    std::shared_ptr<Image> helmetImage = std::make_shared<Image>();
    std::string path = "assets/game_assets/helmets/";
    path += helmet_to_string(helmet);
    helmetImage->initialize(rend, path);
    helmetImage->queryTexture();
    helmetImage->defineSize(6 * tiles, 6 * tiles);  // mismo tamaño que el pato
    helmets[helmet] = helmetImage;
}

void Map::makeArmor() {
    // Creo armadura de mapa
    armorOnMap->initialize(rend, "assets/game_assets/map/armor.png");
    armorOnMap->queryTexture();
    armorOnMap->defineSize(2 * tiles, 2 * tiles);

    // Creo armadura de inventario
    armor->initialize(rend, "assets/game_assets/armor/armor4.png");
    armor->queryTexture();
    armor->defineSize(6 * tiles, 6 * tiles);  // mismo tamaño que el pato

    hombro->initialize(rend, "assets/game_assets/armor/hombro4.png");
    hombro->queryTexture();
    hombro->defineSize(6 * tiles, 6 * tiles);  // mismo tamaño q el pato
}

void Map::makeTile(TileType tileType) {
    std::shared_ptr<Image> dayTile = std::make_shared<Image>();
    std::shared_ptr<Image> nightTile = std::make_shared<Image>();
    std::string path =
            "assets/game_assets/tiles/nightTiles/";  // esto dsp se cambia a aceptar el tipo de tile
                                                     // q me mande el server (dia, noche)
    path += tileType_to_string(tileType);
    nightTile->initialize(rend, path);
    nightTile->queryTexture();
    nightTile->defineSize(6 * tiles, 6 * tiles);
    nightTile->position(0, 0);
    tilesImagesNight[int(tileType)] = nightTile;
    path = "assets/game_assets/tiles/dayTiles/";  // esto dsp se cambia a aceptar el tipo de tile q
                                                  // me mande el server (dia, noche)
    path += tileType_to_string(tileType);
    dayTile->initialize(rend, path);
    dayTile->queryTexture();
    dayTile->defineSize(6 * tiles, 6 * tiles);
    dayTile->position(0, 0);
    tilesImagesDay[int(tileType)] = dayTile;
}

void Map::makeBoxes() {
    // Creo cajas
    for (int i = 1; i <= 8; i++) {
        std::string path = "assets/game_assets/box/";
        path += std::to_string(i);
        path += ".png";

        std::shared_ptr<Image> box = std::make_shared<Image>();
        box->initialize(rend, path);
        box->queryTexture();
        box->defineSize(3 * tiles, 3 * tiles);
        boxes.push_back(box);
    }
}

bool Map::canAddTile(std::vector<std::vector<int>> matriz, int filaActual, int columnaActual) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            // Si esta fuera de rango saltea la pos
            if ((filaActual - i < 0 || columnaActual - j < 0) ||
                (static_cast<size_t>(filaActual - i) >= matriz.size() ||
                 static_cast<size_t>(columnaActual - j) >= matriz[0].size())) {
                continue;
            }

            // Si hay un tile en esa pos entonces ya no se puede poner otro
            if ((matriz[filaActual - i][columnaActual - j] == 5) ||
                (matriz[filaActual - i][columnaActual - j] == 6)) {
                return false;
            }
        }
    }
    return true;
}

void Map::redifine_sizes() {

    for (const auto& pair: players) {
        pair.second->defineSize(6 * tiles, 6 * tiles);
        pair.second->set_tiles(tiles);
    }

    for (const auto& pair: weapons) {
        if ((pair.first == ProjectilesId::ProjectileId::GRENADE) ||
            (pair.first == ProjectilesId::ProjectileId::DUEL_PISTOL)) {
            pair.second->defineSize(2 * tiles, 2 * tiles);
        } else {
            pair.second->defineSize(2 * tiles, 3 * tiles);
        }
    }

    for (const auto& pair: helmets) {
        pair.second->defineSize(6 * tiles, 6 * tiles);
    }

    armor->defineSize(6 * tiles, 6 * tiles);
    hombro->defineSize(6 * tiles, 6 * tiles);
    armorOnMap->defineSize(2 * tiles, 2 * tiles);

    for (const auto& pair: tilesImagesDay) {
        if (pair != nullptr) {
            pair->defineSize(6 * tiles, 6 * tiles);
        }
    }

    for (const auto& pair: tilesImagesNight) {
        if (pair != nullptr) {
            pair->defineSize(6 * tiles, 6 * tiles);
        }
    }

    for (const auto& pair: explosions) {
        pair->defineSize(6 * tiles, 6 * tiles);
    }
}

void Map::makeMap(int columnas, int filas, std::vector<uint16_t> mapa) {

    // Limpiar mapa
    tilesPlace.clear();
    weaponsMap.clear();
    explosionsPos.clear();
    helmetsPos.clear();
    armorMap.clear();
    boxesPos.clear();
    playersNamesAlive.clear();
    if (mapTexture != nullptr) {
        SDL_DestroyTexture(mapTexture);
    }
    mapTexture = nullptr;
    currentZoom = 1.0f;

    // Limpiar jugadores
    for (const auto& pair: players) {
        pair.second->dropEverithing();
        playersNamesAlive.push_back(pair.first);
    }

    // Actualizo tiles
    this->columnas = columnas;
    this->filas = filas;

    uint tiles_w = width_window / columnas;
    uint tiles_h = height_window / filas;
    this->tiles = std::min(tiles_w, tiles_h);

    redifine_sizes();

    // Creo la matriz
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
                if (canAddTile(matriz, filaActual, columnaActual)) {
                    matriz[filaActual][columnaActual] = i;
                    if (filaActual == 0) {
                        tilesPlace[TileType::ROCK].push_back(std::pair(columnaActual, filaActual));
                    } else if ((filaActual >= 6) && (matriz[filaActual - 6][columnaActual] == i)) {
                        tilesPlace[TileType::ROCK].push_back(std::pair(columnaActual, filaActual));
                    } else {
                        tilesPlace[TileType::GRASS].push_back(std::pair(columnaActual, filaActual));
                    }
                }

                break;
            case 6:  // pared
                if (canAddTile(matriz, filaActual, columnaActual)) {
                    matriz[filaActual][columnaActual] = i;
                    tilesPlace[TileType::COLUMN].push_back(std::pair(columnaActual, filaActual));
                }

                break;
            default:
                break;
        }
        columnaActual++;
    }
}

// ----------------- Player -----------------

void Map::addPlayer(int columnaActual, int filaActual, int color, std::string name) {
    std::shared_ptr<Player> player = std::make_shared<Player>(rend, Color(color));
    player->defineSize(6 * tiles, 6 * tiles);
    player->set_tiles(tiles);
    player->update(columnaActual * tiles, filaActual * tiles, DuckState::STANDING, RIGHT);
    players[name] = player;
    playersNamesAlive.push_back(name);

    playersPoints[name] = 0;
}

void Map::remove(std::string playerName) { playersNamesAlive.remove(playerName); }

void Map::update(std::string player, int x, int y, DuckState state, Side side) {
    players[player]->update(x * tiles, y * tiles, state, side);
}

void Map::standing(std::unordered_map<std::string, bool> players_updated) {
    for (std::string name: playersNamesAlive) {
        if (!players_updated[name]) {
            players[name]->standing();
        }
    }
}

// ----------------- Points -----------------

void Map::addPoints(std::string playerName) { playersPoints[playerName]++; }

std::pair<std::string, std::string> Map::get_winner() {
    int maxPoints = 0;
    std::string winner;
    for (const auto& pair: playersPoints) {
        if (pair.second > maxPoints) {
            maxPoints = pair.second;
            winner = pair.first;
        }
    }
    std::string color_path = players[winner]->get_file();
    return std::pair(winner, color_path);
}

std::unordered_map<std::string, int> Map::getPoints() { return playersPoints; }

// ----------------- Weapon -----------------

void Map::newWeapon(int x, int y, ProjectilesId::ProjectileId id, int facing_direction_first,
                    int facing_direction_second) {
    
    if (id == ProjectilesId::ProjectileId::EXPLOSION) {
        explosion(x, y);
    } else if (id == ProjectilesId::ProjectileId::CHEST) {
        newArmor(x, y);
    } else if (id == ProjectilesId::ProjectileId::MYSTERY_BOX) {
        newBox(x, y);
    } else if (int(id) >= int(ProjectilesId::ProjectileId::HELMET)) {
        newHelmet(x, y, id);
    } else {
        weaponsMap[id] = WeaponData(x, y, facing_direction_first, facing_direction_second);
    }
}


void Map::weaponPlayer(ProjectilesId::ProjectileId id, std::string playerName) {
    // Si el jugador ya tiene un arma, entonces la suelta
    if (id == ProjectilesId::ProjectileId::UNARMED) {
        bool dropped = players[playerName]->dropWeapon();
        if (!dropped) {
            dropped = players[playerName]->dropArmor();
        }
        if (!dropped) {
            players[playerName]->dropHelmet();
        }
        return;
    }

    if (id == ProjectilesId::ProjectileId::CHEST) {
        armorPlayer(playerName);
        return;
    }

    if (int(id) >= int(ProjectilesId::ProjectileId::HELMET)) {
        helmetPlayer(id, playerName);
        return;
    }

    players[playerName]->weapon(weapons[id]);
}

// ----------------- Helmet -----------------

void Map::newHelmet(int x, int y, ProjectilesId::ProjectileId newHelmet) {
    helmetsPos[newHelmet].push_back(std::pair(x, y));
}

void Map::helmetPlayer(ProjectilesId::ProjectileId helmet, std::string playerName) {
    players[playerName]->helmet(helmets[helmet]);
}

// ----------------- Armor -----------------

void Map::newArmor(int x, int y) { armorMap.push_back(std::pair(x, y)); }

void Map::armorPlayer(std::string playerName) { players[playerName]->armor(armor, hombro); }

// ----------------- Explosion -----------------

void Map::explosion(int x, int y) {
    explosionsPos.push_back(std::pair(x, y));
    explosionCounter.push_back(0);
}

// ----------------- Box -----------------

void Map::newBox(int x, int y) { 
    // Color de caja al azar
    int box = rand() % 8;
    boxesPos.push_back(std::pair(box, std::pair(x, y)));
}

// ----------------- Remove -----------------

void Map::removeWeapon(int x, int y, ProjectilesId::ProjectileId id) {

    std::pair<int, int> position = std::pair(x, y);

    if (id == ProjectilesId::ProjectileId::CHEST) {
        armorMap.erase(std::remove(armorMap.begin(), armorMap.end(), position),
                       armorMap.end());

    } else if (id == ProjectilesId::ProjectileId::MYSTERY_BOX) {
        boxesPos.erase(
            std::remove_if(
                boxesPos.begin(),
                boxesPos.end(),
                [&position](const std::pair<int, std::pair<int, int>>& box) {
                    return box.second == position; // Compara con el segundo pair
                }),
            boxesPos.end());

    } else if (int(id) >= int(ProjectilesId::ProjectileId::HELMET)) {
        helmetsPos[id].erase(
                std::remove(helmetsPos[id].begin(), helmetsPos[id].end(), position),
                helmetsPos[id].end());

    } else {
        for (auto it = weaponsMap.begin(); it != weaponsMap.end(); ++it) {
            if (it->second.pos_x == x && it->second.pos_y == y) {
                weaponsMap.erase(it);
                return;
            }
        }
    }
}


// ----------------- Pre-fill -----------------

// Ajusta el zoom de manera más conservadora
float Map::animationZoom(float targetZoom) {
    float deltaTime = getDeltaTime();
    float difference = targetZoom - currentZoom;
    if (difference > 0) {  // Zoom out
        difference *= 2.5f;  // Factor adicional para alejar más rápido
    }

    // Ajusta el factor dinámico con una interpolación más lenta
    float smoothFactor = std::clamp(static_cast<float>(std::abs(difference) * VELOCIDAD_DE_REACCION_ZOOM), 0.05f, 20.0f);
    float newZoom = currentZoom + difference * smoothFactor * deltaTime;

    // Limitar el valor del zoom entre el nuevo mínimo y 1.0f
    return std::clamp(static_cast<double>(newZoom), MIN_ZOOM, 1.0);
}

SDL_Rect Map::adjustMapZoom() {
    SDL_Rect zoomRect;
    int max_x = 0, max_y = 0, min_x = 0, min_y = 0;

    for (const auto& pair : players) {
        auto position = pair.second->getPosition();
        max_x = std::max(max_x, static_cast<int>(position.first + TILES_PATIÑOS * tiles));
        max_y = std::max(max_y, static_cast<int>(position.second + TILES_PATIÑOS * tiles));
        min_x = (min_x == 0 || position.first < min_x) ? position.first : min_x;
        min_y = (min_y == 0 || position.second < min_y) ? position.second : min_y;
    }

    int new_width = static_cast<int>((max_x - min_x) * PROPORCION_AÑADIDA);
    int new_height = static_cast<int>((max_y - min_y) * PROPORCION_AÑADIDA);
    int centro_x = (min_x + max_x) / 2;
    int centro_y = (min_y + max_y) / 2;

    // Ajustar la proporción del zoom
    float proportion_width = static_cast<float>(new_width) / width_window;
    float proportion_height = static_cast<float>(new_height) / height_window;
    float targetProportion = std::max(proportion_width, proportion_height);
    currentZoom = animationZoom(targetProportion);

    // Calcular las dimensiones finales
    new_width = static_cast<int>(currentZoom * width_window);
    new_height = static_cast<int>(currentZoom * height_window);

    // Centrar el área, evitando movimientos bruscos
    centro_x = std::clamp(centro_x, new_width / 2, static_cast<int>(width_window) - new_width / 2);
    centro_y = std::clamp(centro_y, new_height / 2, static_cast<int>(height_window) - new_height / 2);

    zoomRect = {centro_x - new_width / 2, centro_y - new_height / 2, new_width, new_height};
    return zoomRect;
}

float Map::getDeltaTime() {
    static Uint32 lastTime = SDL_GetPerformanceCounter();
    Uint32 currentTime = SDL_GetPerformanceCounter();
    float deltaTime = static_cast<float>(currentTime - lastTime) / SDL_GetPerformanceFrequency();
    lastTime = currentTime;
    return deltaTime;
}

// ----------------- Fill -----------------

int condicionAnguloBalas(int facing_direction_first, int facing_direction_second) {
    if (facing_direction_first == 0) {
        if (facing_direction_second == 1) {
            return 90;
        } else if (facing_direction_second == 2) {
            return 270;
        }
    } else if (facing_direction_first == 1) {
        if (facing_direction_second == 0) {
            return 0;
        } else if (facing_direction_second == 1) {
            return 45;
        } else if (facing_direction_second == 2) {
            return 315;
        }
    } else if (facing_direction_first == 2) {
        if (facing_direction_second == 0) {
            return 180;
        } else if (facing_direction_second == 1) {
            return 135;
        } else if (facing_direction_second == 2) {
            return 225;
        }
    }

    return 0;
}

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
        background->fill(true);

        // Dibujamos el mapa
        for (const auto& tilePair: tilesPlace) {
            if (theme == GenericMsg::Theme::DAY) {
                if (tilesImagesDay[int(tilePair.first)] != nullptr) {
                    for (const auto& pair: tilePair.second) {
                        tilesImagesDay[int(tilePair.first)]->position(pair.first * tiles,
                                                                      pair.second * tiles);
                        tilesImagesDay[int(tilePair.first)]->fill();
                    }
                }
            } else {
                if (tilesImagesNight[int(tilePair.first)] != nullptr) {
                    for (const auto& pair: tilePair.second) {
                        tilesImagesNight[int(tilePair.first)]->position(pair.first * tiles,
                                                                        pair.second * tiles);
                        tilesImagesNight[int(tilePair.first)]->fill();
                    }
                }
            }
        }
        // Cambiamos el render target al parentTexture de nuevo
        SDL_SetRenderTarget(rend, parentTexture);
    }

    // Dibujamos el mapa
    SDL_RenderCopy(rend, mapTexture, nullptr, nullptr);

    // Helmets
    for (const auto& helmet: helmetsPos) {
        for (const auto& pos: helmet.second) {
            helmetsMap[helmet.first]->position(pos.first * tiles, pos.second * tiles);
            helmetsMap[helmet.first]->fill();
        }
    }

    // Armor
    for (std::pair armorPos: armorMap) {
        armorOnMap->position(armorPos.first * tiles, armorPos.second * tiles);
        armorOnMap->fill();
    }

    // Weapons
    for (const auto& pair: weaponsMap) {
        const WeaponData& weaponData = pair.second;

        weapons[pair.first]->position(weaponData.pos_x * tiles, weaponData.pos_y * tiles);

        int angle = condicionAnguloBalas(weaponData.facing_direction_first,
                                         weaponData.facing_direction_second);

        weapons[pair.first]->fill(angle, SDL_FLIP_NONE);
    }

    // Boxes
    for (std::pair boxPos: boxesPos) {
        boxes[boxPos.first]->position(boxPos.second.first * tiles, boxPos.second.second * tiles);
        boxes[boxPos.first]->fill();
    }

    // Players
    for (std::string playerName: playersNamesAlive) {
        players[playerName]->fill();
    }

    // Explosions
    std::vector<size_t> toRemove;
    for (size_t i = 0; i < explosionsPos.size(); i++) {
        size_t explosionIndex = explosionCounter[i] / 4;
        if (explosionIndex >= explosions.size()) {
            continue;
        }
        if (explosionCounter[i] % 4 != 0) {
            explosionCounter[i]++;
            explosions[explosionIndex]->fill();
            continue;
        }
        std::pair pos = explosionsPos[i];
        explosions[explosionIndex]->position((pos.first - 3) * tiles, (pos.second - 3) * tiles);
        explosions[explosionIndex]->fill();
        explosionCounter[i]++;
        if (explosionCounter[i] > 26) {
            toRemove.push_back(i);
        }
    }

    // Elimina las explosiones que ya terminaron de explotar
    for (auto it = toRemove.rbegin(); it != toRemove.rend(); ++it) {
        explosionsPos.erase(explosionsPos.begin() + *it);
        explosionCounter.erase(explosionCounter.begin() + *it);
    }

    // Cambiamos el render target al renderer
    SDL_SetRenderTarget(rend, nullptr);

    // Usando zoom
    // Generamos el rectangulo de zoom
    SDL_Rect zoomRect = adjustMapZoom();

    // Dibujamos el parentTexture
    SDL_RenderCopy(rend, parentTexture, &zoomRect, nullptr);
}

SDL_Texture* Map::getTextureMapWithAll() const { return parentTexture; }

SDL_Texture* Map::getTextureMapWithoutAnything() const { return mapTexture; }

// ----------------- Destructor -----------------

Map::~Map() {

    if (parentTexture != nullptr) {
        SDL_DestroyTexture(parentTexture);
    }

    if (mapTexture != nullptr) {
        SDL_DestroyTexture(mapTexture);
    }
}
