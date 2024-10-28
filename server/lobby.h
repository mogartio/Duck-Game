#ifndef LOBBY_H
#define LOBBY_H


#include <list>

#include "./../common/messages/descripcion-lobby.h"

#include "client.h"
#define MAX_PLAYERS 2
#define EMPTY_PLAYERS 0


class Lobby {
private:
    std::list<Client*> jugadores;

    u_int8_t id_lobby;

    void lobby_empty();

public:
    /*
     * Constructor del lobby
     */
    explicit Lobby(Client* client, u_int8_t& id_lobby);

    /*
     * Metodo que agrega un jugador al lobby
     */
    void addPlayer(Client* client);

    /*
     * Metodo que elimina un jugador del lobby
     */
    void removePlayer(Client* client);

    /*
     * Metodo que inicia el juego
     */
    void startGame();

    /*
     * Metodo que cierra el lobby
     */
    void closeLobby();

    /*
     * Metodo que devuelve si el lobby esta vacio
     */
    bool is_empty() const;

    /*
     * Metodo que devuelve el id del lobby
     */
    u_int8_t getId() const;

    /*
     * Metodo que devuelve la descripcion del lobby
     */
    DescripcionLobby getDescription() const;

    // ------------------ Desabilitamos -----------------------
    /*
     * Deshabilitamos el constructor por copia y operador asignación por copia
     * */
    Lobby(const Lobby&) = delete;
    Lobby& operator=(const Lobby&) = delete;

    /*
     * Hacemos que la clase no sea movible.
     * */
    Lobby(Lobby&&) = delete;
    Lobby& operator=(Lobby&&) = delete;

    /*
     * Destructor del aceptador del servidor
     */
    ~Lobby() = default;
};
#endif
