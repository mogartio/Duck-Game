#include "map.h"

#include <algorithm>
#include <iostream>


Map::Map(SDL_Renderer* rend, std::vector<uint16_t> mapa, uint tiles, uint width_window,
         uint height_window):
        rend(rend),
        mapTexture(nullptr),
        parentTexture(nullptr),
        mapa(mapa),
        tiles(tiles),
        width_window(width_window),
        height_window(height_window),
        tilesImages(3, nullptr) {
    // Deberia llegarme la info del fondo
    background.initialize(rend, "img_src/background/day.png");

    for (int i = int(Weapon::MAGNUM); i <= int(Weapon::SNIPER); i++) {
        Weapon weapon = static_cast<Weapon>(i);
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

    prueba.initialize(rend, "img_src/weapons/bullets/laser.png");
    prueba.queryTexture();
    prueba.defineSize(1 * tiles, 1 * tiles);
    prueba.position(100, 100);

    parentTexture = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                                      width_window, height_window);
}

// ----------------- Initialize Images -----------------

void Map::makeWeapon(Weapon weapon) {
    Image* weaponImage = new Image();
    std::string path = "img_src/weapons/";
    path += weapon_to_string(weapon);
    weaponImage->initialize(rend, path);
    weaponImage->queryTexture();
    if ((weapon == Weapon::GRANADA) || (weapon == Weapon::DUELOS)) {
        weaponImage->defineSize(1 * tiles, 1 * tiles);
    } else {
        weaponImage->defineSize(1 * tiles, 2 * tiles);
    }
    weapons[weapon] = weaponImage;
}

void Map::makeHelmet(Helemts helmet) {
    // Creo casco de mapa
    Image* mapHelmet = new Image();
    std::string mapPath = "img_src/map/";
    mapPath += helmet_to_string(helmet);
    mapHelmet->initialize(rend, mapPath);
    mapHelmet->queryTexture();
    mapHelmet->defineSize(2 * tiles, 2 * tiles);
    helmetsMap[mapHelmet] = std::vector<std::pair<int, int>>();

    // Creo casco de inventario
    Image* helmetImage = new Image();
    std::string path = "img_src/helmets/";
    path += helmet_to_string(helmet);
    helmetImage->initialize(rend, path);
    helmetImage->queryTexture();
    helmetImage->defineSize(3 * tiles, 3 * tiles);  // mismo tamaño que el pato
    helmets.push_back(helmetImage);
}

void Map::makeArmor() {
    // Creo armadura de mapa
    armorOnMap.initialize(rend, "img_src/map/armor.png");
    armorOnMap.queryTexture();
    armorOnMap.defineSize(2 * tiles, 2 * tiles);

    // Creo armadura de inventario
    armor.initialize(rend, "img_src/armor/armor4.png");
    armor.queryTexture();
    armor.defineSize(3 * tiles, 3 * tiles);  // mismo tamaño que el pato

    hombro.initialize(rend, "img_src/armor/hombro4.png");
    hombro.queryTexture();
    hombro.defineSize(3 * tiles, 3 * tiles);  // mismo tamaño q el pato
}

void Map::makeTile(TileType tileType) {
    Image* tile = new Image();
    std::string path = "img_src/tiles/dayTiles/";  // esto dsp se cambia a aceptar el tipo de tile q
                                                   // me mande el server (dia, noche)
    path += tileType_to_string(tileType);
    tile->initialize(rend, path);
    tile->queryTexture();
    tile->defineSize(1 * tiles, 1 * tiles);
    tile->position(0, 0);
    tilesImages[int(tileType)] = tile;
}

void Map::makeMap(int columnas, int filas) {
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

                if (matriz[filaActual - 1][columnaActual] == i) {
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
    player->defineSize(3 * tiles, 3 * tiles);
    player->update(columnaActual * tiles, filaActual * tiles, DuckState::STANDING, RIGHT);
    player->armor(&armor, &hombro);
    player->weapon(weapons[Weapon::MAGNUM]);
    player->helmet(helmets[int(Helemts::TINFOIL)]);
    players[name] = player;
    playersNamesAlive.push_back(name);
}

void Map::remove(std::string playerName) { playersNamesAlive.remove(playerName); }

void Map::update(std::string player, int x, int y, DuckState state, Side side) {
    players[player]->update(x * tiles, y * tiles, state, side);
}

// ----------------- Weapon -----------------

void Map::newWeapon(int x, int y, Weapon weapon) { weaponsMap[weapon].push_back(std::pair(x, y)); }

void Map::weaponPlayer(Weapon weapon, std::string playerName) {
    // Si el jugador ya tiene un arma, entonces dispara
    players[playerName]->weapon(weapons[weapon]);
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
        max_x < position.first ? max_x = position.first : max_x;
        max_y < position.second ? max_y = position.second : max_y;

        // seteamos los valores minimos de x e y
        if (position.first < min_x || min_x == 0) {
            min_x = position.first;
        }
        if (position.second < min_y || min_y == 0) {
            min_y = position.second;
        }
    }
    int distancia = 3 * tiles;
    min_x < distancia ? min_x = 0 : min_x -= distancia;
    min_y < distancia ? min_y = 0 : min_y -= distancia;

    int new_width = (max_x - min_x) + 6 * tiles;
    int new_height = (max_y - min_y) + 6 * tiles;

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

    for (const auto& pair: weaponsMap) {
        for (const auto& weapon: pair.second) {
            weapons[pair.first]->position(weapon.first * tiles, weapon.second * tiles);
            weapons[pair.first]->fill();
        }
    }

    for (std::string playerName: playersNamesAlive) {
        players[playerName]->fill();
    }

    prueba.fill();

    // Cambiamos el render target al renderer
    SDL_SetRenderTarget(rend, nullptr);

    // Usando zoom
    /*
    // Generamos el rectangulo de zoom
    SDL_Rect zoomRect = adjustMapZoom();

    // Dibujamos el parentTexture
    SDL_RenderCopy(rend, parentTexture, &zoomRect, nullptr);
    */

    // Sin usar zoom
    // Dibujamos el parentTexture
    SDL_RenderCopy(rend, parentTexture, nullptr, nullptr);
}

// ----------------- Destructor -----------------

Map::~Map() {

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
