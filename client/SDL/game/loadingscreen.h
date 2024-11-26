#include <cmath>
#include <stdexcept>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

// Clase para la pantalla de carga
class LoadingScreen {
private:
    SDL_Renderer* renderer;
    SDL_Rect ubication;
    SDL_Texture* textura_texto;
    SDL_Texture* backgroundImage;
    SDL_Texture* mainTexture;

    void renderText();

    void renderLoadingCircle(float startAngle, float sweepAngle, int grosorminimo,
                             int grosormaximo);

    void renderFilledCircle(int x, int y, int radius);

    void renderWithOpacity(SDL_Texture* texture, float alpha);

public:
    LoadingScreen(SDL_Renderer* renderer, int width, int height);

    void fadeIn(SDL_Texture* texture, Uint32 durationMs);

    void fadeOut(SDL_Texture* texture, Uint32 durationMs);

    void show(Uint32 durationMs);

    ~LoadingScreen();
};
