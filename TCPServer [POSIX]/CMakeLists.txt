cmake_minimum_required(VERSION 3.6)
project(server)

set(CMAKE_CXX_STANDARD 14)

set(
        SOURCE_FILES
        main.cpp src/server/server.cpp
        src/client/client.cpp
        src/core/clientinteraction.cpp
        src/config/config.cpp
        src/core/commands/functions.cpp
        src/core/commands/scheduler.cpp
        src/core/database/database.cpp
        src/core/commands/functions.h)

add_definitions(-std=c++14 -O0 -g)

#link_libraries(-lmysqlclient)
#link_libraries(-lpthread)

add_executable(server ${SOURCE_FILES})
target_link_libraries(server pthread mysqlclient)

