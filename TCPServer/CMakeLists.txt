# ====================================================================================================================
cmake_minimum_required(VERSION 3.6)
project(server)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/server/server.cpp src/core/clientinteraction.cpp src/config/config.cpp)
add_executable(server ${SOURCE_FILES})

if(WIN32)
    target_link_libraries(server wsock32 ws2_32)
endif()