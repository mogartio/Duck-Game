#include "game.h"

//estos events los voy a definir cuando empiece a armar el front
//son constantes globales
void Game::play() {

    while(playing) {
        std::string map;
        bool poped = queueReciver.try_pop(std::ref(map));
        if (poped) {
            queueFrontReciver.try_push(map);
        }

        //pseudocodigo que explica como funciona lobby
        auto mensaje = queueFrontSender.pop();
        switch(mensaje[0]) {
        case PICKUP_EVENT:
            KeyboardAction msj(1);
            queueSender.try_push(&msj);
            break;

        case MOVE_LEFT_EVENT:
            KeyboardAction msj(2);
            queueSender.push(&msj);
            break;
        
        case MOVE_RIGHT_EVENT:
            KeyboardAction msj(3);
            queueSender.push(&msj);
            break;

        case JUMP_EVENT:
            KeyboardAction msj(4, mensaje[1]);
            queueSender.push(&msj);
            break;

        case PLAY_DEAD_EVENT:
            KeyboardAction msj(5);
            queueSender.push(&msj);
            break;

        case SHOOT_EVENT:
            KeyboardAction msj(6);
            queueSender.push(&msj);
            break;

        default:
            break;
        }
    }


}



