#ifndef CONFIG_H
#define CONFIG_H
/* ================================================================================================================== */
#include <vector>
#include <time.h>
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <mutex>
/* ================================================================================================================== */
#define SOCKET int
#define SOCKET_ERROR -1

extern std::mutex MAIN_MUTEX;

namespace ServerCfg {
    const char LOCALHOST[] = "127.0.0.1";
    const std::uint16_t PORT = 8082;
    const std::uint16_t PROTOCOL = IPPROTO_TCP;
    const std::uint16_t BACKLOG = 1;
    const std::uint16_t BUFF_SIZE = 4056;
    // Database
    const std::string DB_ADDRESS = "127.0.0.1";
    const std::string DATABASE = "logger";
    const std::string DB_USER = "root";
    const std::string DB_PASSWORD = "dbpassword";
    // const unsigned int port = 3306;
}
/* ================================================================================================================== */
#endif /* CONFIG_H */
