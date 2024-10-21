# Add this line to include all .cpp files from the common directory
file(GLOB COMMON_SOURCES ../common/*.cpp)

# Add this line to include all .h files from the common directory
file(GLOB COMMON_HEADERS ../common/*.h)

target_sources(server_exe  # Use the correct target name
    PRIVATE
    # .cpp files
    ${COMMON_SOURCES}  # Include all .cpp files from common
    server.cpp
    acceptor.cpp 
    client.cpp 
    clients_monitor.cpp
    main.cpp
    receiver.cpp
    sender.cpp
    lobby-manager.cpp
    mensaje-lobby.cpp  # Ensure this line is present
    protocolo-lobbys.cpp
    lobby.cpp

    PUBLIC
    # .h files
    ${COMMON_HEADERS}  # Include all .h files from common
    server.h
    acceptor.h
    client.h
    clients_monitor.h
    send_queues_monitor.h
    read_input.h 
    protocol.h
    receiver.h
    sender.h
    lobby-manager.h
    mensaje-lobby.h
    protocolo-lobbys.h
    lobby.h
)

# Include the common directory for headers
target_include_directories(server_exe PRIVATE ../common)