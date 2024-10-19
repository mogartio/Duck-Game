# Add this line to include all .cpp files from the common directory
file(GLOB COMMON_SOURCES ../common/*.cpp)

# Add this line to include all .h files from the common directory
file(GLOB COMMON_HEADERS ../common/*.h)

target_sources(taller_server
    PRIVATE
    # .cpp files
    ${COMMON_SOURCES}  # Include all .cpp files from common
    server.cpp
    acceptor.cpp 
    client.cpp 
    clients_monitor.cpp
    send_queues_monitor.cpp
    main.cpp
    receiver.cpp
    sender.cpp

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
)

# Include the common directory for headers
target_include_directories(taller_server PRIVATE ../common)