#include "client.h"

Client::Client(Socket&& client_skt, Queue<GenericMsg*>* send_queue, Queue<GenericMsg*>* recv_queue,
               int id):
        client_skt(std::move(client_skt)),
        send_queue(send_queue),
        recv_queue(recv_queue),
        id(id),
        protocol(this->client_skt),
        receiver(recv_queue, &protocol, this),
        sender(send_queue, &protocol) {
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
    sender.stop();
    sender.join();
}

bool Client::is_alive() { return receiver.is_alive() && sender.is_alive(); }

int Client::get_id() const { return id; }

// operador de comparacion para poder comparar clientes
bool Client::operator==(const Client* other) const { return id == other->id; }

void Client::handle_read(const CustomizedPlayerInfoMsg& msg) { (void)msg; }

void Client::handle_read(const ViewLobbiesMsg& msg) { (void)msg; }

void Client::handle_read(const ChooseLobbyMsg& msg) { (void)msg; }

void Client::handle_read(const CreateLobbyMsg& msg) { (void)msg; }

void Client::handle_read(const GoBackMsg& msg) { (void)msg; }

void Client::handle_read(const ExitFromLobbyMsg& msg) { (void)msg; }

void Client::handle_read(const StartGameMsg& msg) { (void)msg; }
