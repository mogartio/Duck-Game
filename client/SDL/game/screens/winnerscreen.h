#ifndef WINNER_SCREEN_H
#define WINNER_SCREEN_H
#include <cmath>
#include <stdexcept>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class WinnerScreen {
private:
    SDL_Renderer* rend;
    SDL_Texture* textura_texto;
    SDL_Texture* backgroundImage;
    SDL_Texture* mainTexture;
    SDL_Texture* winnerTexture;
    SDL_Texture* winnerWingTexture;
    SDL_Rect textUbi;
    SDL_Rect winnerUbi;

    int width;
    int height;

    void renderWithOpacity(SDL_Texture* texture, float alpha);

    void renderBackground();
    void renderText();
    void renderWinner();

    void makeText(std::string winner);
    void makeWinner(std::string winner);

public:
    WinnerScreen(SDL_Renderer* renderer, int width, int height);
    void show(std::pair<std::string, std::string> winner);

    ~WinnerScreen();
};
#endif
