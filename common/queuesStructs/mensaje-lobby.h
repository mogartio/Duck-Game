#ifndef MENSAJELOBBY_H
#define MENSAJELOBBY_H
#include <list>

#include "mensaje.h"
#include "descripcion-lobby.h"


class MensajeLobby : public Mensaje {
public:
    enum tipoMensajeCliente {
        VER_LOBBYS = 0x01,
        CREAR_LOBBY = 0x02,
        UNIRSE_A_LOBBY = 0x03,
        SALIR_DE_LOBBY = 0x04,
        INICIAR_PARTIDA = 0x05,
    };

    enum tipoMensajeServidor {
        LOBBYS_DISPONIBLES = 0x06,
        TODO_SALIO_OKEY = 0x07,
        ERROR = 0x08,
    };

protected:
    // ------------------ Atributos ----------------------
    u_int8_t tipoMensaje;

    u_int8_t idLobby;

    std::list<DescripcionLobby> lobbys;

    //------------------ Métodos privados -----------------------
    /*
     * Lanza una excepcion si el tipo de mensaje no es valido
     */
    void validarTipoMensaje(u_int8_t& tipoMensaje) const;

public:
    // ------------------ Constructor -----------------------

    explicit MensajeLobby(u_int8_t& tipoMensaje);

    explicit MensajeLobby(u_int8_t& tipoMensaje,u_int8_t& idLobby);

    explicit MensajeLobby(u_int8_t& tipoMensaje,std::list<DescripcionLobby>& lobbys);

    // ------------------ Getters -----------------------
    /*
     * Devuelve el tipo de mensaje del lobby
     */
    u_int8_t getTipoMensaje() const;
    /*
     * Devuelve la lista de lobbys
     */
    std::list<DescripcionLobby> getLobbys() const;

    /*
     * Devuelve el id del lobby
     */
    u_int8_t getIdLobby() const;

    // ------------------ Destructor -----------------------
    /*
     * Destructor del mensaje del lobby
     */
    ~MensajeLobby() = default;
};
#endif
