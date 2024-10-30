# Add this line to include all .cpp files from the common directory
file(GLOB COMMON_SOURCES ../common/*.cpp)

# Add this line to include all .h files from the common directory
file(GLOB COMMON_HEADERS ../common/*.h)

target_sources(client_exe  # Use the correct target name
    PRIVATE
    # .cpp files
    ${COMMON_SOURCES}  # Include all .cpp files from common
    main.cpp  
    client_protocol.cpp  
    client.cpp 
    sender.cpp 
    receiver.cpp
    PUBLIC
    # .h files
    ${COMMON_HEADERS}  # Include all .h files from common
    client_protocol.h
    client.h
    sender.h
    receiver.h
)

# Include the common directory for headers
target_include_directories(client_exe PRIVATE ../common)
