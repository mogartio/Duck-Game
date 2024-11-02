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
    main.cpp
    server_protocol.cpp
    server.cpp
    receiver.cpp
    game_logic/config.cpp
    game_logic/game_main.cpp
    game_logic/player/air_state.cpp
    game_logic/player/player.cpp
    game_logic/player/player_position.cpp
    game_logic/player/weapon.cpp

    game_logic/map/stage.cpp

    PUBLIC
    # .h files
    ${COMMON_HEADERS}  # Include all .h files from common
    acceptor.h
    client.h
    clients_monitor.h
    server_protocol.cpp
    read_input.h
    send_queues_monitor.h
    server.h
    receiver.h
    game_logic/config.h
    game_logic/game_main.h
    game_logic/player/air_state.h
    game_logic/player/player.h
    game_logic/player/player_position.h
    game_logic/player/weapon.h
    game_logic/player/projectile.h

    game_logic/map/stage.h
)

# Include the common directory for headers
target_include_directories(server_exe PRIVATE ../common)
