file(GLOB GAME_SOURCES ../server/game_logic/*.cpp)
file(GLOB GAME_HEADERS ../server/game_logic/*.h)

target_sources(taller_tests
    PRIVATE
    # .cpp files
    ${GAME_SOURCES}
    player.cpp
    air_state.cpp
    stage.cpp
    PUBLIC
    # .h files
    ${GAME_HEADERS}
    player.h
    air_state.h
    stage.h
    )
