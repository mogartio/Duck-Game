#ifndef DESCRIPCIONLOBBY_H
#define DESCRIPCIONLOBBY_H
#include <cstdint>
#include <string>

struct DescipcionPlayer {
    std::string nombre;
    uint8_t color;
    // agregar mas en caso de ser necesario

    ~DescipcionPlayer() = default;
};

/*
 * Clase que representa la descripcion de un lobby
 */
struct DescripcionLobby {
    u_int8_t idLobby;
    std::string nombreLobby;
    u_int8_t cantidadJugadores;  // 1 o 2 por ahora (tanto online como local)

    /*
     * Destructor del mensaje del lobby
     */
    ~DescripcionLobby() = default;
};
#endif
