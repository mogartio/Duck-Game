#include <list>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <SDL2/SDL_render.h>

#include "../../../common/queue.h"

#include "player.h"

enum TileType { COLUMN, GRASS, ROCK };

class Map {
private:
    SDL_Renderer* rend;
    std::vector<uint16_t> mapa;
    uint tiles;
    uint columnas;
    uint filas;

    std::vector<Image*> tilesImages;
    std::unordered_map<TileType, std::vector<std::pair<int, int>>> tilesPlace;
    std::unordered_map<std::string, Player*> players;
    SDL_Texture* mapTexture;
    bool updated;

    // std::vector<Weapon> weapons; // Tengo que crear un sistema de descarte de las armas vacias

    Image background;

    void makeTile(TileType tileType);

    SDL_Rect adjustMapZoom();

public:
    Map(SDL_Renderer* rend, std::vector<uint16_t> mapa, uint tiles);

    void makeMap(int w, int h);

    void addPlayer(int columnaActual, int filaActual, int color, std::string name);

    // Actualiza posicion y estado del jugador
    void update(std::string player, int x, int y, DuckState state, Side side);

    // Agrega un nuevo arma al mapa
    void newWeapon(/*int x, int y*/ /*, Weapon newWeapon*/);

    // Dibuja el mapa, a los jugadores y las armas
    void fill();

    ~Map();
};
