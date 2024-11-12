cmake_minimum_required(VERSION 3.15)
project(duck_game
    VERSION 1.0
    HOMEPAGE_URL "https://github.com/FacuGerez/Tp-Duck-Game-7.git"
    LANGUAGES CXX
)

# Enable AUTOMOC for Qt's Meta-Object Compiler
set(CMAKE_AUTOMOC ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags for C and C++
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -std=c11 -D _POSIX_C_SOURCE=200809L")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -std=c++17 -D _POSIX_C_SOURCE=200809L")

# Include directories
include_directories(common client server common/messages common/socket client/menu server/game_logic client/menu)

# Find required libraries
find_package(SDL2 REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(yaml-cpp REQUIRED)

# Add all .cpp and .h files 
file(GLOB_RECURSE COMMON_SOURCES common/*.cpp common/*.h)
file(GLOB_RECURSE CLIENT_SOURCES client/*.cpp client/*.h client/menu/*.cpp client/menu/*.h)
file(GLOB_RECURSE SERVER_SOURCES server/*.cpp server/*.h server/game_logic/*.cpp server/game_logic/*.h)

# Define the common static library
add_library(common STATIC ${COMMON_SOURCES})

# Add executables 
add_executable(client ${CLIENT_SOURCES} ${COMMON_SOURCES})
add_executable(server ${SERVER_SOURCES} ${COMMON_SOURCES})

# Copy the entire img_src folder, including subdirectories, to the build directory
add_custom_target(CopyResources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/client/SDL/img_src ${CMAKE_BINARY_DIR}/img_src
)

add_dependencies(client CopyResources)


# Link libraries
target_link_libraries(client common SDL2::SDL2 SDL2 SDL2_image Qt5::Core Qt5::Widgets yaml-cpp)
target_link_libraries(server common yaml-cpp)