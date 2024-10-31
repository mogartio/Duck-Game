#include "map.h"
#include <iostream>

#define TILES_TO_PIXELS 10

Map::Map(SDL_Renderer* rend, std::vector<uint16_t> mapa, int w, int h): rend(rend), mapa(mapa) {
    // Deberia llegarme la info del fondo

    makeMap(w, h);
}

void Map::makeMap(int columnas, int filas) {
    
    Image tile(rend, "");
    Player player(rend, Color(0));
    int filaActual = 0;
    int columnaActual = 0;
    for (uint16_t i: mapa) {
        if (columnaActual%columnas == 0) {
            filaActual++;
        }
        switch (i) {
            case 1:
            case 2:
            case 3:
            case 4:
                //llega jugador
                // Necesito un sistema que si vuelve a aparecer el num 2 a 3 tiles de distancia de la actual lo saltee

                //aca determino que color es para conseguir el string q necesito
                player = Player(rend, Color(players.size()));
                player.defineSize(50, 50);
                //player.update(pos.x, pos.y, info.state, info.side);
                players.push_back(player);
                break;
            case 5: //piso
            case 6: //pared
                
                // DEFINIR que tamaño tienen los tiles

                //aca determino que tipo de tile es para conseguir el string q necesito
                tile = Image(rend, "../img_src/tiles/dayTiles/middle.png");
                tile.queryTexture();
                tile.defineSize(35, 35);
                tile.position(columnaActual*TILES_TO_PIXELS, filaActual*TILES_TO_PIXELS);
                tiles.push_back(tile);
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

void Map::fill() { // Dibuja de atras para adelante

    for (Image tile: tiles) {
        tile.fill();
    }

    /*
    for (Weapon weapon: weapons) {
        weapon.fill();
    }
    */

    for (Player player: players) {
        player.fill();
    }
}

