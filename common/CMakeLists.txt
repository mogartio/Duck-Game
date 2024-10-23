target_sources(common
    PRIVATE
    # .cpp files
    messages/mensaje.cpp
    messages/mensaje-lobby.cpp
    liberror.cpp
    protocolo-common.cpp
    resolver.cpp
    resolvererror.cpp
    socket.cpp


    PUBLIC
    # .h files
    messages/descripcion-lobby.h
    messages/mensaje.h
    messages/mensaje-lobby.h
    liberror.h
    protocolo-common.h
    queue.h
    resolver.h
    resolvererror.h
    socket.h
    socket_error.h
    thread.h
    )
