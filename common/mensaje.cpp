#include "mensaje.h"

Mensaje::Mensaje(genericType causa) : causa(causa) {}

Mensaje::genericType Mensaje::getCausa() const {
    return causa;
}


