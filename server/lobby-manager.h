#ifndef LOBBYMANAGER_H
#define LOBBYMANAGER_H


#include <list>

#include "./../common/queue.h"
#include "./../common/thread.h"

#include "clients_monitor.h"
#include "lobby.h"
#include "send_queues_monitor.h"

/*
class LobbyManager: public Thread {
private:
    std::list<Lobby> lobbys_disponibles;

    ClientsMonitor& clients;

    Queue<std::string>& recv_queue;

    SendQueuesMonitor<std::string>& send_queues;

    std::atomic<bool> keep_running;

    void crearLobby(uint8_t& idCliente);

    void unirseALobby(uint8_t& idLobby, uint8_t& idCliente);

    void iniciarPartida(uint8_t& idLobby);

    void salirDeLobby(uint8_t& idCliente, uint8_t& idLobby);

    void enviarLobbysDisponibles();

    void killLobbys();

    void cleanLobbys();

    void analizarMensaje(std::string& msg);

public:

    // Constructor del manejador de lobbys
    LobbyManager(ClientsMonitor& clients, Queue<std::string>& recv_queue,
                 SendQueuesMonitor<std::string>& send_queues);

    // Implementamos el método `run`
    void run() override;


    // Método que se encarga de detener el hilo del manejador de lobbys
    void kill();

    // Destructor del manejador de lobbys
    ~LobbyManager();

    // ------------------ Desabilitamos -----------------------
    // Desabilitamos el constructor por copia
    LobbyManager(const LobbyManager&) = delete;
    LobbyManager& operator=(const LobbyManager&) = delete;


    // Hacemos que no se pueda mover
    LobbyManager(LobbyManager&&) = delete;
    LobbyManager& operator=(LobbyManager&&) = delete;

};
*/
#endif
