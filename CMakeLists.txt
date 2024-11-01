# CMake minimum version and project declaration
cmake_minimum_required(VERSION 3.15)
project(MyGameProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required libraries
find_package(SDL2 REQUIRED)
find_package(SDL2pp REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(yaml-cpp REQUIRED)

# Common include directories
include_directories(common)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2PP_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})

# Agrega todos los archivos .cpp en common y server
file(GLOB_RECURSE COMMON_SOURCES common/*.cpp)
file(GLOB_RECURSE SERVER_SOURCES server/*.cpp)
file(GLOB_RECURSE CLIENT_SOURCES client/*.cpp)

# Client executable
add_executable(client_bin client/main.cpp ${CLIENT_SOURCES} ${COMMON_SOURCES})
target_include_directories(client_bin PRIVATE client common)
target_link_libraries(client_bin SDL2::SDL2 SDL2pp::SDL2pp Qt5::Core Qt5::Widgets yaml-cpp)

# Server executable
add_executable(server_bin server/server.cpp ${SERVER_SOURCES} ${COMMON_SOURCES})
target_include_directories(server_bin PRIVATE server common)
target_link_libraries(server_bin SDL2::SDL2 SDL2pp::SDL2pp Qt5::Core Qt5::Widgets yaml-cpp)

# Organize project files if using an IDE like Visual Studio or CLion
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${COMMON_SOURCES})
