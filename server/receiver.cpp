#include "receiver.h"

#include <iostream>
#include <string>


Receiver::Receiver(Socket& skt, Queue<std::string>& queue, std::atomic<bool>& is_dead)
    : skt(skt), receiver_queue(queue), is_dead(is_dead) {}

void Receiver::run() {
    try {
        // Creo el protocolo del servidor
        //ServerProtocol protocolo(skt);
        // Mientras el cliente no este muerto
        while (!is_dead) {
            // Recibo el mensaje del cliente a traves del protocolo o me quedo esperando
            //auto messaje = protocolo.recv_capture_attempt();
            // Agrego el mensaje a la cola de mensajes o me quedo esperando
            //receiver_queue.push(messaje);
        }
    }/* catch (SocketClosedError& e) {
        // Si el socket esta cerrado significa que el cliente se fue
        // cuando estabamos bloqueados esperando un mensaje del cliente
        return;
    }*/ catch (...) {
        // Si ocurre un error desconocido el hilo tenemos un problema
        std::cerr << "Error desconocido en el receiver" << std::endl;
    }
}
