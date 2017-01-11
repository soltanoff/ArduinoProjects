#include "../lib/clientinteraction.h"


bool ClientInteraction::get_answer(int &bytesRecv, char *answer) {
    bytesRecv = recv(_client_socket, answer, ServerCfg::BUFF_SIZE, 0);
    if (bytesRecv == 0 || bytesRecv == WSAECONNRESET) {
        std::cout << "[SERVER] Client #" << _client_number + 1 << " disconnected.\n";
        return false;
    }
    if (bytesRecv < 0) {
        std::cout << "[SERVER] Connection lost with client #" << _client_number + 1 << std::endl;
        return false;
    }
    return true;
}

bool ClientInteraction::send_message(const char *msg) {
    MAIN_MUTEX.lock();
    send(_client_socket, msg, strlen(msg), 0);
    MAIN_MUTEX.unlock();
    return true;
}

int ClientInteraction::user_interact() {
    int bytesRecv = SOCKET_ERROR;
    char recvbuf[ServerCfg::BUFF_SIZE] = "";

    if (!get_answer(bytesRecv, recvbuf))
        return -1;

    std::string str;

    MAIN_MUTEX.lock();
    std::cout
            << "[Client #" << _client_number + 1
            << "] Bytes recv: " << bytesRecv << " | [MSG: " << recvbuf << "]\n";
    MAIN_MUTEX.unlock();

    str = "You send my message :) \"";
    str += recvbuf;
    str += "\"";

    send_message(str.c_str());


    return 0;
}