#include "common/queue.h"
#include "image.h"
#include "player.h"

#include <list>
#include <SDL2/SDL_render.h>

class Map {
private:

    Queue<int>& queueRecive;
    SDL_Renderer* rend;

    std::list<Image> tiles;
    std::vector<Player> players;
    // std::vector<Weapon> weapons; // Tengo que crear un sistema de descarte de las armas vacias

    Image* background;

public:
    Map(SDL_Renderer* rend, Queue<int>& queueRecive);

    void makeMap(int w, int h);

    // Actualiza posicion y estado del jugador
    void update(int player, int x, int y, DuckState state, Side side);

    // Agrega un nuevo arma al mapa
    void newWeapon(int x, int y /*, Weapon newWeapon*/);

    // Dibuja el mapa, a los jugadores y las armas
    void fill();

    ~Map() = default;
};
