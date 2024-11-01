#include "../../../common/queue.h"
#include "player.h"

#include <list>
#include <SDL2/SDL_render.h>

enum TileType {
    BORDE,
    MEDIO
};

class Map {
private:

    SDL_Renderer* rend;
    std::vector<uint16_t> mapa;

    std::list<Image*> tiles;
    std::vector<Player*> players;

    // std::vector<Weapon> weapons; // Tengo que crear un sistema de descarte de las armas vacias

    Image background;

    void makePlayer(int columnaActual, int filaActual, int color);
    void makeTile(int columnaActual, int filaActual /*, TileType tileType*/);


public:
    Map(SDL_Renderer* rend, std::vector<uint16_t> mapa);

    void makeMap(int w, int h);

    // Actualiza posicion y estado del jugador
    void update(int player, int x, int y, DuckState state, Side side);

    // Agrega un nuevo arma al mapa
    void newWeapon(/*int x, int y*/ /*, Weapon newWeapon*/);

    // Dibuja el mapa, a los jugadores y las armas
    void fill();

    ~Map();
};
