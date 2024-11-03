#include "client.h"

Client::Client(Socket&& client_skt, int id, SendQueuesMonitor<GenericMsg*>& send_queues,
               LobbysMonitor& lobbys):
        client_skt(std::move(client_skt)),
        send_queue(100),
        recv_queue(),
        send_queues(send_queues),
        id(id),
        protocol(this->client_skt),
        receiver(recv_queue, &protocol, this),
        sender(&send_queue, &protocol),
        lobbys(lobbys) {
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

int Client::get_id() const { return id; }

// operador de comparacion para poder comparar clientes
bool Client::operator==(const Client* other) const { return id == other->id; }

void Client::handle_read(const ViewLobbiesMsg& msg) {
    (void)msg;
    send_queue.push(new SendLobbiesListMsg(lobbys.get_lobbys()));
}

void Client::handle_read(const CreateLobbyMsg& msg) {
    lobby_unido_id = lobbys.create(std::make_tuple(msg.get_player_name(), id));
    send_queue.push(new EverythingOkMsg);
}

void Client::handle_read(const ChooseLobbyMsg& msg) {
    try {
        lobbys.add_player(msg.get_lobby_id(), std::make_tuple(msg.get_player_name(), id));
        lobby_unido_id = msg.get_lobby_id();
        send_queue.push(new EverythingOkMsg);
    } catch (const std::runtime_error& e) {
        std::cout << "Error al unirse al lobby debido a que: " << e.what() << std::endl;
        send_queue.push(new ErrorMsg(e.what()));
    }
}

void Client::handle_read(const CustomizedPlayerInfoMsg& msg) {
    (void)msg;
    // lobbys.update_player(lobby_unido_id, std::make_tuple(msg.get_player_name(), id));
    // send_queue.push(new EverythingOkMsg);
}

void Client::handle_read(const GoBackMsg& msg) { (void)msg; }

void Client::handle_read(const ExitFromLobbyMsg& msg) {
    try {
        lobbys.remove_player(lobby_unido_id, std::make_tuple(msg.get_player_name(), id));
        send_queue.push(new EverythingOkMsg);
        lobby_unido_id = 0;
    } catch (const std::runtime_error& e) {
        std::cout << "Error al salir del lobby debido a que: " << e.what() << std::endl;
        send_queue.push(new ErrorMsg(e.what()));
    }
}

void Client::handle_read(const StartGameMsg& msg) {
    (void)msg;
    lobbys.start_game(lobby_unido_id);
    // lobbys.start_game(lobby_unido_id,id); esto es para la funcionalidad futura
    send_queue.push(new EverythingOkMsg);
}
