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
    u_int8_t tipoMensaje;

public:
    // ------------------ Constructor -----------------------
    /*
     * Constructor del mensaje del lobby
     */
    explicit MensajeLobby(genericType causa,u_int8_t tipoMensaje);

    // ------------------ Destructor -----------------------
    /*
     * Destructor del mensaje del lobby
     */
    ~MensajeLobby() = default;

    // ------------------ Getters -----------------------
    /*
     * Devuelve el tipo de mensaje del lobby
     */
    u_int8_t getTipoMensaje() const;

};
#endif
