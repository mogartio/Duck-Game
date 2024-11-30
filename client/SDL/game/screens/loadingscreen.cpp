#include "loadingscreen.h"

#include <iostream>


#define RADIUS 70

LoadingScreen::LoadingScreen(SDL_Renderer* renderer, int width, int height): renderer(renderer) {
    // Crear la fuente y la textura
    TTF_Font* font = TTF_OpenFont("assets/game_assets/font/Bokor-Regular.ttf", 56);

    // Si no se pudo cargar la fuente, lanzar una excepción
    if (!font) {
        throw std::runtime_error("Error al cargar la fuente: " + std::string(TTF_GetError()));
    }

    // Crear la superficie con el mensaje "Cargando..."
    SDL_Surface* surface = TTF_RenderText_Solid(font, "Cargando...", {255, 255, 255, 255});
    // Si no se pudo crear la superficie, lanzar una excepción
    if (!surface) {
        throw std::runtime_error("Error al crear la superficie: " + std::string(TTF_GetError()));
    }
    int position_x = width / 2 - surface->w / 2;
    int position_y = (height / 2 - RADIUS) - surface->h;
    ubication = {position_x, position_y, surface->w, surface->h};

    // Crear la textura a partir de la superficie
    textura_texto = SDL_CreateTextureFromSurface(renderer, surface);
    // Liberar la superficie
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    // Si no se pudo crear la textura, lanzar una excepción
    if (!textura_texto) {
        throw std::runtime_error("Error al crear la textura: " + std::string(SDL_GetError()));
    }

    // Cargar la imagen de la pantalla de carga
    surface = IMG_Load("assets/game_assets/background/99bf80c0-14b1-4b73-ba9f-065bc5046a51.png");
    if (!surface) {
        throw std::runtime_error("Error al cargar la imagen: " + std::string(IMG_GetError()));
    }

    // Crear una textura desde la superficie
    backgroundImage = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);  // Liberar la superficie después de crear la textura

    if (!backgroundImage) {
        throw std::runtime_error("Error al crear la textura: " + std::string(SDL_GetError()));
    }

    // Crear la textura principal
    mainTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                                    width, height);
}

void LoadingScreen::renderText() {
    // Renderiza un mensaje de "Cargando..."
    SDL_RenderCopy(renderer, textura_texto, nullptr, &ubication);
}

void LoadingScreen::renderLoadingCircle(float startAngle, float sweepAngle, int grosorminimo,
                                        int grosormaximo) {
    int radius = RADIUS;                         // Radio del círculo
    int x = ubication.x + ubication.w / 2;       // Posición x del centro del círculo
    int y = ubication.y + RADIUS + ubication.h;  // Posición y del centro del círculo
    const int segments = 200;                    // Número de líneas para aproximar el arco
    float angleStep = sweepAngle / segments;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Blanco

    for (int i = 0; i < segments; i++) {
        // Ángulos de los puntos actuales y siguientes
        float angle1 = startAngle + i * angleStep;
        float angle2 = startAngle + (i + 1) * angleStep;

        // Calcular grosor dinámico (interpolación lineal entre minThickness y maxThickness)
        float progress = (float)i / segments;  // Va de 0.0 a 1.0 a lo largo del arco
        int currentThickness = grosorminimo + progress * (grosormaximo - grosorminimo);

        for (int t = -currentThickness / 2; t <= currentThickness / 2; t++) {
            int adjustedRadius = radius + t;

            int x1 = x + adjustedRadius * cos(angle1);
            int y1 = y + adjustedRadius * sin(angle1);
            int x2 = x + adjustedRadius * cos(angle2);
            int y2 = y + adjustedRadius * sin(angle2);

            SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        }

        // Dibujar las puntas redondeadas en los extremos
        if (i == 0) {  // Extremo inicial
            renderFilledCircle(x + radius * cos(angle1), y + radius * sin(angle1),
                               currentThickness / 2);
        }
        if (i == segments - 1) {  // Extremo final
            renderFilledCircle(x + radius * cos(angle2), y + radius * sin(angle2),
                               currentThickness / 2);
        }
    }
}

void LoadingScreen::renderFilledCircle(int x, int y, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;  // Distancia x al centro
            int dy = radius - h;  // Distancia y al centro
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void LoadingScreen::show(Uint32 durationMs) {
    Uint32 startTime = SDL_GetTicks();  // Registrar el inicio
    float startAngle = 0.0f;            // Ángulo inicial del círculo de carga
    float rotationSpeed = 0.05f;        // Velocidad de rotación del círculo

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

        startAngle += rotationSpeed;  // Rotar el círculo

        // Renderizar el círculo de carga
        renderLoadingCircle(startAngle, 4 * M_PI / 3, 1, 15);

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

void LoadingScreen::renderWithOpacity(SDL_Texture* texture, float alpha) {
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

// Función para realizar un fade in de una textura
void LoadingScreen::fadeIn(SDL_Texture* texture, Uint32 duration) {
    // Inicializo el tiempo inicio y fin
    Uint32 start = SDL_GetTicks();
    Uint32 end = start + duration;
    // Inicializo la opacidad en 0 osea que no es visible nada
    float alpha = 0.0f;

    // Animación de fade-in
    while (SDL_GetTicks() < end) {
        alpha = 255.0f * (float)(SDL_GetTicks() - start) / duration;
        renderWithOpacity(texture, alpha);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);  // ~60 FPS
    }
}

// Función para realizar un fade out de una textura
void LoadingScreen::fadeOut(SDL_Texture* texture, Uint32 duration) {
    // Inicializo el tiempo de inicio y fin
    Uint32 start = SDL_GetTicks();
    Uint32 end = start + duration;
    // Inicializo la opacidad en 255 osea completamente visible
    float alpha = 255.0f;

    // Animación de fade-out
    while (SDL_GetTicks() < end) {
        alpha = 255.0f - 255.0f * (float)(SDL_GetTicks() - start) / duration;
        renderWithOpacity(texture, alpha);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);  // ~60 FPS
    }
}

LoadingScreen::~LoadingScreen() {
    SDL_DestroyTexture(textura_texto);
    SDL_DestroyTexture(mainTexture);
    SDL_DestroyTexture(backgroundImage);
}
