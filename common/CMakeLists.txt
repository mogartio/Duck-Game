target_sources(common
    PRIVATE
    # .cpp files
    socket/liberror.cpp
    socket/resolver.cpp
    socket/resolvererror.cpp
    socket/socket.cpp
    protocolo-common.cpp
    messages/generic_msg.cpp
    messages/generic_msg_responseser.cpp
    messages/generic_msg_lobbys.cpp
    messages/generic_msg_game.cpp
    messages/generic_msg_customizer.cpp
    messages/handler.cpp

    PUBLIC
    # .h files
    socket/liberror.h
    queue.h
    socket/resolver.h
    socket/resolvererror.h
    socket/socket.h
    socket/socket_error.h
    thread.h
    protocolo-common.h
    messages/generic_msg.h
    messages/generic_msg_responseser.h
    messages/generic_msg_lobbys.h
    messages/generic_msg_game.h
    messages/generic_msg_customizer.h
    messages/descripcion-lobby.h
    messages/handler.h
    )
