#ifndef LOBBY_H
#define LOBBY_H

#include <list>
#include <stdexcept>
#include <string>
#include <tuple>

#include "./../common/messages/descripcion-lobby.h"

#define MAX_PLAYERS 2
#define EMPTY_PLAYERS 0


class Lobby {
private:
    // El primer elemento es el id del client y el segundo su nombre de usuario
    std::list<DescipcionPlayer> players;

    uint player1_id;

    uint id_lobby;

    void lobby_empty();

public:
    /*
     * Constructor del lobby
     */
    explicit Lobby(std::tuple<std::string, uint> player1, uint& id_lobby);

    /*
     * Metodo que agrega un jugador al lobby
     */
    void addPlayer(std::tuple<std::string, uint> player2);

    /*
     * Metodo que elimina un jugador del lobby
     */
    void removePlayer(std::tuple<std::string, uint> player);

    /*
     * Metodo que inicia el juego
     */
    void startGame();

    /*
     * Metodo que devuelve si el lobby esta vacio
     */
    bool is_empty() const;

    /*
     * Metodo que devuelve el id del lobby
     */
    uint getId() const;

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
