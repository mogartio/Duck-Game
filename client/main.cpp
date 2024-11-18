#include <QApplication>
#include <iostream>

#include "../client/menu/connection_screen.h"
#include "../client/menu/create_game_screen.h"
#include "../client/menu/main_window.h"
#include "../common/messages/generic_msg.h"
#include "../common/queue.h"
#include "SDL/game/game.h"

#include "client.h"
#include "client_protocol.h"

int main(int argc, char* argv[]) {
    // inicializadores
    Queue<std::shared_ptr<GenericMsg>> send_queue(100);
    Queue<std::shared_ptr<GenericMsg>> recv_queue(100);
    std::string first_player = "Pepiño";
    std::string second_player = "Madre mia";

    // cosa rara que necesita qt
    std::list<std::string>* local_players = new std::list<std::string>();
    Client* client = nullptr;

    if (argc > 1 && strcmp(argv[1], "test")) {

        QApplication app(argc, argv);

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

        first_player = local_players->front();
        local_players->pop_front();
        second_player = local_players.size() != 0 ? local_players->front() : "";
    } else {
        std::cout << "Test mode activado" << std::endl;
        Socket skt("localhost", "8080");
        client = new Client(std::move(skt), &send_queue, &recv_queue);

        std::cout << "Se pide la lista de lobbies" << std::endl;
        std::shared_ptr<GenericMsg> msg = std::make_shared<ViewLobbiesMsg>();
        send_queue.push(msg);
        std::shared_ptr<SendLobbiesListMsg> msg2 =
                std::dynamic_pointer_cast<SendLobbiesListMsg>(recv_queue.pop());
        std::cout << "Se reciben los lobbies" << std::endl;

        std::vector<DescripcionLobby> lobbies = msg2->get_lobbies();
        if (lobbies.size() == 0) {
            std::cout << "No hay lobbies, se crea uno" << std::endl;
            std::shared_ptr<GenericMsg> msg3 =
                    std::make_shared<CreateLobbyMsg>(first_player, "Lobby de Pepiño", 3);
            send_queue.push(msg3);
            recv_queue.pop()->get_header() == GenericMsg::MsgTypeHeader::EVERYTHING_OK_MSG ?
                    std::cout << "Recepcion excelente" << std::endl :
                    throw std::runtime_error("Error al crear el lobby");
            recv_queue.pop()->get_header() == GenericMsg::MsgTypeHeader::INFO_LOBBY_MSG ?
                    std::cout << "Recepcion excelente" << std::endl :
                    throw std::runtime_error("Error al crear el lobby");
            std::cout << "Lobby creado" << std::endl;
            std::cout << "Se elige el lobby" << std::endl;
            std::shared_ptr<GenericMsg> msg4 = std::make_shared<ChooseLobbyMsg>(1, second_player);
            send_queue.push(msg4);
            recv_queue.pop()->get_header() == GenericMsg::MsgTypeHeader::EVERYTHING_OK_MSG ?
                    std::cout << "Recepcion excelente" << std::endl :
                    throw std::runtime_error("Error al elegir el lobby");
            recv_queue.pop()->get_header() == GenericMsg::MsgTypeHeader::PLAYER_INFO_MSG ?
                    std::cout << "Recepcion excelente" << std::endl :
                    throw std::runtime_error("Error al elegir el lobby");
            recv_queue.pop()->get_header() == GenericMsg::MsgTypeHeader::INFO_LOBBY_MSG ?
                    std::cout << "Recepcion excelente" << std::endl :
                    throw std::runtime_error("Error al elegir el lobby");
            std::cout << "Lobby elegido" << std::endl;
            // Esperar a que otra terminal se una al lobby de ser necesario
            std::cout << "Esperando a que se una otro jugador ....." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(15));
            std::cout << "Tiempo de espera de otro jugador terminado" << std::endl;
            std::cout << "Se envian los datos de los jugadores" << std::endl;
            std::shared_ptr<GenericMsg> msg5 = std::make_shared<CustomizedPlayerInfoMsg>(
                    1, GenericMsg::DuckColor::GREY, second_player, second_player,
                    GenericMsg::PlayerReadyState::READY);
            std::shared_ptr<GenericMsg> msg6 = std::make_shared<CustomizedPlayerInfoMsg>(
                    1, GenericMsg::DuckColor::WHITE, first_player, first_player,
                    GenericMsg::PlayerReadyState::READY);
            send_queue.push(msg5);
            send_queue.push(msg6);
            recv_queue.pop()->get_header() == GenericMsg::MsgTypeHeader::INFO_LOBBY_MSG ?
                    std::cout << "Recepcion excelente" << std::endl :
                    throw std::runtime_error("Error al enviar los datos de los jugadores");
            recv_queue.pop()->get_header() == GenericMsg::MsgTypeHeader::INFO_LOBBY_MSG ?
                    std::cout << "Recepcion excelente" << std::endl :
                    throw std::runtime_error("Error al enviar los datos de los jugadores");
            std::cout << "Datos enviados" << std::endl;
            std::cout << "Se inicia el juego" << std::endl;
            std::shared_ptr<GenericMsg> msg7 = std::make_shared<StartGameMsg>();
            send_queue.push(msg7);
            recv_queue.pop()->get_header() == GenericMsg::MsgTypeHeader::INFO_LOBBY_MSG ?
                    std::cout << "Recepcion excelente" << std::endl :
                    throw std::runtime_error("Error al iniciar el juego");
            std::cout << "Juego iniciado" << std::endl;
        } else if (lobbies.size() == 1) {
            DescripcionLobby lobby = lobbies[0];
            first_player = "Martinsiño";
            second_player = "";
            std::cout << "Se une un jugador online" << std::endl;
            std::shared_ptr<GenericMsg> msg3 =
                    std::make_shared<ChooseLobbyMsg>(lobby.idLobby, first_player);
            send_queue.push(msg3);
            recv_queue.pop()->get_header() == GenericMsg::MsgTypeHeader::EVERYTHING_OK_MSG ?
                    std::cout << "Recepcion excelente" << std::endl :
                    throw std::runtime_error("Error al elegir el lobby");
            recv_queue.pop()->get_header() == GenericMsg::MsgTypeHeader::PLAYER_INFO_MSG ?
                    std::cout << "Recepcion excelente" << std::endl :
                    throw std::runtime_error("Error al elegir el lobby");
            recv_queue.pop()->get_header() == GenericMsg::MsgTypeHeader::INFO_LOBBY_MSG ?
                    std::cout << "Recepcion excelente" << std::endl :
                    throw std::runtime_error("Error al elegir el lobby");
            std::cout << "Jugador unido" << std::endl;
            std::cout << "Se envian los datos de los jugadores" << std::endl;
            std::shared_ptr<GenericMsg> msg4 = std::make_shared<CustomizedPlayerInfoMsg>(
                    1, GenericMsg::DuckColor::ORANGE, first_player, first_player,
                    GenericMsg::PlayerReadyState::READY);
            send_queue.push(msg4);
            recv_queue.pop()->get_header() == GenericMsg::MsgTypeHeader::INFO_LOBBY_MSG ?
                    std::cout << "Recepcion excelente" << std::endl :
                    throw std::runtime_error("Error al enviar los datos de los jugadores");
            std::cout << "Datos enviados" << std::endl;
            std::cout << "Esperando a que se empiece el juego....." << std::endl;
            recv_queue.pop()->get_header() == GenericMsg::MsgTypeHeader::INFO_LOBBY_MSG ?
                    std::cout << "Recepcion excelente" << std::endl :
                    throw std::runtime_error("Error al enviar los datos de los jugadores");
            std::cout << "Juego iniciado" << std::endl;
        }
    }
    Game game(send_queue, recv_queue, first_player, second_player);
    game.play();
    recv_queue.close();
    if (client) {
        client->stop();
        delete client;
    }
    delete local_players;
    return 0;
}
