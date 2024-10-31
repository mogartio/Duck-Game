#include "client.h"

Client::Client(const char* host, const char* port, Queue<GenericMsg*>* send_queue, Queue<GenericMsg*>* recv_queue) :
    client_skt(host, port),
    send_queue(send_queue),
    recv_queue(recv_queue),
    protocol(client_skt),
    receiver(recv_queue, &protocol),
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
    client_skt.shutdown(2);
    client_skt.close();
    receiver.kill();
    receiver.join();
    sender.kill();
    sender.join();
}

bool Client::is_alive() { return receiver.is_alive() && sender.is_alive(); }

