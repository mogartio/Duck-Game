# Add this line to include all .cpp files from the common directory
file(GLOB COMMON_SOURCES ../common/*.cpp)

# Add this line to include all .h files from the common directory
file(GLOB COMMON_HEADERS ../common/*.h)

target_sources(server_exe  # Use the correct target name
    PRIVATE
    # .cpp files
    ${COMMON_SOURCES}  # Include all .cpp files from common
    acceptor.cpp
    client.cpp
    clients_monitor.cpp
    lobby.cpp
    main.cpp
    receiver.cpp
    sender.cpp
    server.cpp


    PUBLIC
    # .h files
    ${COMMON_HEADERS}  # Include all .h files from common
    acceptor.h
    client.h
    clients_monitor.h
    lobby.h
    protocol.h
    read_input.h
    receiver.h
    send_queues_monitor.h
    sender.h
    server.h
)

# Include the common directory for headers
target_include_directories(server_exe PRIVATE ../common)
