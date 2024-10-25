#include "common/queue.h"
#include "image.h"

#include <list>
#include <SDL2/SDL_render.h>

class Map {
private:

    Queue<int>& queueRecive;
    SDL_Renderer* rend;

    std::list<Image> tiles;
    std::vector<Image> players;
    Image* background;

public:
    Map(SDL_Renderer* rend, Queue<int>& queueRecive);

    void makeMap(int w, int h);
    void updatePosition(int player, int x, int y);
    void updateImage(int player, std::string img);
    void fill();

    ~Map() = default;
};
