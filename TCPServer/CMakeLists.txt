# ====================================================================================================================
cmake_minimum_required(VERSION 3.6)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/server.cpp src/clientinteraction.cpp src/config.cpp)
add_executable(untitled ${SOURCE_FILES})

if(WIN32)
    target_link_libraries(untitled wsock32 ws2_32)
endif()