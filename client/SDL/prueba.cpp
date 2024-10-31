#include <SDL2/SDL.h>            // Incluye la biblioteca principal de SDL
#include <SDL2/SDL_image.h>      // Incluye la biblioteca para manejar imágenes
#include <SDL2/SDL_timer.h>      // Incluye la biblioteca para manejar temporizadores
#include <vector>

#include "game/player.h"

int main(int argc, char* argv[]) {
    // Inicializa todos los subsistemas de SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError()); // Imprime el error si la inicialización falla
        return 1; // Sale del programa con código de error
    }

    // Crea una ventana de 800x600 píxeles, centrada en la pantalla y redimensionable
    SDL_Window* win = SDL_CreateWindow("GAME",
                                       SDL_WINDOWPOS_CENTERED, // Posición X centrada
                                       SDL_WINDOWPOS_CENTERED, // Posición Y centrada
                                       800,                     // Ancho de la ventana
                                       600,                     // Alto de la ventana
                                       SDL_WINDOW_RESIZABLE);  // Permite que la ventana sea redimensionable

    // Configura las opciones del renderizador (aceleración por hardware)
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags); // Crea el renderizador asociado a la ventana

    // Carga la imagen de fondo
    Image background(rend, "img_src/background/day.png");

    Side side = RIGHT;

    Player grey(rend, GREY);
    grey.defineSize(50, 50);
    grey.update(250, 150, DuckState::STANDING, side);
    int destx = 250;
    int desty = 150; 

    //std::vector<Image> whiteWings = {Image(rend, "img_src/ducks/grey/wing/normal.png")};


    Image tex2(rend, "img_src/ducks/white/standing.png");
    tex2.queryTexture();
    tex2.defineSize(50, 50);
    tex2.position(250, 150);
    int dest2x = 350;
    int dest2y = 250; 

    Image whiteWing(rend, "img_src/ducks/white/wing/normal.png");
    whiteWing.queryTexture();
    whiteWing.defineSize(23, 23);
    whiteWing.position(250, 150);
    int destWing2x = dest2x - 12;
    int destWing2y = dest2y + 13; 

    // Variables de control del programa
    bool close = false; // Variable para controlar si se debe cerrar la ventana
    int speed = 200; // Velocidad de movimiento del objeto

    // Variables para controlar el movimiento en ambas direcciones
    int vel_x = 0; // Velocidad en la dirección X
    int vel_y = 0; // Velocidad en la dirección Y

    int vel_x2 = 0;
    int vel_y2 = 0;

    SDL_RendererFlip flip2 = SDL_FLIP_NONE;

    int offsetX = 10;

    const Uint32 frame_rate = 1000 / 40; // 40 FPS
    Uint32 last_frame_time = SDL_GetTicks(); // Tiempo del último frame

    // Bucle principal del programa
    while (!close) {
        Uint32 current_time = SDL_GetTicks();
        Uint32 elapsed_time = current_time - last_frame_time;

        SDL_Event event; // Estructura para manejar eventos

        // Procesa los eventos en la cola
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: // Evento de cerrar la ventana
                    close = true; // Establece la variable para cerrar el programa
                    break;

                case SDL_KEYDOWN: // Evento de tecla presionada
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_W: // Tecla W
                            vel_y2 = -speed / 30; // Mueve hacia arriba
                            break;
                        case SDL_SCANCODE_UP: // Flecha arriba
                            vel_y = -speed / 30; // Mueve hacia arriba
                            break;
                        case SDL_SCANCODE_S: // Tecla S
                            vel_y2 = speed / 30; // Mueve hacia abajo
                            break;
                        case SDL_SCANCODE_DOWN: // Flecha abajo
                            vel_y = speed / 30; // Mueve hacia abajo
                            break;
                        case SDL_SCANCODE_A: // Tecla A
                            vel_x2 = -speed / 30; // Mueve hacia la izquierda
                            flip2 = SDL_FLIP_HORIZONTAL;
                            break;
                        case SDL_SCANCODE_LEFT: // Flecha izquierda
                            vel_x = -speed / 30; // Mueve hacia la izquierda
                            side = LEFT;
                            break;
                        case SDL_SCANCODE_D: // Tecla D
                            vel_x2 = speed / 30; // Mueve hacia la derecha
                            flip2 = SDL_FLIP_NONE;
                            break;
                        case SDL_SCANCODE_RIGHT: // Flecha derecha
                            side = RIGHT;
                            vel_x = speed / 30; // Mueve hacia la derecha
                            break;
                        default:
                            break; // Ignora otras teclas
                    }
                    break;

                case SDL_KEYUP: // Evento de tecla soltada
                    // Detiene el movimiento cuando se sueltan las teclas
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_W: // Tecla W
                        case SDL_SCANCODE_S: // Tecla S
                            vel_y2 = 0; // Detiene el movimiento vertical
                            break;
                        case SDL_SCANCODE_UP: // Flecha arriba
                        case SDL_SCANCODE_DOWN: // Flecha abajo
                            vel_y = 0; // Detiene el movimiento vertical
                            break;
                        case SDL_SCANCODE_A: // Tecla A
                        case SDL_SCANCODE_D: // Tecla D
                            vel_x2 = 0; // Detiene el movimiento horizontal
                            break;
                        case SDL_SCANCODE_LEFT: // Flecha izquierda
                        case SDL_SCANCODE_RIGHT: // Flecha derecha
                            vel_x = 0; // Detiene el movimiento horizontal
                            break;
                        default:
                            break; // Ignora otras teclas
                    }
                    break;
            }
        }

        // Actualiza la posición del objeto basándose en su velocidad
        destx += vel_x; // Actualiza la posición X
        desty += vel_y; // Actualiza la posición Y
        grey.update(destx, desty, DuckState::STANDING, side);

        dest2x += vel_x2;
        dest2y += vel_y2;
        tex2.position(dest2x, dest2y);
        destWing2y += vel_y2;

        if (flip2 == SDL_FLIP_HORIZONTAL) {
            destWing2x = dest2x + 1.7*offsetX;
        } else {
            destWing2x = dest2x + offsetX;
        }

        whiteWing.position(destWing2x, destWing2y);

        if (elapsed_time >= frame_rate) {
            // Renderiza el objeto en la ventana
            SDL_RenderClear(rend); // Limpia la pantalla
            background.fill(true);
            grey.fill();
            tex2.fill(flip2);
            whiteWing.fill(flip2);
            SDL_RenderPresent(rend); // Muestra el renderizado en la ventana
        }

        if (close) {
            break;
        }
        // Controla la frecuencia de cuadros por segundo (FPS)
        SDL_Delay(frame_rate - (SDL_GetTicks() - current_time));
    }

    // Limpieza de recursos
    SDL_DestroyRenderer(rend); 
    SDL_DestroyWindow(win);
    SDL_Quit(); // Finaliza SDL

    return 0;
}

