target_sources(common
    PRIVATE
    # .cpp files
    socket/liberror.cpp
    socket/resolver.cpp
    socket/resolvererror.cpp
    socket/socket.cpp
    protocol/protocol-socket.cpp
    protocol/send.cpp
    messages/server_generic_msg.cpp
    messages/client_generic_msg.cpp
    messages/generic_msg.cpp

    PUBLIC
    # .h files
    socket/liberror.h
    queue.h
    socket/resolver.h
    socket/resolvererror.h
    socket/socket.h
    socket/socket_error.h
    thread.h
    protocol/send.h
    protocol/protocol-socket.h
    messages/client_generic_msg.h
    messages/server_generic_msg.h
    messages/generic_msg.h
    )
