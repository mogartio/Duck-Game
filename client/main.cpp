#include <QApplication>
#include <iostream>
#include "client.h"
#include "client_protocol.h"
#include "../client/menu/main_window.h"
#include "../common/queue.h"
#include "../common/messages/generic_msg.h"
#include "../client/menu/create_game_screen.h"
#include "../client/menu/connection_screen.h"
#include "SDL/game/game.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Queue<std::shared_ptr<GenericMsg>> send_queue(100);
    Queue<std::shared_ptr<GenericMsg>> recv_queue(100);

    Client* client = nullptr;

    std::list<std::string>* local_players = new std::list<std::string>();

    MainWindow mainWindow(nullptr, &send_queue, &recv_queue, client, local_players);
    mainWindow.show();


    if (app.exec() == 0) {
        if (local_players->size() == 0) {
            recv_queue.close();
            send_queue.close();
            delete local_players;
            delete client;
            return 0;
        }
    } else {
        return 1;
    }

    local_players->push_back("");

    std::string first_player = local_players->front();
    local_players->pop_front();
    Game game(send_queue, recv_queue, first_player, local_players->front());
    game.play();
    recv_queue.close();
    send_queue.close();
    delete local_players;
    return 0;
}