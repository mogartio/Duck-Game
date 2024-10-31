#include "game/frontOnePlaye.h"

#define MAX 1000

int main(int argc, char const* argv[]) {

    Queue<GenericMsg*> send(MAX);
    Queue<GenericMsg*> recv(MAX);

    OnePlayer game(send, recv, "pedro");
    game.play();
    return 0;
}

