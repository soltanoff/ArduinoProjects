#include "clientinteraction.h"


ClientInteraction::ClientInteraction(int client_number, SOCKET client_socket) : // , std::mutex& server_mutex) :
        _client_number(client_number), _client_socket(client_socket) {
    // _main_mutex = &server_mutex;

    auto result_callback = [&](std::vector<std::uint8_t> data, SOCKET s) {
        std::cout << "[SERVER] SEND ANSWER" << std::endl;
        send_message((const char*)data.data(), s);
    };
    static auto shutdown_callback = [&](std::vector<std::uint8_t> data) {
        send_message((const char*)data.data());
        throw 1;
    };

    Scheduler::bind(COMMANDS::unknown, bind(&Functions::unknown, _functions), std::ref(result_callback));
    Scheduler::bind(COMMANDS::help, bind(&Functions::help, _functions), std::ref(result_callback));
    Scheduler::bind(COMMANDS::test, bind(&Functions::test, _functions), std::ref(result_callback));
    Scheduler::bind(COMMANDS::store, bind(&Functions::store, _functions), std::ref(result_callback));
    Scheduler::bind(COMMANDS::get_all, bind(&Functions::get_all, _functions), std::ref(result_callback));
    Scheduler::bind(COMMANDS::get_read, bind(&Functions::get_read, _functions), std::ref(result_callback));
    Scheduler::bind(COMMANDS::get_unread, bind(&Functions::get_unread, _functions), std::ref(result_callback));
    Scheduler::bind(COMMANDS::set_read_all, bind(&Functions::set_read_all, _functions), std::ref(result_callback));
    Scheduler::bind(COMMANDS::clear_db, bind(&Functions::clear_db, _functions), std::ref(result_callback));
    //Scheduler::bind(COMMANDS::shutdown, bind(&Functions::shutdown, _functions), std::ref(shutdown_callback));
}

bool ClientInteraction::get_answer(std::int32_t& bytesRecv, char* answer) {
    bytesRecv = (std::int32_t)recv(_client_socket, answer, ServerCfg::BUFF_SIZE, 0);
    if (bytesRecv == 0) {
        std::cout << "[SERVER] Client #" << _client_number + 1 << " disconnected.\n";
        throw 0;
    }
    if (bytesRecv < 0) {
        std::cout << "[SERVER] Connection lost with client #" << _client_number + 1 << std::endl;
        throw 0;
    }
    return true;
}

bool ClientInteraction::send_message(const char* msg) {
    std::lock_guard<decltype(MAIN_MUTEX)> scoped_lock(MAIN_MUTEX);
    // std::lock_guard<decltype(*_main_mutex)> scoped_lock(*_main_mutex);

    // std::cout << "send message: " << msg << std::endl;
    // std::string bytes = std::to_string((unsigned long long)strlen(msg));
    // send(_client_socket, bytes.data(), bytes.size(), 0);
    if (!strlen(msg))
        send(_client_socket, " > NONE", 7, 0);
    else
        send(_client_socket, msg, strlen(msg), 0);
    return true;
}

bool ClientInteraction::send_message(const char* msg, SOCKET s) {
    std::lock_guard<decltype(MAIN_MUTEX)> scoped_lock(MAIN_MUTEX);
    if (!strlen(msg))
        send(s, " > NONE", 7, 0);
    else
        send(s, msg, strlen(msg), 0);
    return true;
}

int ClientInteraction::exec() {
    std::int32_t bytesRecv = SOCKET_ERROR;
    char recvbuf[ServerCfg::BUFF_SIZE] = "";

    get_answer(bytesRecv, recvbuf);

    std::string str;

    {
        std::lock_guard<decltype(MAIN_MUTEX)> scoped_lock(MAIN_MUTEX);
        // std::lock_guard<decltype(*_main_mutex)> scoped_lock(*_main_mutex);
        std::cout
                << "[Client #" << _client_number + 1
                << "] Bytes recv: " << bytesRecv << " | [MSG: " << recvbuf << "]\n";
    }

    if (!Scheduler::schedule(std::vector<std::uint8_t>(recvbuf, recvbuf + bytesRecv), _client_socket)) {
        std::cout << "[SERVER] Client command is not execute. \n";
        send_message(" > command is not execute (maybe unknown)");
    }

    /*
    std::string result = command_scheduler(std::string(recvbuf));
    if (result.empty())
        send_message(" ");
    else {
        send_message(result.c_str());
    }
    */
    return 0;
}

void ClientInteraction::close() {
    shutdown(_client_socket, 1);
}