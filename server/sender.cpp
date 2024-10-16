#include "sender.h"

#include <utility>

Sender::Sender(Socket& skt, std::atomic<bool>& is_dead, const u_int& id_client)
    : skt(skt), is_dead(is_dead), id_client(id_client) {}

void Sender::run() {
    try {
        // Creo el protocolo del servidor
        //ServerProtocol protocolo(skt);
        // Mientras el cliente no este muerto
        while (!is_dead) {
            // Popeo el mensaje de la cola o me quedo esperando
            auto messaje = queue.pop();
            // Envio el mensaje al cliente a traves del protocolo
            //protocolo.send_ms(messaje);
        }
    } catch (ClosedQueue& e) {  // HAY Q MEJORARLO
        // Si la cola esta cerrada significa que alguien killeo
        // al cliente y por ende el hilo debe terminar
        return;
    }/*catch (SocketClosedError& e) {
        // Si el socket esta cerrado significa que el cliente se fue
        // cuando estabamos bloqueados mandando un mensaje al cliente
        // tampoco seria un error
        return;
    }*/ catch (...) {
        // Si ocurre un error desconocido el hilo tenemos un problema
        std::cerr << "Error desconocido en el sender" << std::endl;
    }
}

void Sender::close() { queue.close(); }
