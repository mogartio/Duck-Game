target_sources(common
    PRIVATE
    # .cpp files
    # queuesStructs/clientInfo.cpp
    queuesStructs/mensaje.cpp
    queuesStructs/mensaje-lobby.cpp
    liberror.cpp
    protocolo-common.cpp
    resolver.cpp
    resolvererror.cpp
    socket.cpp


    PUBLIC
    # .h files
    queuesStructs/descripcion-lobby.h
    queuesStructs/mensaje.h
    queuesStructs/mensaje-lobby.h
    liberror.h
    protocolo-common.h
    queue.h
    resolver.h
    resolvererror.h
    socket.h
    socket_error.h
    thread.h
    )
