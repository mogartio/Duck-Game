# Add this line to include all .cpp files from the common directory
file(GLOB COMMON_SOURCES ../common/*.cpp)

# Add this line to include all .h files from the common directory
file(GLOB COMMON_HEADERS ../common/*.h)

target_sources(client_exe  # Use the correct target name
    PRIVATE
    # .cpp files
    ${COMMON_SOURCES}  # Include all .cpp files from common
    main.cpp  # Assuming main.cpp is the entry point for the client
    client_protocol.cpp  # Assuming client.cpp is the client implementation
    client.cpp
    SDL/game/frontOnePlayer.cpp
    SDL/game/window.cpp
    SDL/game/map.cpp
    SDL/game/player.cpp
    SDL/game/image.cpp
    SDL/game/wingState.cpp
    PUBLIC
    # .h files
    ${COMMON_HEADERS}  # Include all .h files from common
      # Include only protocol.h from the client directory
    client_protocol.h
    client.h
    SDL/game/frontOnePlaye.h
    SDL/game/window.h
    SDL/game/map.h
    SDL/game/player.h
    SDL/game/image.h
    SDL/game/wingState.h
)

# Include the common directory for headers
target_include_directories(client_exe PRIVATE ../common)
