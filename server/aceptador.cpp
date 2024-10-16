#include "aceptador.h"

#include <utility>

#include "./../common/liberror.h"

Aceptador::Aceptador(Socket& skt)
    : skt(skt){
    // logic_game.start();
    }

void Aceptador::acceptClient(const u_int& id_client) {
    // Aca acepto un solo cliente
    Socket client = skt.accept();
    // Creo un nuevo cliente pasandole el socket al container
    // Agregamos un cliente a la lista de clientes
    clients.emplace_back(std::move(client), receiver_queue, id_client);
}

void Aceptador::run() {
    // Inicio la logica del juego
    try {
        // Aca acepto multiples clientes
        u_int id_clients = 1;
        while (true) {
            // Acepto un cliente
            acceptClient(id_clients);
            // Limpio los clientes que se desconectaron
            cleanClients();
            id_clients++;
        }
    } catch (const LibError& e) {
        // Error al aceptar un cliente, esto ocurre porque se cerro
        // el socket del servidor que es el aceptador
        // Pero tambien puede ser que el socket haya ocurrido un error
        // inesperado
        std::cerr << "Error en el aceptador por LibError:" << e.what() << std::endl;
    } catch (...) {
        // Error desconocido
        std::cerr << "Error desconocido en el aceptador" << std::endl;
    }
}

void Aceptador::cleanClients() {
    // Por cada cliente en la lista de clientes
    clients.remove_if([](Client& client) {
        // Si el cliente esta muerto
        if (client.isDead()) {
            // Lo matamos
            client.kill();
            // y lo eliminamos de la lista
            return true;
        }
        // Si no esta muerto, no lo eliminamos
        return false;
    });
}

void Aceptador::killAllClients() {
    // Por cada cliente en la lista de clientes
    for (auto& client: clients) {
        // Lo matamos
        client.kill();
    }
    // Limpiamos la lista de clientes entera
    clients.clear();
}

Aceptador::~Aceptador() {
    // cierro todo
    killAllClients();   // Mato a todos los clientes
    //logic_game.kill();  // Mato a la logica del juego
    //logic_game.join();  // Espero a que termine la logica del juego
}
