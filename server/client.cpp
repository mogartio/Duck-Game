#include "client.h"

Client::Client(Socket&& client_skt, uint id,
               SendQueuesMonitor<std::shared_ptr<GenericMsg>>& send_queues, LobbysMonitor& lobbys,
               bool is_testing):
        client_skt(std::move(client_skt)),
        send_queue(100),
        recv_queue(),
        send_queues(send_queues),
        id(id),
        protocol(this->client_skt),
        receiver(recv_queue, &protocol, this),
        sender(&send_queue, &protocol, this),
        lobbys(lobbys),
        is_testing(is_testing) {
    send_queues.add(&send_queue, id);
    start_client();
}

void Client::start_client() {
    try {
        receiver.start();
        sender.start();
    } catch (const std::exception& e) {
        std::cout << "Error al iniciar el cliente: " << e.what() << std::endl;
    }
}

void Client::stop() {
    receiver.stop();
    receiver.join();
    sender.kill();
    sender.join();
}

bool Client::is_alive() { return receiver.is_alive() && sender.is_alive(); }

uint Client::get_id() const { return id; }

void Client::switch_queues(Queue<std::shared_ptr<GenericMsg>>* new_queue) {
    receiver.switch_q(new_queue);
}

// operador de comparacion para poder comparar clientes
bool Client::operator==(const Client* other) const { return id == other->id; }

void Client::handle_read(const ViewLobbiesMsg& msg) {
    (void)msg;
    send_queues.send_to_client(std::make_shared<SendLobbiesListMsg>(lobbys.get_lobbys()), id);
}

void Client::handle_read(const CreateLobbyMsg& msg) {
    std::string player_name = msg.get_player_name();
    std::string lobby_name = msg.get_lobby_name();
    uint8_t max_players = msg.get_max_players();
    lobby_unido_id = lobbys.create(send_queues, player_name, lobby_name, max_players, this);
}

void Client::handle_read(const ChooseLobbyMsg& msg) {
    try {
        std::string player_name = msg.get_player_name();
        lobbys.add_player(msg.get_lobby_id(), player_name, this);
        lobby_unido_id = msg.get_lobby_id();
    } catch (const std::runtime_error& e) {
        std::cout << "Error al unirse al lobby debido a que: " << e.what() << std::endl;
        send_queues.send_to_client(std::make_shared<ErrorMsg>(e.what()), id);
    }
}

void Client::handle_read(const CustomizedPlayerInfoMsg& msg) {
    try {
        lobbys.update_player_info(msg.get_lobby_id(), msg.get_player_name(),
                                  msg.get_player_new_name(), msg.get_color(), msg.get_is_ready());
    } catch (const std::runtime_error& e) {
        std::cout << "Error al actualizar la informacion del jugador debido a que: " << e.what()
                  << std::endl;
        send_queues.send_to_client(std::make_shared<ErrorMsg>(e.what()), id);
    }
}


void Client::handle_read(const GoBackMsg& msg) { (void)msg; }

void Client::handle_read(const ExitFromLobbyMsg& msg) {
    try {
        lobbys.remove_player(lobby_unido_id, msg.get_player_name());
    } catch (const std::runtime_error& e) {
        std::cout << "Error al salir del lobby debido a que: " << e.what() << std::endl;
        send_queues.send_to_client(std::make_shared<ErrorMsg>(e.what()), id);
    }
}

void Client::handle_read(const StartGameMsg& msg) {
    (void)msg;
    try {
        lobbys.start_game(lobby_unido_id);
        // lobbys.start_game(lobby_unido_id,id); esto es para la funcionalidad futura
    } catch (const std::runtime_error& e) {
        std::cout << "Error al unirse al lobby debido a que: " << e.what() << std::endl;
        send_queues.send_to_client(std::make_shared<ErrorMsg>(e.what()), id);
    } catch (...) {
        std::cout << "Error al iniciar el juego debido a un error desconocido " << std::endl;
        send_queues.send_to_client(
                std::make_shared<ErrorMsg>(
                        "Error al iniciar el juego debido a un error desconocido "),
                id);
    }
}

void Client::killGameAndLobby() { lobbys.remove_lobby(lobby_unido_id); }
