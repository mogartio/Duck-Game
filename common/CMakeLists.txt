target_sources(common
    PRIVATE
    # .cpp files
    messages/mensaje.cpp
    messages/mensaje-lobby.cpp
    socket/liberror.cpp
    protocolo-common.cpp
    socket/resolver.cpp
    socket/resolvererror.cpp
    socket/socket.cpp


    PUBLIC
    # .h files
    messages/descripcion-lobby.h
    messages/mensaje.h
    messages/mensaje-lobby.h
    socket/liberror.h
    protocolo-common.h
    queue.h
    socket/resolver.h
    socket/resolvererror.h
    socket/socket.h
    socket/socket_error.h
    thread.h
    )
