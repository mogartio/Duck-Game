#include <SDL2/SDL_timer.h>


#include "frontOnePlaye.h"

#define TILES_TO_PIXELS 10

enum Front_event {
    MOVE_LEFT,
    MOVE_RIGHT,
    JUMP_EVENT,
    PLAY_DEAD,
    END
};

OnePlayer::OnePlayer(Queue<GenericMsg*>& queueSend, Queue<GenericMsg*>& queueRecive, std::string playerName): 
                    queueSend(queueSend), queueRecive(queueRecive), playerName(playerName) {}

void OnePlayer::play() {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return;
    }
    
    // GenericMsg* matriz = queueRecive.pop();
    // std::vector<uint16_t> mapa;
    // uint16_t filas;
    // uint16_t columnas;
    // if (matriz->get_header() == GenericMsg::MsgTypeHeader::SEND_MAP_MSG) {
    //     SendMapMsg* map = dynamic_cast<SendMapMsg*>(matriz);
    //     mapa = map->get_map();
    //     filas = map->get_filas();
    //     columnas = map->get_columnas();
    // } else if (matriz == nullptr) {
    //     throw("Algo anda mal! Mandaste un msj que nda que ver");
    // }

    // ------------ Codigo prueba --------------
    std::vector<uint16_t> mapa = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,0,0,0,5,5,5,5,0,0,0,0,0,0,0,0};
    uint16_t filas = 6;
    uint16_t columnas = 7;
    // ------------------------------------------

    Window win(columnas*TILES_TO_PIXELS, filas*TILES_TO_PIXELS);

    Map map(win.get_rend(), mapa, columnas, filas);
    map.makeMap(columnas, filas);

    const Uint32 frame_rate = 1000 / 40; // 30 FPS
    Uint32 last_frame_time = SDL_GetTicks(); // Tiempo del último frame

    bool close = false;

    while (!close) {
        Uint32 current_time = SDL_GetTicks();
        Uint32 elapsed_time = current_time - last_frame_time;

        SDL_Event event;

        // Procesa los eventos en la cola
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: 
                    close = true;
                    // queueSend.try_push(END);
                    break;
                case SDL_KEYDOWN: // Evento de tecla presionada
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_W: // Tecla W
                            // queueSend.try_push(JUMP_EVENT);
                            break;
                        case SDL_SCANCODE_S: // Tecla S
                            // queueSend.try_push(PLAY_DEAD);
                            break;
                        case SDL_SCANCODE_A: // Tecla A
                            // queueSend.try_push(MOVE_LEFT);
                            break;
                        case SDL_SCANCODE_D: // Tecla D
                            // queueSend.try_push(MOVE_RIGHT);
                            break;
                        default:
                            break; // Ignora otras teclas
                    }
                    break;

                case SDL_KEYUP: // Evento de tecla soltada
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_S: // Tecla S
                            // queueSend.try_push(PLAY_DEAD);
                            break;
                        case SDL_SCANCODE_A: // Tecla A
                            // queueSend.try_push(MOVE_LEFT);
                            break;                            
                        case SDL_SCANCODE_D: // Tecla D
                            // queueSend.try_push(MOVE_RIGHT);
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
        // int msj;
        // bool poped = queueRecive.try_pop(msj);

        // Actualiza Jugadores y armas
        // if (poped) {
        //     /* map.update()*/
        // }

        // Renderiza los objetos en la ventana
        if (elapsed_time >= frame_rate) {
            win.clear();
            map.fill();
            win.fill();
            last_frame_time = current_time;
        }

        // Controla la frecuencia de cuadros por segundo (FPS)
        SDL_Delay(frame_rate - (SDL_GetTicks() - current_time));
    }

}




