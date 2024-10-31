#include "../../../common/queue.h"
#include "player.h"

#include <list>
#include <SDL2/SDL_render.h>

class Map {
private:

    SDL_Renderer* rend;
    std::vector<uint16_t> mapa;

    std::list<Image> tiles;
    std::vector<Player> players;
    // std::vector<Weapon> weapons; // Tengo que crear un sistema de descarte de las armas vacias

    // Image background;

    void makeMap(int w, int h);

public:
    Map(SDL_Renderer* rend, std::vector<uint16_t> mapa, int w, int h);

    

    // Actualiza posicion y estado del jugador
    void update(int player, int x, int y, DuckState state, Side side);

    // Agrega un nuevo arma al mapa
    void newWeapon(int x, int y /*, Weapon newWeapon*/);

    // Dibuja el mapa, a los jugadores y las armas
    void fill();

    ~Map() = default;
};
