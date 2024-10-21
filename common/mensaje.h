#ifndef MENSAJE_H
#define MENSAJE_H

#include "descripcion-lobby.h"

class Mensaje {
public:
    enum genericType {
        CUSTOMIZEPLAYER = 0x01,
        LOBBYMESSAGE = 0x02,
        TECLADOMESSAGE = 0x03,
    };

protected:
    // El tipo de mensaje que se quiere enviar
    genericType causa;
public:
    // ------------------ Constructor -----------------------
    /*
     * Constructor del mensaje
     */
    explicit Mensaje(genericType causa);

    // ------------------ Getters -----------------------
    /*
     * Devuelve el tipo de mensaje
     */
    genericType getCausa() const;

    // ------------------ Destructor -----------------------
    /*
     * Destructor del mensaje del lobby
     */
    ~Mensaje() = default;
};
#endif
