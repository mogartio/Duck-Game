#include "map.h"

#include <iostream>

#define TILES_TO_PIXELS 16

Map::Map(SDL_Renderer* rend, std::vector<uint16_t> mapa, uint tiles):
        rend(rend), mapa(mapa), tiles(tiles), tilesImages(3, nullptr) {
    // Deberia llegarme la info del fondo
    background.initialize(rend, "img_src/background/day.png");

    for (int i = int(TileType::COLUMN); i <= int(TileType::ROCK); i++) {
        TileType tileType = static_cast<TileType>(i);
        makeTile(tileType);
    }
}

void Map::makeTile(TileType tileType) {
    Image* tile = new Image();
    switch (tileType) {
        case GRASS:
            tile->initialize(rend, "img_src/tiles/dayTiles/grass.png");
            break;
        case ROCK:
            tile->initialize(rend, "img_src/tiles/dayTiles/rock.png");
            break;
        case COLUMN:
            tile->initialize(rend, "img_src/tiles/dayTiles/column.png");
            break;
        default:
            tile->initialize(rend, "img_src/tiles/dayTiles/middle.png");
    }
    tile->queryTexture();
    tile->defineSize(1 * tiles, 1 * tiles);
    tile->position(0, 0);
    tilesImages[int(tileType)] = tile;
}

SDL_Rect Map::adjustMapZoom() {
    SDL_Rect zoomRect;
    int max_x = 0;
    int max_y = 0;
    int min_x = 0;
    int min_y = 0;
    for (const auto& pair: players) {
        std::pair<int, int> position = pair.second->getPosition();
        if (position.first > max_x) {
            max_x = position.first;
        }
        if (position.first < min_x || min_x == 0) {
            min_x = position.first;
        }
        if (position.second > max_y) {
            max_y = position.second;
        }
        if (position.second < min_y || min_y == 0) {
            min_y = position.second;
        }
    }

    int new_width = (max_x - min_x);
    int new_height = (max_y - min_y);

    zoomRect = {min_x, min_y, new_width, new_height};
    return zoomRect;
}

void Map::addPlayer(int columnaActual, int filaActual, int color, std::string name) {
    Player* player = new Player(rend, Color(color));
    player->defineSize(3 * tiles, 3 * tiles);
    player->update(columnaActual * tiles, filaActual * tiles, DuckState::STANDING, RIGHT);
    players[name] = player;
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
                    tilesPlace[ROCK].push_back(std::pair(columnaActual, filaActual));
                } else {
                    tilesPlace[GRASS].push_back(std::pair(columnaActual, filaActual));
                }
                break;
            case 6:                                     // pared
                matriz[filaActual][columnaActual] = i;  // este proximamente va a servir para cuando
                                                        // las columnas tengan tope inferior
                tilesPlace[COLUMN].push_back(std::pair(columnaActual, filaActual));
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

void Map::update(std::string player, int x, int y, DuckState state, Side side) {
    players[player]->update(x * tiles, y * tiles, state, side);
}

void Map::newWeapon(/*int x, int y*/) {}

void Map::fill() {  // Dibuja de atras para adelante

    background.fill(true);

    for (const auto& tilePair: tilesPlace) {
        if (tilesImages[int(tilePair.first)] != nullptr) {
            for (const auto& pair: tilePair.second) {
                tilesImages[int(tilePair.first)]->position(pair.first * tiles, pair.second * tiles);
                tilesImages[int(tilePair.first)]->fill();
            }
        }
    }

    /*
    for (Weapon weapon: weapons) {
        weapon.fill();
    }
    */

    for (const auto& pair: players) {
        pair.second->fill();
    }
}

Map::~Map() {
    for (Image* piso: tilesImages) {
        delete piso;
    }

    for (const auto& pair: players) {
        delete pair.second;
    }
}
