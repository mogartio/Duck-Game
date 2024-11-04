#include <iomanip>  // Incluir el encabezado <iomanip> para std::setw y std::setfill
#include <iostream>
#include <sstream>  // Incluir el encabezado <sstream>

#include "../common/messages/generic_msg.h"
#include "../common/socket/socket.h"

#include "client_protocol.h"

int main(int argc, char const* argv[]) {

    if (argc != 3) {
        std::cerr << "Bad number of arguments in client side\n";
        return -1;
    }

    std::cout << argv[1] << std::endl;

    Socket skt(argv[1], argv[2]);

    ClientProtocol protocol(skt);

    std::string input_line;
    std::stringstream input;
    int directive;
    while (true) {
        std::getline(std::cin, input_line);   // Leer la entrada en una cadena de texto
        std::stringstream input(input_line);  // Insertar la cadena en el stringstream
        input >> directive;
        GenericMsg* msg;

        switch (directive) {
            case 1:
                std::cout << "Preguntando por lobbies" << std::endl;
                msg = new ViewLobbiesMsg();
                break;
            case 2:
                std::cout << "Creando lobby con nombre de player Player1" << std::endl;
                msg = new CreateLobbyMsg("player1");
                break;
            case 3:
                std::cout << "Eligiendo lobby 1 con nombre de player Player2" << std::endl;
                msg = new ChooseLobbyMsg(1, "player2");
                break;
            case 4:
                std::cout << "Saliendo del lobby con nombre de player Player2" << std::endl;
                msg = new ExitFromLobbyMsg("player2");
                break;
            case 5:
                std::cout << "Iniciando juego" << std::endl;
                msg = new StartGameMsg();
                break;
            default:
                std::cout << "Termino el programa" << std::endl;
                return 0;
        }

        msg->accept_send(protocol);
        GenericMsg* msg_recv = protocol.receive();

        std::cout << "Mensaje recibido con header: 0x" << std::hex << std::setw(2)
                  << std::setfill('0') << static_cast<int>(msg_recv->get_header()) << std::endl;
    }

    /*

    std::string input;

    StartActionMsg msg(ActionsId::MOVE_LEFT, "player1");
    protocol.send(&msg);
    ViewLobbiesMsg msg2;
    protocol.send(&msg2);

    GenericMsg* msg_recv1 = protocol.receive();
    std::cout << "Mensaje recibido con header: 0x" << std::hex << std::setw(2) << std::setfill('0')
              << static_cast<int>(msg_recv1->get_header()) << std::endl;
    GenericMsg* msg_recv2 = protocol.receive();
    std::cout << "Mensaje recibido con header: 0x" << std::hex << std::setw(2) << std::setfill('0')
              << static_cast<int>(msg_recv2->get_header()) << std::endl;
    */


    return 0;
}
