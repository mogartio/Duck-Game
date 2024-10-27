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
    Image* background;

public:
    Map(SDL_Renderer* rend, Queue<int>& queueRecive);

    void makeMap(int w, int h);
    void update(int player, int x, int y, DuckState state, Side side);
    void fill();

    ~Map() = default;
};
