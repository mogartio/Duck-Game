#ifndef PROTOCOLOLOBBYS_H
#define PROTOCOLOLOBBYS_H


class ProtocoloLobbys {
public:
    // ------------------- Restricciones -------------------
    /*
     * Deshabilitamos el constructor por copia y operador asignación por copia
     * */
    ProtocoloLobbys(const ProtocoloLobbys&) = delete;
    ProtocoloLobbys& operator=(const ProtocoloLobbys&) = delete;

    /*
     * Hacemos que la clase no sea movible.
     * */
    ProtocoloLobbys(ProtocoloLobbys&&) = delete;
    ProtocoloLobbys& operator=(ProtocoloLobbys&&) = delete;

    // ------------------- Destructor -------------------
    /*
     * Destructor del cliente
     */
    ~ProtocoloLobbys() = default;
};
#endif
