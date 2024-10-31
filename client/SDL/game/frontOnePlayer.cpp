#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "image.h"
#include "map.h"
#include "frontOnePlaye.h"

#define TILES_TO_PIXELS 10

enum Front_event {
    MOVE_LEFT,
    MOVE_RIGHT,
    JUMP_EVENT,
    PLAY_DEAD,
    END
};

OnePlayer::OnePlayer(Queue<Front_event>& queueSend, Queue<int>& queueRecive, std::string playerName): 
                    queueSend(queueSend), queueRecive(queueRecive), playerName(playerName) {}

void OnePlayer::play() {

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

    Map map(rend, queueRecive);

    const Uint32 frame_rate = 1000 / 30; // 30 FPS
    Uint32 last_frame_time = SDL_GetTicks(); // Tiempo del último frame

    bool close = false;

    Uint32 current_time;
    Uint32 elapsed_time;
    while (!close) {
        current_time = SDL_GetTicks();
        elapsed_time = current_time - last_frame_time;

        SDL_Event event;

        // Procesa los eventos en la cola
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: 
                    close = true;
                    queueSend.try_push(END);
                    break;
                case SDL_KEYDOWN: // Evento de tecla presionada
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_W: // Tecla W
                            queueSend.try_push(JUMP_EVENT);
                            break;
                        case SDL_SCANCODE_S: // Tecla S
                            queueSend.try_push(PLAY_DEAD);
                            break;
                        case SDL_SCANCODE_A: // Tecla A
                            queueSend.try_push(MOVE_LEFT);
                            break;
                        case SDL_SCANCODE_D: // Tecla D
                            queueSend.try_push(MOVE_RIGHT);
                            break;
                        default:
                            break; // Ignora otras teclas
                    }
                    break;

                case SDL_KEYUP: // Evento de tecla soltada
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_S: // Tecla S
                            queueSend.try_push(PLAY_DEAD);
                            break;
                        case SDL_SCANCODE_A: // Tecla A
                            queueSend.try_push(MOVE_LEFT);
                            break;                            
                        case SDL_SCANCODE_D: // Tecla D
                            queueSend.try_push(MOVE_RIGHT);
                            break;
                        default:
                            break; // Ignora otras teclas
                    }
                    break;
                default:
                    break;
            }
        }

        // DEBERIA fijarme si popeo de a uno o varios de una
        int msj;
        bool poped = queueRecive.try_pop(msj);

        // Actualiza Jugadores y armas
        if (poped) {
            /* map.update()*/
        }

        // Renderiza los objetos en la ventana
        if (elapsed_time >= frame_rate) {
            SDL_RenderClear(rend); // Limpia la pantalla
            map.fill();
            SDL_RenderPresent(rend); // Muestra el renderizado en la ventana
            last_frame_time = current_time;
        }

        // Controla la frecuencia de cuadros por segundo (FPS)
        SDL_Delay(frame_rate - (SDL_GetTicks() - current_time));
    }

    // Libera de recursos
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

}




