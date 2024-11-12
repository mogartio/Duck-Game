#include "map.h"

#include <iostream>
#include <algorithm>

#define TILES_TO_PIXELS 16

Map::Map(SDL_Renderer* rend): rend(rend), tilesImages(3, nullptr) {
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

    // newWeapon(5, 5, Weapon::MAGNUM);

    for (int i = int(TileType::COLUMN); i <= int(TileType::ROCK); i++) {
        TileType tileType = static_cast<TileType>(i);
        makeTile(tileType);
    }
}

// ----------------- Initialize Images -----------------

void Map::makeWeapon(Weapon weapon) {
    Image* weaponImage = new Image();
    std::string path = "img_src/weapons/";
    path += weapon_to_string(weapon);
    weaponImage->initialize(rend, path);
    weaponImage->queryTexture();
    if ((weapon == Weapon::GRANADA) || (weapon == Weapon::DUELOS)) {
        weaponImage->defineSize(1 * TILES_TO_PIXELS, 1 * TILES_TO_PIXELS);
    } else {
        weaponImage->defineSize(1 * TILES_TO_PIXELS, 2 * TILES_TO_PIXELS);
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
    mapHelmet->defineSize(2 * TILES_TO_PIXELS, 2 * TILES_TO_PIXELS);
    helmetsMap[mapHelmet] = std::vector<std::pair<int, int>>();

    // Creo casco de inventario
    Image* helmetImage = new Image();
    std::string path = "img_src/helmets/";
    path += helmet_to_string(helmet);
    helmetImage->initialize(rend, path);
    helmetImage->queryTexture();
    helmetImage->defineSize(3 * TILES_TO_PIXELS, 3 * TILES_TO_PIXELS);
    helmets.push_back(helmetImage);
}

void Map::makeArmor() {
    // Creo armadura de mapa
    armorOnMap.initialize(rend, "img_src/map/armor.png");
    armorOnMap.queryTexture();
    armorOnMap.defineSize(2 * TILES_TO_PIXELS, 2 * TILES_TO_PIXELS);

    // Creo armadura de inventario
    armor.initialize(rend, "img_src/armor/armor4.png"); 
    armor.queryTexture();
    armor.defineSize(3 * TILES_TO_PIXELS, 3 * TILES_TO_PIXELS); // mismo tamaño que el pato

    hombro.initialize(rend, "img_src/armor/hombro4.png");
    hombro.queryTexture();
    hombro.defineSize(3 * TILES_TO_PIXELS, 3 * TILES_TO_PIXELS); //mismo tamaño q el pato
}

void Map::makeTile(TileType tileType) {
    Image* tile = new Image();
    std::string path = "img_src/tiles/dayTiles/"; // esto dsp se cambia a aceptar el tipo de tile q me mande el server (dia, noche)
    path += tileType_to_string(tileType);
    tile->initialize(rend, path);
    tile->queryTexture();
    tile->defineSize(1 * TILES_TO_PIXELS, 1 * TILES_TO_PIXELS);
    tile->position(0, 0);
    tilesImages[int(tileType)] = tile;
}

// ----------------- Make Map -----------------

void Map::makeMap(int columnas, int filas, std::vector<uint16_t> mapa) {
    
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
            case 5: // piso
                matriz[filaActual][columnaActual] = i;
                if (matriz[filaActual-1][columnaActual] == i) {
                    tilesPlace[tilesImages[int(TileType::ROCK)]].push_back(std::pair(columnaActual * TILES_TO_PIXELS, filaActual * TILES_TO_PIXELS));
                } else {
                    tilesPlace[tilesImages[int(TileType::GRASS)]].push_back(std::pair(columnaActual * TILES_TO_PIXELS, filaActual * TILES_TO_PIXELS));
                }
                break;
            case 6: // pared
                matriz[filaActual][columnaActual] = i; // este proximamente va a servir para cuando las columnas tengan tope inferior
                tilesPlace[tilesImages[int(TileType::COLUMN)]].push_back(std::pair(columnaActual * TILES_TO_PIXELS, filaActual * TILES_TO_PIXELS));
                break;
            case 13: // caja                
            case 14: // caja rota
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
    player->defineSize(3 * TILES_TO_PIXELS, 3 * TILES_TO_PIXELS);
    player->update(columnaActual * TILES_TO_PIXELS, filaActual * TILES_TO_PIXELS,
                   DuckState::STANDING, RIGHT);
    player->armor(&armor, &hombro);
    player->weapon(weapons[Weapon::MAGNUM]);
    player->helmet(helmets[int(Helemts::TINFOIL)]);
    players[name] = player;
    playersNamesAlive.push_back(name);
}

void Map::remove(std::string playerName) {
    playersNamesAlive.remove(playerName);
}

void Map::update(std::string player, int x, int y, DuckState state, Side side) {
    if (std::find(playersNamesAlive.begin(), playersNamesAlive.end(), player) == playersNamesAlive.end()) {
        players[player]->dropEverithing();
        playersNamesAlive.push_back(player);
    }
    players[player]->update(x * TILES_TO_PIXELS, y * TILES_TO_PIXELS, state, side);
}

// ----------------- Weapon -----------------

void Map::newWeapon(int x, int y, Weapon weapon) {
    weaponsMap[weapon].push_back(std::pair(x * TILES_TO_PIXELS, y * TILES_TO_PIXELS));
}

void Map::weaponPlayer(Weapon weapon, std::string playerName) {
    // Si el jugador ya tiene un arma, entonces dispara
    players[playerName]->weapon(weapons[weapon]);
}

void Map::dropWeapon(std::string playerName) {
    players[playerName]->dropWeapon();
}

// ----------------- Helmet -----------------

void Map::newHelmet(int x, int y, Helemts newHelmet) {
    helmetsMap[helmets[int(newHelmet)]].push_back(std::pair(x * TILES_TO_PIXELS, y * TILES_TO_PIXELS));
}

void Map::helmetPlayer(Helemts helmet, std::string playerName) {
    players[playerName]->helmet(helmets[int(helmet)]);
}

// ----------------- Armor -----------------

void Map::newArmor(int x, int y) {
    armorMap.push_back(std::pair(x * TILES_TO_PIXELS, y * TILES_TO_PIXELS));
}

void Map::armorPlayer(std::string playerName) {
    players[playerName]->armor(&armor, &hombro);
}

// ----------------- Fill -----------------

void Map::fill() { // Dibuja de atras para adelante

    background.fill(true);

    for(const auto& tilePair: tilesPlace) {
        if (tilePair.first != nullptr) {
            for (const auto& pair: tilePair.second) {
                tilePair.first->position(pair.first, pair.second);
                tilePair.first->fill();
            }
        }
    }

    for (const auto& pair : helmetsMap) {
        for (const auto& helmet: pair.second) {
            pair.first->position(helmet.first, helmet.second);
            pair.first->fill();
        }
    }

    for (std::pair armorPos: armorMap) {
        armorOnMap.position(armorPos.first, armorPos.second);
        armorOnMap.fill();
    }
    
    for (const auto& pair : weaponsMap) {
        for (const auto& weapon: pair.second) {
            weapons[pair.first]->position(weapon.first, weapon.second);
            weapons[pair.first]->fill();
        }
    }

    for (std::string playerName: playersNamesAlive) {
        players[playerName]->fill();
    }
}

// ----------------- Destructor -----------------

Map::~Map() {
    for (Image* piso: tilesImages) {
        delete piso;
    }

    for (const auto& pair : weapons) {
        delete pair.second;
    }

    for (Image* helmet: helmets) {
        delete helmet;
    }

    for (const auto& pair : helmetsMap) {
        delete pair.first;
    }

    for (const auto& pair : players) {
        delete pair.second;
    }
}

