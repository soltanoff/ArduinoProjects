#ifndef CONFIG_H
#define CONFIG_H
/* ================================================================================================================== */
#include <vector>
#include <time.h>
#include <string>
#include <iostream>
#include <winsock.h>
#include <thread>
#include <mutex>
/* ================================================================================================================== */
extern std::mutex MAIN_MUTEX;
extern std::vector<std::thread*> CLIENT_THREADS;
extern std::vector<SOCKET> CLIENT_SOCKETS;
extern std::vector<CHAR*> CLIENT_IPS;

namespace ServerCfg {
    const u_short PORT = 8082;
    const int PROTOCOL = IPPROTO_TCP;
    const int BACKLOG = 1;
    const int BUFF_SIZE = 1024;
}
/* ================================================================================================================== */
#endif /* CONFIG_H */
