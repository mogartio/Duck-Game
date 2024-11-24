#include <cmath>
#include <stdexcept>
#include <string>

#include <SDL.h>
#include <SDL2/SDL_ttf.h>

// Clase para la pantalla de carga
class LoadingScreen {
private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Rect ubication;
    SDL_Texture* textura_texto;

    void renderText();

    void renderLoadingCircle(float startAngle, float sweepAngle, int grosorminimo,
                             int grosormaximo);

    void renderFilledCircle(int x, int y, int radius);

public:
    LoadingScreen(SDL_Renderer* renderer, int width, int height);

    void show(Uint32 durationMs);

    ~LoadingScreen();
};
