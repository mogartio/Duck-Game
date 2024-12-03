#include <cmath>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

// Clase para la pantalla de puntos
class PointsScreen {
private:
    SDL_Renderer* renderer;
    std::unordered_map<SDL_Texture*, SDL_Rect> textures;
    SDL_Texture* backgroundImage;
    SDL_Texture* mainTexture;

    // SDL no toma los \n como saltos de línea
    std::vector<std::string> lines;

    int width;
    int height;

    void makeText(std::unordered_map<std::string, int> playersPoints);
    void renderText();
    void renderWithOpacity(SDL_Texture* texture, float alpha);

public:
    PointsScreen(SDL_Renderer* renderer, int width, int height);

    void show(Uint32 durationMs, std::unordered_map<std::string, int> playersPoints);

    ~PointsScreen();
};
