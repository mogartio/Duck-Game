#include "map.h"

#include <iostream>

#define TILES_TO_PIXELS 16

Map::Map(SDL_Renderer* rend, std::vector<uint16_t> mapa): rend(rend), mapa(mapa), tilesImages(3, nullptr) {
    // Deberia llegarme la info del fondo
    background.initialize(rend, "img_src/background/day.png");

    armor.initialize(rend, "img_src/armor/armor.png"); 

    for (int i = int(TileType::COLUMN); i <= int(TileType::ROCK); i++) {
        TileType tileType = static_cast<TileType>(i);
        makeTile(tileType);
    }
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

void Map::addPlayer(int columnaActual, int filaActual, int color, std::string name) {
    Player* player = new Player(rend, Color(color));
    player->defineSize(3 * TILES_TO_PIXELS, 3 * TILES_TO_PIXELS);
    player->update(columnaActual * TILES_TO_PIXELS, filaActual * TILES_TO_PIXELS,
                   DuckState::STANDING, RIGHT);
    players[name] = player;
}

void Map::makeMap(int columnas, int filas) {
    
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
                    tilesPlace[tilesImages[int(TileType::ROCK)]].push_back(std::pair(columnaActual, filaActual));
                } else {
                    tilesPlace[tilesImages[int(TileType::GRASS)]].push_back(std::pair(columnaActual, filaActual));
                }
                break;
            case 6: // pared
                matriz[filaActual][columnaActual] = i; // este proximamente va a servir para cuando las columnas tengan tope inferior
                tilesPlace[tilesImages[int(TileType::COLUMN)]].push_back(std::pair(columnaActual, filaActual));
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

void Map::update(std::string player, int x, int y, DuckState state, Side side) {
    players[player]->update(x * TILES_TO_PIXELS, y * TILES_TO_PIXELS, state, side);
}

void Map::newWeapon(/*int x, int y*/) {

}

void Map::fill() { // Dibuja de atras para adelante

    background.fill(true);

    for(const auto& tilePair: tilesPlace) {
        if (tilePair.first != nullptr) {
            for (const auto& pair: tilePair.second) {
                tilePair.first->position(pair.first * TILES_TO_PIXELS, pair.second * TILES_TO_PIXELS);
                tilePair.first->fill();
            }
        }
    }
    
    /*
    for (Weapon weapon: weapons) {
        weapon.fill();
    }
    */

    for (const auto& pair : players) {
        pair.second->fill();
    }
}

Map::~Map() {
    for (Image* piso: tilesImages) {
        delete piso;
    }

    for (const auto& pair : players) {
        delete pair.second;
    }
}

