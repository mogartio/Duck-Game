#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>


class Window {
private:

    SDL_Window* win;
    SDL_Renderer* rend;
    
public:
    Window(int w, int h);

    SDL_Renderer* get_rend();
    void clear();
    void fill();

    ~Window();
};


