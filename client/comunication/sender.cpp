#include "sender.h"

void Sender::run() {
    try {
        // Creo el protocolo del cliente
        //ClientProtocol protocolo(skt);
        // Mientras la comunicacion no este muerta
        while ((!is_dead)&&_keep_running) {
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

void Sender::close() { 
    _keep_running = false;
    is_dead = true;    
    queue.close(); 
}
