#include "map.h"
#include <iostream>

#define TILES_TO_PIXELS 10

Map::Map(SDL_Renderer* rend, std::vector<uint16_t> mapa, int w, int h): rend(rend), mapa(mapa) {
    // Deberia llegarme la info del fondo
    background.initialize(rend, "img_src/background/day.png");
}

void Map::makeTile(int columnaActual, int filaActual, TileType tileType) {
    // tiles.emplace_back(rend, "img_src/tiles/dayTiles/middle.png");
    // Image& tile = tiles.back(); // Referencia al último elemento recién insertado

    // tile.queryTexture();
    // tile.defineSize(20, 20);
    // tile.position(columnaActual * TILES_TO_PIXELS, filaActual * TILES_TO_PIXELS);

}

void Map::makePlayer(int columnaActual, int filaActual, int color) {
    players.emplace_back(rend, Color(color));
    players[color].defineSize(50, 50);
    players[color].update(columnaActual*TILES_TO_PIXELS, filaActual*TILES_TO_PIXELS, DuckState::STANDING, RIGHT);
}

bool condicion(int i, int filaActual, int columnaActual, std::vector<std::vector<int>> *matriz) {
    bool a = ((*matriz)[filaActual-1][columnaActual] == i);
    bool b = ((*matriz)[filaActual][columnaActual-1] == i);
    bool c = ((*matriz)[filaActual-2][columnaActual] == i);
    bool d = ((*matriz)[filaActual][columnaActual-2] == i);
    return (a || b || c || d);
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
            case 1:
            case 2:
            case 3:
            case 4:
                //llega jugador
                // Necesito un sistema que si vuelve a aparecer el num 2 a 3 tiles de distancia de la actual lo saltee
                if (condicion(i, filaActual, columnaActual, &matriz)) {

                }
                //aca determino que color es para conseguir el string q necesito}
                matriz[filaActual][columnaActual] = i;
                makePlayer(columnaActual, filaActual, i-1);
                break;
            case 5: //piso
            case 6: //pared
                // if ((matriz[filaActual-1][columnaActual] == i) || (matriz[filaActual][columnaActual-1] == i) ) {
                //     break;
                // }
                // DEFINIR que tamaño tienen los tiles
                matriz[filaActual][columnaActual] = i;
                //aca determino que tipo de tile es para conseguir el string q necesito
                makeTile(columnaActual, filaActual, MEDIO);
                break;
            case 13: //caja                
            case 14: //caja rota
                break;
            default:
                break;
        }
        columnaActual++;
    }
}

void Map::update(int player, int x, int y, DuckState state, Side side) {
    players[player].update(x, y, state, side);
}

void Map::newWeapon(int x, int y) {

}

void Map::fill() { // Dibuja de atras para adelante

    background.fill(true);

    // for (auto& [type, tileVector] : tiles) {
    //     for (Image& tile : tileVector) {
    //         tile.fill();
    //     }
    // }
    for (Image* piso: tiles) {
        piso->fill();
    }
    /*
    for (Weapon weapon: weapons) {
        weapon.fill();
    }
    */

    for (Player& player: players) {
        player.fill();
    }
}

