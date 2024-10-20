#ifndef MENSAJELOBBY_H
#define MENSAJELOBBY_H
#include "descripcion-lobby.h"
#include <list>


class MensajeLobby {
public:
    enum tipoMensaje{
        LOBBYS_DISPONIBLES = 0x01,
        CREAR_LOBBY = 0x02,
        UNIRSE_A_LOBBY = 0x03,
        INICIAR_PARTIDA = 0x04,
        SALIR_DE_LOBBY = 0x05,
    };

private:
    // El tipo de mensaje que se quiere enviar
    tipoMensaje tipo;

    // Para unirse a un lobby se necesita el id del lobby
    uint8_t idLobby;

    // se necesita el id del jugador para saber quien realizo la accion
    uint8_t idCliente;

    // Para mandar las lobbys disponibles se necesita un vector de lobbys
    std::list<DescripcionLobby> lobbys;

    // ------------------ Constructores -----------------------
    /*
     * Constructor del mensaje del lobby
     */
    MensajeLobby() = default;

public:
    // ------------------ Constructores -----------------------
    /*
     * Constructor del mensaje del lobby
     */
    static MensajeLobby crearMensajeLobbysDisponibles(std::list<DescripcionLobby> lobbys);

    /*
     * Constructor del mensaje del lobby
     */
    static MensajeLobby crearMensajeCrearLobby();

    /*
     * Constructor del mensaje del lobby
     */
    static MensajeLobby crearMensajeUnirseALobby(uint8_t idLobby);

    /*
     * Constructor del mensaje del lobby
     */
    static MensajeLobby crearMensajeIniciarPartida();

    /*
     * Constructor del mensaje del lobby
     */
    static MensajeLobby crearMensajeSalirDeLobby();

    // ------------------ Getters -----------------------
    /*
     * Devuelve el tipo de mensaje
     */
    u_int8_t getTipo() const;

    /*
     * Devuelve el id del lobby
     */
    uint8_t getIdLobby() const;

    /*
     * Devuelve el id del cliente
     */
    uint8_t getIdCliente() const;

    /*
     * Setea el id del cliente
     */
    void setIdCliente(uint8_t idCliente);

    /*
     * Devuelve la lista de lobbys
     */
    std::list<DescripcionLobby> getLobbys() const;

    // ------------------ Validaciones -----------------------
    /* PARA CHEQUEAR

        * Devuelve si el mensaje es valido segun el siguiente criterio
            *  - LOBBYS_DISPONIBLES: necesita una lista de lobbys
            * - CREAR_LOBBY: no necesita parametros
            * - UNIRSE_A_LOBBY: necesita el id del lobby
            * - INICIAR_PARTIDA: no necesita parametros
            * - SALIR_DE_LOBBY: no necesita parametros

        static bool esMensajeValido(u_int8_t tipo,...);

    */

    // ------------------ Desabilitamos -----------------------
    /*
     * Destructor del mensaje del lobby
     */
    ~MensajeLobby()=default;

};
#endif
