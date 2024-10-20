#ifndef DESCRIPCIONLOBBY_H
#define DESCRIPCIONLOBBY_H
#include <cstdint>
#include <string>

class DescripcionLobby {
public:
    u_int8_t idLobby;
    u_int8_t cantidadJugadores;
    std::string nombreLobby;

    // ------------------ Desabilitamos -----------------------
    /*
     * Destructor del mensaje del lobby
     */
    ~DescripcionLobby() = default;
};
#endif
