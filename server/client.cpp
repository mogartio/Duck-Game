#include "client.h"

#include <utility>

Client::Client(Socket&& skt,Queue<std::string>& receiver_queue, const u_int& id_client)
    : socket(std::move(skt)), is_dead(false), receiver(socket,receiver_queue, is_dead), sender(socket,is_dead, id_client) {
    // Iniciamos los hilos
    receiver.start();
    sender.start();
}

void Client::kill() {
    // Le decimos a los hilos que murio el cliente
    is_dead = true;
    // Cerramos los medios de comunicacion para que los hilos terminen
    socket.shutdown(2);
    // Cerramos el socket
    socket.close();
    // Cerramos la cola del sender para que termine de esperar mensajes
    sender.close();
    // El receiver no lo podemos cerrar porque es global
    // y ademas de que el gameloop lo esta consumiendo constantemente
    // por lo que no sera necesario cerrarlo ya que el hilo terminara

    // Esperamos a que los hilos terminen
    receiver.join();
    sender.join();
}

bool Client::isDead() const {
    // Si el socket esta cerrado, el cliente esta muerto
    return is_dead;
}
