#include "pointsscreen.h"

PointsScreen::PointsScreen(SDL_Renderer* renderer, int width, int height): renderer(renderer), width(width), height(height) {
    // Cargo la imagen de fondo
    backgroundImage = IMG_LoadTexture(renderer, "assets/game_assets/background/points.jpg");
    if (backgroundImage == nullptr) {
        throw std::runtime_error("Error al cargar la imagen de fondo de los puntos");
    }

    // Crear la textura principal
    mainTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                                    width, height);

}

void PointsScreen::makeText(std::unordered_map<std::string, int> playersPoints) {
    lines.push_back("Puntos");

    for (const auto& player : playersPoints) {
        lines.push_back(player.first + ": " + std::to_string(player.second));
    }

    TTF_Font* font = TTF_OpenFont("assets/game_assets/font/Bokor-Regular.ttf", 80);
    if (!font) {
        throw std::runtime_error("Error al cargar la fuente");
    }

    SDL_Color color = {255, 255, 255, 200};
    int y_offset = 0;

    for (const std::string& line : lines) {
        SDL_Surface* surface = TTF_RenderText_Solid(font, line.c_str(), color);
        if (!surface) {
            TTF_CloseFont(font);
            throw std::runtime_error("Error al renderizar el texto");
        }

        int position_x = width / 2 - surface->w / 2;
        int position_y = height / 2 - (surface->h * 3) + y_offset;

        SDL_Rect textRect = {position_x, position_y, surface->w, surface->h};
        SDL_Texture* lineTexture = SDL_CreateTextureFromSurface(renderer, surface);

        textures[lineTexture] = textRect;

        SDL_FreeSurface(surface);

        // Incrementa el offset vertical para la próxima línea
        y_offset += surface->h + (surface->h / 8);  // Espaciado entre líneas
    }

    TTF_CloseFont(font);
}

void PointsScreen::renderText() {
    for (const auto& text : textures) {
        SDL_RenderCopy(renderer, text.first, nullptr, &text.second);
    }
}

void PointsScreen::renderWithOpacity(SDL_Texture* texture, float alpha) {
    // Configurar para renderizar con opacidad
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Establecer el color

    SDL_SetTextureAlphaMod(texture, (Uint8)alpha);  // Modifica la opacidad
    SDL_RenderClear(renderer);                      // Limpia la pantalla
    SDL_RenderCopy(renderer, texture, NULL, NULL);  // Renderiza la textura

    SDL_SetTextureAlphaMod(texture,
                           255);  // Asegura que la textura esté completamente visible nuevamente
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);  // Restablece el modo de mezcla
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
}

void PointsScreen::show(Uint32 durationMs, std::unordered_map<std::string, int> playersPoints) {
    makeText(playersPoints);

    Uint32 startTime = SDL_GetTicks();  // Registrar el inicio

    // Variables para el fadein y fadeout
    Uint32 finishtimeFadeIn = durationMs / 4;
    Uint32 startedtimeFadeOut = (3 * durationMs) / 4;
    float alphaFadeIn = 0.0f;
    float alphaFadeOut = 255.0f;

    while (true) {
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if (elapsedTime >= durationMs) {
            break;  // Salir después de que pase el tiempo
        }

        // Limpiar la pantalla
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderTarget(renderer,
                            mainTexture);  // Cambiar el render target a la textura principal

        // Limpia la pantalla de la textura principal
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Negro
        SDL_RenderClear(renderer);

        // Renderizar la imagen de fondo
        SDL_RenderCopy(renderer, backgroundImage, nullptr, nullptr);

        // Renderizar el texto de la pantalla de carga y la limpia
        renderText();

        SDL_SetRenderTarget(renderer, nullptr);  // Restablecer el render target

        if (elapsedTime < finishtimeFadeIn) {
            alphaFadeIn = 255.0f * (float)elapsedTime / finishtimeFadeIn;
            renderWithOpacity(mainTexture, alphaFadeIn);
        } else if (elapsedTime > startedtimeFadeOut) {
            alphaFadeOut = 255.0f - 255.0f * (float)(elapsedTime - startedtimeFadeOut) /
                                            (durationMs - startedtimeFadeOut);
            renderWithOpacity(mainTexture, alphaFadeOut);
        } else {
            SDL_RenderCopy(renderer, mainTexture, nullptr, nullptr);
        }

        // Presenta la pantalla
        SDL_RenderPresent(renderer);

        // Limitar el FPS
        SDL_Delay(16);  // Aproximadamente 60 FPS
    }
}

PointsScreen::~PointsScreen() {
    SDL_DestroyTexture(backgroundImage);
    SDL_DestroyTexture(mainTexture);
    for (const auto& text : textures) {
        SDL_DestroyTexture(text.first);
    }

}


