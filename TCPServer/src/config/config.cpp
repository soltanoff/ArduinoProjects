#include "config.h"


std::mutex MAIN_MUTEX;
std::vector<std::thread*> CLIENT_THREADS;
std::vector<SOCKET> CLIENT_SOCKETS;
std::vector<CHAR*> CLIENT_IPS;