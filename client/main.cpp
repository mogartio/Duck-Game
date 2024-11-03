#include <iostream>
#include <QApplication>
#include "../client/menu/opening_window.h"
#include "../common/socket/socket.h"
#include "client_protocol.h"
#include "../common/messages/generic_msg.h"

void onButtonClicked() {
    std::cout << "Button clicked!" << std::endl;
    // Add your custom action here
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Bad number of arguments in client side\n";
        return -1;
    }

    QApplication app(argc, argv);

    OpeningWindow window;
    window.show();

    Socket skt(argv[1], argv[2]);
    ClientProtocol protocol(skt);

    std::string input;

    StartActionMsg msg(ActionsId::MOVE_LEFT, "player1");
    protocol.send(&msg);

    GenericMsg* msg_recv1 = protocol.receive();
    std::cout << "Mensaje recibido con hEADER: 0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(msg_recv1->get_header()) << std::endl;

    return app.exec();
}