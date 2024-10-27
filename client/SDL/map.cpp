#include "map.h"

Map::Map(SDL_Renderer* rend, Queue<int>& queueRecive): rend(rend), queueRecive(queueRecive) {}

void Map::makeMap(int w, int h) {
    int back;
    queueRecive.try_pop(back);
    //aca hago que back se convierta en el string q necesito
    Image background(rend, "img_src/background/day.png");
    this->background = &background;

    Image tile(rend, "");
    Player player(rend, 0);
    for (int i = 0; i < (w*h); i++) {
        int pos;
        queueRecive.try_pop(pos);
        switch (pos) {
            case 1:
                //aca determino qu tipo de tile es para conseguir el string q necesito
                tile = Image(rend, "img_src/tiles/dayTiles/middle.png");
                tile.queryTexture();
                tile.defineSize(35, 35);
                //tile.position(pos.x, pos.y);
                tiles.push_back(tile);
                break;
            case 2:
                //aca determino qu tipo de tile es para conseguir el string q necesito
                player = Player(rend, players.size());
                player.defineSize(50, 50);
                //player.update(pos.x, pos.y, info.state, info.side);
                players.push_back(player);
                break;
            case 3:
                //proyectiles
            default:
                break;
        }

    }
}

void Map::update(int player, int x, int y, DuckState state, Side side) {
    players[player].update(x, y, state, side);
}

void Map::fill() {
    (*background).fill(true);
    for (Image tile: tiles) {
        tile.fill();
    }
    for (Player player: players) {
        player.fill();
    }
}

