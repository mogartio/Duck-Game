target_sources(common
    PRIVATE
    # .cpp files
    
    socket/liberror.cpp
    socket/resolver.cpp
    socket/resolvererror.cpp
    socket/socket.cpp
    protocol.cpp

    PUBLIC
    # .h files

    socket/liberror.h
    protocol.h
    queue.h
    socket/resolver.h
    socket/resolvererror.h
    socket/socket.h
    socket/socket_error.h
    thread.h
    messages/handler.h
    messages/generic_msg.h
    )
