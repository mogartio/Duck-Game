#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Image {
private:

    SDL_Renderer* rend;
    std::string img;
    SDL_Texture* imgTex;

public:
    Image(SDL_Renderer* rend, std::string img);

    void fill(SDL_Rect* dest);

    ~Image();
};


