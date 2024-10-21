#include "mensaje.h"

Mensaje::Mensaje(Mensaje::genericType header) : header(header) {}

Mensaje::genericType Mensaje::getHeader() const {
    return header;
}


