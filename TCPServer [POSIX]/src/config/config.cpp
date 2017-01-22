#include "config.h"


std::mutex MAIN_MUTEX;
std::vector<std::shared_ptr<std::thread>> CLIENT_THREADS;
std::vector<SOCKET> CLIENT_SOCKETS;
std::vector<char*> CLIENT_IPS;