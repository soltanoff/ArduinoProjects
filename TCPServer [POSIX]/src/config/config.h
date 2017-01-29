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
extern std::vector<std::shared_ptr<std::thread>> CLIENT_THREADS;
extern std::vector<SOCKET> CLIENT_SOCKETS;
extern std::vector<char*> CLIENT_IPS;

namespace ServerCfg {
    const char LOCALHOST[] = "127.0.0.1";
    const u_short PORT = 8084;
    const int PROTOCOL = IPPROTO_TCP;
    const int BACKLOG = 1;
    const int BUFF_SIZE = 1024;
    // Database
    const std::string DB_ADDRESS = "127.0.0.1";
    const std::string DATABASE = "logger";
    const std::string DB_USER = "root";
    const std::string DB_PASSWORD = "dbpassword";
    const unsigned int port = 3306;
}
/* ================================================================================================================== */
#endif /* CONFIG_H */
