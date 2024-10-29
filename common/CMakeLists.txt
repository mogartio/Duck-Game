target_sources(common
    PRIVATE
    # .cpp files
    socket/liberror.cpp
    socket/resolver.cpp
    socket/resolvererror.cpp
    socket/socket.cpp
    protocolo-common.cpp
    messages/generic_msg.cpp
    messages/handler_send.cpp
    messages/handler_recv.cpp

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
    messages/handler_send.h
    messages/handler_recv.h
    )
