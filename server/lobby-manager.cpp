#include "lobby-manager.h"

LobbyManager::LobbyManager(ClientsMonitor& clients, Queue<ServerMensajeLobby>& recv_queue,
                           SendQueuesMonitor<ServerMensajeLobby>& send_queues):
        clients(clients), recv_queue(recv_queue), send_queues(send_queues), keep_running(true) {}

void LobbyManager::crearLobby(uint8_t& idCliente) {
    std::cout << "Client id: " << (int) idCliente << " created a lobby" << std::endl;
    // Crear lobby
    // lobbys_disponibles.emplace_back(clients.getClient(idCliente));
}

void LobbyManager::unirseALobby(uint8_t& idLobby, uint8_t& idCliente) {
    std::cout << "Client id: " << (int) idCliente << " joined lobby id: " << (int) idLobby << std::endl;
    // Unirse a lobby
    // lobbys_disponibles[idLobby].agregarCliente(clients.getClient(idCliente));
}

void LobbyManager::iniciarPartida(uint8_t& idLobby) {
    // Iniciar partida
    for (auto& lobby: lobbys_disponibles) {
        if (lobby.getId() == idLobby) {
            lobby.startGame();
            return;
        }
    }
}

void LobbyManager::salirDeLobby(uint8_t& idCliente, uint8_t& idLobby) {
    std::cout << "Client id: " << (int) idCliente << " left lobby id: " << (int) idLobby << std::endl;
    // Salir de lobby
    for (auto& lobby: lobbys_disponibles) {
        if (lobby.getId() == idLobby) {
            // lobby.removePlayer(clients.getClient(idCliente));
            return;
        }
    }
}

void LobbyManager::enviarLobbysDisponibles() {
    std::list<DescripcionLobby> lobbys;
    for (auto& lobby: lobbys_disponibles) {
        lobbys.push_back(lobby.getDescription());
    }
    // Enviar lobbys disponibles
    ServerMensajeLobby msg = ServerMensajeLobby::mensajeLobbysDisponibles(lobbys);

    // esto se podria mejorar
    std::list<ServerMensajeLobby> msgs;
    msgs.push_back(msg);

    // mando a los clientes
    send_queues.broadcast(msgs);

    /*
    LO QUE SE NECESITA ES UNA FORMA DE ACCEDER A LA QUEUE DEL CLIENT ESPECIFICO
    ALGO DEL ESTILO:
    send_queues.sendToClient(msg, idCliente);
    */
}

void LobbyManager::killLobbys() {
    for (auto& lobby: lobbys_disponibles) {
        lobby.closeLobby();
    }
    lobbys_disponibles.clear();
}

void LobbyManager::cleanLobbys() {
    lobbys_disponibles.remove_if([](Lobby& lobby) { return lobby.is_empty(); });
}

void LobbyManager::analizarMensaje(ServerMensajeLobby& msg) {
    u_int8_t idCliente = msg.getIdCliente();
    u_int8_t idLobby = msg.getIdLobby();
    switch (msg.getTipoMensaje()) {
        case MensajeLobby::CREAR_LOBBY:
            crearLobby(idCliente);
            break;
        case MensajeLobby::UNIRSE_A_LOBBY:
            unirseALobby(idLobby, idCliente);
            break;
        case MensajeLobby::INICIAR_PARTIDA:
            iniciarPartida(idLobby);
            break;
        case MensajeLobby::SALIR_DE_LOBBY:
            salirDeLobby(idCliente, idLobby);
            break;
        case MensajeLobby::VER_LOBBYS:
            enviarLobbysDisponibles();
            break;
    }
}

void LobbyManager::run() {
    try {
        while (keep_running) {
            ServerMensajeLobby msg = recv_queue.pop();
            // Procesar mensajes aca
            analizarMensaje(msg);

            // Limpiar lobbys vacios
            cleanLobbys();
        }
    } catch (const ClosedQueue& e) {
        // error esperado
        return;
    } catch (...) {
        std::cerr << "error inesperado surgio en Lobby manager" << std::endl;
        return;
    }
}

void LobbyManager::kill() {
    keep_running = false;
    recv_queue.close();
}

LobbyManager::~LobbyManager() { killLobbys(); }
