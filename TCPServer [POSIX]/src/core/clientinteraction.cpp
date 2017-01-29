#include <cstring>
#include "clientinteraction.h"
#include "commands/scheduler.h"


bool ClientInteraction::get_answer(int& bytesRecv, char* answer) {
    bytesRecv = recv(_client_socket, answer, ServerCfg::BUFF_SIZE, 0);
<<<<<<< HEAD
    if (bytesRecv == 0) {
        std::cout << "[SERVER] Client #" << _client_number + 1 << " disconnected.\n";
=======
    if (bytesRecv == 0) { // || bytesRecv == WSAECONNRESET) {
        std::cout << "[SERVER] CClient #" << _client_number + 1 << " disconnected.\n";
>>>>>>> origin/master
        throw 0;
    }
    if (bytesRecv < 0) {
        std::cout << "[SERVER] Connection lost with client #" << _client_number + 1 << std::endl;
        throw 0;
    }
    return true;
}

bool ClientInteraction::send_message(const char* msg) {
    MAIN_MUTEX.lock();
    send(_client_socket, msg, strlen(msg), 0);
    MAIN_MUTEX.unlock();
    return true;
}

int ClientInteraction::exec() {
    int bytesRecv = SOCKET_ERROR;
    char recvbuf[ServerCfg::BUFF_SIZE] = "";

    get_answer(bytesRecv, recvbuf);

    std::string str;

    MAIN_MUTEX.lock();
    std::cout
            << "[CClient #" << _client_number + 1
            << "] Bytes recv: " << bytesRecv << " | [MSG: " << recvbuf << "]\n";
    MAIN_MUTEX.unlock();

    std::string result = command_scheduler(std::string(recvbuf));

    if (result.empty())
        send_message(" ");
    else {
        send_message(result.c_str());
    }
    return 0;
}

void ClientInteraction::close() {
    shutdown(_client_socket, 1);
}