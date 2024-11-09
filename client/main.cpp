#include <QApplication>
#include <iostream>
#include "client.h"
#include "client_protocol.h"
#include "../client/menu/main_window.h"
#include "../client/menu/connection_screen.h"
#include "../common/queue.h"
#include "../common/messages/generic_msg.h"
#include "../client/menu/logo_screen.h"
#include "../client/menu/main_menu_screen.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Queue<GenericMsg*>* send_queue = new Queue<GenericMsg*>(100);
    Queue<GenericMsg*>* recv_queue = new Queue<GenericMsg*>(100);

    Client* client = nullptr;

    MainWindow mainWindow(nullptr, send_queue, recv_queue, client);
    mainWindow.show();

    if (app.exec() == 0) {
        // se cerro ordenadamente y se tiene que iniciar el render del juego
    }
    return 0;
}