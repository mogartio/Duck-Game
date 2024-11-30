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
include_directories(common client server tests)

# Find required libraries
find_package(SDL2 REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets Multimedia REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(GTest REQUIRED)

# Add all .cpp and .h files
file(GLOB_RECURSE COMMON_SOURCES common/*.cpp common/*.h)
file(GLOB_RECURSE CLIENT_SOURCES client/*/*.cpp client/*/*.h)
file(GLOB_RECURSE SERVER_SOURCES server/*/*.cpp server/*/*.h server/*/*/*.cpp server/*/*/*.h)
file(GLOB_RECURSE EDITOR_SOURCES editor/*.cpp editor/*.h)
file(GLOB_RECURSE TEST_SOURCES tests/*/*.cpp tests/*/*.h)

# Excluir archivos en los directorios de CMake
list(FILTER COMMON_SOURCES EXCLUDE REGEX "CMakeFiles")
list(FILTER CLIENT_SOURCES EXCLUDE REGEX "CMakeFiles")
list(FILTER SERVER_SOURCES EXCLUDE REGEX "CMakeFiles")
list(FILTER TEST_SOURCES EXCLUDE REGEX "CMakeFiles")

# Define the common static library
add_library(common STATIC ${COMMON_SOURCES})
target_link_libraries(common PUBLIC yaml-cpp)

# Define the client static library
add_library(client_library STATIC ${CLIENT_SOURCES})
target_link_libraries(client_library PUBLIC common SDL2::SDL2 SDL2 SDL2_image SDL2_mixer SDL2_ttf Qt5::Core Qt5::Widgets Qt5::Multimedia)

# Define the server static library
add_library(server_library STATIC ${SERVER_SOURCES})
target_link_libraries(server_library PUBLIC common)

# Add executables
add_executable(client ./client/main.cpp)
target_link_libraries(client client_library)

add_executable(server ./server/main.cpp)
target_link_libraries(server server_library)

add_executable(editor ${EDITOR_SOURCES})
target_link_libraries(editor PUBLIC Qt5::Core Qt5::Widgets Qt5::Multimedia yaml-cpp)

# Define the test executable
add_executable(tests ./tests/main.cpp ${TEST_SOURCES})
target_link_libraries(tests server_library client_library GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

# Copy the entire img_src folder, including subdirectories, to the build directory
add_custom_target(CopyResources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
)

add_custom_target(CopyResourcesTests ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/tests/gameloop/tests_map ${CMAKE_BINARY_DIR}/tests_map
)

add_dependencies(client CopyResources)
add_dependencies(editor CopyResources)
add_dependencies(tests CopyResourcesTests)
