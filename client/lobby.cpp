#include "lobby.h"

// estos events los voy a definir cuando empiece a armar el front
// son constantes globales
void Lobby::run() {

    while (!play) {

        // pseudocodigo que explica como funciona lobby
        auto mensaje = queueFrontSender.pop();
        // switch(mensaje[0]) {
        // case PLAY_EVENT:
        //     play = true;
        //     break;

        // case VIEW_LOBBIES_EVENT:
        //     LobbyAction msj(1, NULL, NULL);
        //     queueSender.push(&msj);
        //     auto lobbies = queueReciver.pop();
        //     queueFrontReciver.push(lobbies);
        //     break;

        // case CHOOSE_LOBBY_EVENT:
        //     LobbyAction msj(2, mensaje[1], mensaje[2]);
        //     queueSender.push(&msj);
        //     break;

        // case CREATE_LOBBY_ONE_LOCAL_PLAYER_EVENT:
        //     LobbyAction msj(3, mensaje[1]);
        //     queueSender.push(&msj);
        //     lobby_created = queueReciver.pop();
        //     if (lobby_created) {
        //         queueFrontReciver(ok?);
        //     }
        //     break;

        // case CUSTOMIZE_PLAYER_EVENT:
        //     CustomizePlayer msj(true, NULL, NULL);
        //     queueSender.push(&msj);
        //     auto colors = queueReciver.pop();
        //     queueFrontReciver.push(colors);
        //     break;

        // case PLAYER_CUSTOMIZED_EVENT:
        //     CustomizePlayer msj(false, mensaje[1], mensaje[2]);
        //     queueSender.push(&msj);
        //     break;

        // default:
        //     break;
        // }
    }
}
