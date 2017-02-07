#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H
/* ================================================================================================================== */
#include "../config/config.h"
#include "../core/commands/scheduler.h"
#include "../core/commands/functions.h"
#include "interaction.h"
/* ================================================================================================================== */


class ClientInteraction: public IBaseInteraction {
public:
    ClientInteraction(int client_number, SOCKET client_socket);  // , std::mutex& server_mutex);
    ~ClientInteraction() { close(); }

    int exec();
    void close();
private:
    int _client_number;
    SOCKET _client_socket;
    Functions _functions;
    // std::mutex* _main_mutex;

    bool get_answer(std::int32_t& bytesRecv, char* answer);
    bool send_message(const char* msg);

    template<class TFunc, class TObj>
    auto bind(TFunc&& fptr, TObj& optr) -> decltype(std::bind(fptr, optr, std::placeholders::_1, std::placeholders::_2)) {
        return std::bind(fptr, optr, std::placeholders::_1, std::placeholders::_2);
    }
};
/* ================================================================================================================== */
#endif /* SERVERTHREAD_H */
