#include "winnerscreen.h"
#include <iostream>


#define RADIUS 70

// ------------------------ Constructor ------------------------

WinnerScreen::WinnerScreen(SDL_Renderer* rend, int width, int height): rend(rend), width(width), height(height) {

    // Cargo la imagen de fondo
    backgroundImage = IMG_LoadTexture(rend, "assets/game_assets/background/winner.jpeg");
    if (backgroundImage == nullptr) {
        throw std::runtime_error("Error al cargar la imagen de fondo del ganador");
    }

    // Crear la textura principal
    mainTexture = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                                    width, height);

}


// ------------------------ Makes ------------------------

void WinnerScreen::makeText(std::string winner) {
    std::string text;

    for (char& c : winner) {
        text += std::toupper(static_cast<unsigned char>(c));
    }

    text += " WINS!!!";

    TTF_Font* font = TTF_OpenFont("assets/game_assets/font/Bokor-Regular.ttf", 100);
    if (!font) {
        throw std::runtime_error("Error al cargar la fuente");
    }

    SDL_Color color = {0, 0, 0, 0};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        throw std::runtime_error("Error al renderizar el texto");
    }

    int position_x = width / 2 - (surface->w * 5 / 12);
    int position_y = (height / 5) - surface->h;
    textUbi = {position_x, position_y, surface->w, surface->h};

    textura_texto = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}

void WinnerScreen::makeWinner(std::string winner) {
    std::string duck = winner + "standingWopenMouth.png";
    std::string wing = winner + "wing/flapUp.png";

    winnerTexture = IMG_LoadTexture(rend, duck.c_str());
    winnerWingTexture = IMG_LoadTexture(rend, wing.c_str());

    if (!winnerTexture || !winnerWingTexture) {
        std::cout << std::string(SDL_GetError()) << std::endl;
        throw std::runtime_error("Error al cargar la textura del ganador");
    }

    SDL_QueryTexture(winnerTexture, NULL, NULL, &winnerUbi.w, &winnerUbi.h);
    SDL_QueryTexture(winnerWingTexture, NULL, NULL, &winnerUbi.w, &winnerUbi.h);

    winnerUbi.w = width / 5;
    winnerUbi.h = winnerUbi.w;

    winnerUbi.x = width / 2 - (winnerUbi.w * 5 / 12);
    winnerUbi.y = height / 3 - winnerUbi.h / 3;

}

// ------------------------ Render ------------------------

void WinnerScreen::renderWithOpacity(SDL_Texture* texture, float alpha) {
    // Configurar para renderizar con opacidad
    SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);  // Establecer el color

    SDL_SetTextureAlphaMod(texture, (Uint8)alpha);  // Modifica la opacidad
    SDL_RenderClear(rend);                      // Limpia la pantalla
    SDL_RenderCopy(rend, texture, NULL, NULL);  // Renderiza la textura

    SDL_SetTextureAlphaMod(texture,
                           255);  // Asegura que la textura esté completamente visible nuevamente
    SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_NONE);  // Restablece el modo de mezcla
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
}

void WinnerScreen::renderBackground() {
    SDL_RenderCopy(rend, backgroundImage, NULL, NULL);
}

void WinnerScreen::renderText() {
    SDL_RenderCopy(rend, textura_texto, nullptr, &textUbi);
}

void WinnerScreen::renderWinner() {
    SDL_RenderCopy(rend, winnerTexture, nullptr, &winnerUbi);
    SDL_RenderCopy(rend, winnerWingTexture, nullptr, &winnerUbi);
}

// ------------------------ Show ------------------------

void WinnerScreen::show(std::pair<std::string, std::string> winner) {
    makeText(winner.first);
    makeWinner(winner.second);

    Uint32 durationMs = 3000;

    Uint32 startTime = SDL_GetTicks();  // Registrar el inicio

    // Variables para el fadein y fadeout
    Uint32 finishtimeFadeIn = durationMs / 4;
    float alphaFadeIn = 0.0f;

    while (true) {
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if (elapsedTime >= durationMs) {
            break;  // Salir después de que pase el tiempo
        }

        // Limpiar la pantalla
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);

        SDL_SetRenderTarget(rend,
                            mainTexture);  // Cambiar el render target a la textura principal

        // Limpia la pantalla de la textura principal
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);  // Negro
        SDL_RenderClear(rend);

        // Renderizar la imagen de fondo
        renderBackground();

        renderWinner();

        // Renderizar el texto de la pantalla de carga y la limpia
        renderText();

        SDL_SetRenderTarget(rend, nullptr);  // Restablecer el render target

        if (elapsedTime < finishtimeFadeIn) {
                alphaFadeIn = 255.0f * (float)elapsedTime / finishtimeFadeIn;
                renderWithOpacity(mainTexture, alphaFadeIn);
        } else {
            SDL_RenderCopy(rend, mainTexture, nullptr, nullptr);
        }
        

        // Presenta la pantalla
        SDL_RenderPresent(rend);

        // Limitar el FPS
        SDL_Delay(16);  // Aproximadamente 60 FPS
    }


    bool running = true;
    
    while (running) {
        SDL_Event event;
        if (SDL_WaitEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            }
        }
    }
    

}

// ------------------- Destructor ----------------------

WinnerScreen::~WinnerScreen() {
    SDL_DestroyTexture(textura_texto);
    SDL_DestroyTexture(backgroundImage);
}

