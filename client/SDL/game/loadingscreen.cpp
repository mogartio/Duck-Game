#include "loadingscreen.h"

#define RADIUS 70

LoadingScreen::LoadingScreen(SDL_Renderer* renderer, int width, int height): renderer(renderer) {
    // Crear la fuente y la textura
    font = TTF_OpenFont("assets/game_assets/font/Bokor-Regular.ttf", 24);

    // Si no se pudo cargar la fuente, lanzar una excepción
    if (!font) {
        throw std::runtime_error("Error al cargar la fuente: " + std::string(TTF_GetError()));
    }

    // Crear la superficie con el mensaje "Cargando..."
    SDL_Surface* surface = TTF_RenderText_Solid(font, "Cargando...", {255, 255, 255, 255});
    int position_x = width / 2 - surface->w / 2;
    int position_y = (height / 2 - RADIUS) - surface->h;
    ubication = {position_x, position_y, surface->w, surface->h};
    // Si no se pudo crear la superficie, lanzar una excepción
    if (!surface) {
        throw std::runtime_error("Error al crear la superficie: " + std::string(TTF_GetError()));
    }

    // Crear la textura a partir de la superficie
    textura_texto = SDL_CreateTextureFromSurface(renderer, surface);
    // Liberar la superficie
    SDL_FreeSurface(surface);
    // Si no se pudo crear la textura, lanzar una excepción
    if (!textura_texto) {
        throw std::runtime_error("Error al crear la textura: " + std::string(SDL_GetError()));
    }
}

void LoadingScreen::renderText() {
    // Limpia la pantalla
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Negro
    SDL_RenderClear(renderer);

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

    while (true) {
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if (elapsedTime >= durationMs) {
            break;  // Salir después de que pase el tiempo
        }

        startAngle += rotationSpeed;  // Rotar el círculo

        // Renderizar contenido de la pantalla de carga
        renderText();

        // Renderizar el círculo de carga
        renderLoadingCircle(startAngle, 4 * M_PI / 3, 1, 15);

        // Presenta la pantalla
        SDL_RenderPresent(renderer);

        // Limitar el FPS
        SDL_Delay(16);  // Aproximadamente 60 FPS
    }
}

LoadingScreen::~LoadingScreen() {
    TTF_CloseFont(font);
    SDL_DestroyTexture(textura_texto);
}
