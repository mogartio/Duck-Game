#include <SDL2/SDL.h>
#include <string>

class Image {
private:

    SDL_Renderer* rend;
    SDL_Texture* imgTex;
    SDL_Rect dest;

public:
    Image() = default;
    Image(SDL_Renderer* rend, std::string img);

    // fill() para background e imagenes estaticas
    void fill(bool background = false);
    
    // fill(SDL_RendererFlip flip) para imagenes no estaticas
    void fill(SDL_RendererFlip flip);

    //Query the attributes of a texture.
    void queryTexture();

    void defineSize(int height, int width);
    void position(int x, int y);

    ~Image();
};


