#include "client.h"

Client::Client(Socket&& client_skt, Queue<std::string>& send_queue, Queue<std::string>& recv_queue, int id): 
    client_skt(std::move(client_skt)), 
    send_queue(send_queue), 
    recv_queue(recv_queue), 
    id(id), 
    protocol(this->client_skt),
    receiver(recv_queue, protocol),
    sender(send_queue, protocol) {
}

void Client::start_client() {
    try {
        receiver.start();
        // sender.start();
    } catch(const std::exception& e) {
        std::cout << "Error al iniciar el cliente: " << e.what() << std::endl;
    }
}

void Client::stop() {
    receiver.stop();
    receiver.join();
    sender.stop();
    sender.join();
}

bool Client::is_alive() {
    return receiver.is_alive() && sender.is_alive();
}

// operador de comparacion para poder comparar clientes
bool Client::operator==(const Client& other) const {
    return id == other.id;
}