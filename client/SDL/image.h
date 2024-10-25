#include <SDL2/SDL.h>
#include <string>

class Image {
private:

    SDL_Renderer* rend;
    SDL_Texture* imgTex;
    SDL_Rect dest;

public:
    Image(SDL_Renderer* rend, std::string img);

    void fill(bool background = false);
    void queryTexture();
    void defineSize(int height, int width);
    void position(int x, int y);
    void updateImage(std::string img);

    ~Image();
};


