#ifndef LOBBYMANAGER_H
#define LOBBYMANAGER_H


#include <list>

#include "mensaje-lobby.h"
#include "./../common/queue.h"
#include "./../common/thread.h"

#include "clients_monitor.h"
#include "lobby.h"
#include "send_queues_monitor.h"


class LobbyManager: public Thread {
private:
    std::list<Lobby> lobbys_disponibles;

    ClientsMonitor& clients;

    Queue<ServerMensajeLobby>& recv_queue;

    SendQueuesMonitor<ServerMensajeLobby>& send_queues;

    std::atomic<bool> keep_running;

    void crearLobby(uint8_t& idCliente);

    void unirseALobby(uint8_t& idLobby, uint8_t& idCliente);

    void iniciarPartida(uint8_t& idLobby);

    void salirDeLobby(uint8_t& idCliente, uint8_t& idLobby);

    void enviarLobbysDisponibles();

    void killLobbys();

    void cleanLobbys();

    void analizarMensaje(ServerMensajeLobby& msg);

public:
    /*
     * Constructor del manejador de lobbys
     */
    LobbyManager(ClientsMonitor& clients, Queue<ServerMensajeLobby>& recv_queue,
                 SendQueuesMonitor<ServerMensajeLobby>& send_queues);

    /*
     * Implementamos el método `run`
     */
    void run() override;

    /*
     * Método que se encarga de detener el hilo del manejador de lobbys
     */
    void kill();

    /*
     * Destructor del aceptador del servidor
     */
    ~LobbyManager();

    // ------------------ Desabilitamos -----------------------
    /*
     * Deshabilitamos el constructor por copia y operador asignación por copia
     * */
    LobbyManager(const LobbyManager&) = delete;
    LobbyManager& operator=(const LobbyManager&) = delete;

    /*
     * Hacemos que la clase no sea movible.
     * */
    LobbyManager(LobbyManager&&) = delete;
    LobbyManager& operator=(LobbyManager&&) = delete;
};
#endif
