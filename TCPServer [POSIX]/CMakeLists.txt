# ====================================================================================================================
cmake_minimum_required(VERSION 3.6)
project(server)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/server/server.cpp src/client/client.cpp src/core/clientinteraction.cpp src/config/config.cpp src/core/commands/command.cpp src/core/commands/functions.cpp src/core/commands/scheduler.cpp)
add_executable(server ${SOURCE_FILES})

link_libraries(-lmysqlclient)
link_libraries(-lpthread)

target_link_libraries(server pthread)
