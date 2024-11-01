cmake_minimum_required(VERSION 3.13)

if (POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)

project(taller_tp
    VERSION 1.0
    HOMEPAGE_URL "https://github.com/URL-HERE"
    LANGUAGES CXX
)

option(TALLER_TESTS "Enable / disable tests." ON)
option(TALLER_CLIENT "Enable / disable client program." ON)
option(TALLER_SERVER "Enable / disable server program." ON)
option(TALLER_EDITOR "Enable / disable editor program." ON)
option(TALLER_MAKE_WARNINGS_AS_ERRORS "Enable / disable warnings as errors." ON)

message(CMAKE_CXX_COMPILER_ID="${CMAKE_CXX_COMPILER_ID}")

add_library(common STATIC)  # Define the common target

add_subdirectory(common/)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(common ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

target_include_directories(common PUBLIC .)

if(TALLER_CLIENT OR TALLER_EDITOR)
    include(FetchContent)
    FetchContent_Declare(
        libSDL2pp
        URL https://github.com/libSDL2pp/libSDL2pp/archive/cc198c9a5657048bee67ece82de620b2d5661084.zip
    )

    FetchContent_MakeAvailable(libSDL2pp)
endif()

if(TALLER_CLIENT)
    add_executable(client_exe)  # Change the executable name to client_exe

    add_dependencies(client_exe common SDL2pp::SDL2pp)

    add_subdirectory(client)

    set_project_warnings(client_exe ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

    target_include_directories(client_exe PRIVATE ${libSDL2pp_SOURCE_DIR})

    target_link_libraries(client_exe common SDL2pp::SDL2pp SDL2 SDL2_image)
    
    add_custom_command(TARGET client_exe POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/client/SDL/img_src"
        "${CMAKE_BINARY_DIR}/img_src"
    )
endif()

if(TALLER_SERVER)
    add_executable(server_exe)  # Change the executable name to server_exe

    add_dependencies(server_exe common)

    add_subdirectory(server)

    set_project_warnings(server_exe ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

    target_link_libraries(server_exe common yaml-cpp)
endif()

if(TALLER_EDITOR)
    add_executable(editor_exe)  # Change the executable name to editor_exe

    add_dependencies(editor_exe common SDL2pp::SDL2pp)

    add_subdirectory(editor)

    set_project_warnings(editor_exe ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

    target_include_directories(editor_exe PRIVATE ${libSDL2pp_SOURCE_DIR})

    target_link_libraries(editor_exe common SDL2pp::SDL2pp)
endif()

if(TALLER_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)

    add_executable(tests_exe)  # Change the executable name to tests_exe

    add_dependencies(tests_exe common)

    target_include_directories(tests_exe PUBLIC .)

    add_subdirectory(tests)

    set_project_warnings(tests_exe ${TALLER_MAKE_WARNINGS_AS_ERRORS} TRUE)

    target_include_directories(tests_exe
        PUBLIC
        ${gtest_SOURCE_DIR}/include
        ${gmock_SOURCE_DIR}/include
    )

    target_link_libraries(tests_exe
        common
        GTest::gtest_main
    )
endif()
