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
    receiver.cpp  # Assuming receiver.cpp is the receiver implementation

    PUBLIC
    # .h files
    ${COMMON_HEADERS}  # Include all .h files from common
      # Include only protocol.h from the client directory
    client_protocol.h
    receiver.h
)

# Include the common directory for headers
target_include_directories(client_exe PRIVATE ../common)
