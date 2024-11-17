#include <QApplication>
#include <iostream>
#include "client.h"
#include "client_protocol.h"
#include "../client/menu/main_window.h"
#include "../common/queue.h"
#include "../common/messages/generic_msg.h"
#include "../client/menu/create_game_screen.h"
#include "../client/menu/connection_screen.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Queue<GenericMsg*>* send_queue = new Queue<GenericMsg*>(100);
    Queue<GenericMsg*>* recv_queue = new Queue<GenericMsg*>(100);

    Client* client = nullptr;

    MainWindow mainWindow(nullptr, send_queue, recv_queue, client);
    mainWindow.show();

    std::list<std::string> names;

    if (app.exec() == 0) {
        // se cerro ordenadamente y se tiene que iniciar el render del juego
        GenericMsg* msg = recv_queue->pop();
        if (msg->get_header() == GenericMsg::MsgTypeHeader::INFO_LOBBY_MSG) {
            InfoLobbyMsg* info_msg = dynamic_cast<InfoLobbyMsg*>(msg);
            for (auto& player: info_msg->get_players()) {
                names.push_back(player.nombre);
            }
        }
    }
    return 0;
}