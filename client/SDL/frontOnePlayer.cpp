#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "image.h"
#include "frontOnePlaye.h"

#define TILES_TO_PIXELS 10

enum Front_event {
    MOVE_LEFT_START,
    MOVE_LEFT_STOP,
    MOVE_RIGHT_START,
    MOVE_RIGHT_STOP,
    JUMP,
    PLAY_DEAD_START,
    PLAY_DEAD_STOP,
    END
};

OnePlayer::OnePlayer(Queue<Front_event>& queueSend, Queue<int>& queueRecive): 
                    queueSend(queueSend), queueRecive(queueRecive) {}

void OnePlayer::run() {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return;
    }

    int rows = queueRecive.pop();
    int w = rows*TILES_TO_PIXELS;
    int columns = queueRecive.pop();
    int h = columns*TILES_TO_PIXELS;

    // Crea una ventana
    SDL_Window* win = SDL_CreateWindow("DUCK GAME",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       w,                     // Ancho de la ventana
                                       h,                     // Alto de la ventana
                                       NULL);

    // Configura las opciones del renderizador (aceleración por hardware)
    // TODO: A chequear los flags
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    // -------------------- Map --------------------
    Map map(rend, queueRecive);

    //int speed = 200; // Velocidad de movimiento del objeto

    while (_keep_running) {
        SDL_Event event;

        // Procesa los eventos en la cola
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: 
                    _keep_running = false;
                    break;
                case SDL_KEYDOWN: // Evento de tecla presionada
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_W: // Tecla W
                            queueSend.try_push(JUMP);
                            break;
                        case SDL_SCANCODE_S: // Tecla S
                            queueSend.try_push(PLAY_DEAD_START);
                            break;
                        case SDL_SCANCODE_A: // Tecla A
                            queueSend.try_push(MOVE_LEFT_START);
                            break;
                        case SDL_SCANCODE_D: // Tecla D
                            queueSend.try_push(MOVE_RIGHT_START);
                            break;
                        default:
                            break; // Ignora otras teclas
                    }
                    break;

                case SDL_KEYUP: // Evento de tecla soltada
                    // Detiene el movimiento cuando se sueltan las teclas
                    switch (event.key.keysym.scancode) {
                        // case SDL_SCANCODE_W: // Tecla W
                        case SDL_SCANCODE_S: // Tecla S
                            queueSend.try_push(PLAY_DEAD_STOP);
                            break;
                        case SDL_SCANCODE_A: // Tecla A
                            queueSend.try_push(MOVE_LEFT_STOP);
                            break;                            
                        case SDL_SCANCODE_D: // Tecla D
                            queueSend.try_push(MOVE_RIGHT_STOP);
                            break;
                        default:
                            break; // Ignora otras teclas
                    }
                    break;
                default:
                    break;
            }
        }

        int msj;
        bool poped = queueRecive.try_pop(msj);

        if (poped) {
            //calculo el defasaje y me fijo si actualizo o salto directamente al sig
            map.updatePosition(msj, msj, msj);
            map.updateImage(msj, std::to_string(msj));
        }

        // Renderiza los objetos en la ventana
        SDL_RenderClear(rend); // Limpia la pantalla
        map.fill();
        SDL_RenderPresent(rend); // Muestra el renderizado en la ventana

        // Controla la frecuencia de cuadros por segundo (FPS)
        SDL_Delay(1000 / 60); // Espera para mantener 60 FPS
    }

    // Libera de recursos
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

}




