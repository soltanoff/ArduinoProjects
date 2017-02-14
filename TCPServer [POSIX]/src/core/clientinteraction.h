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
    ClientInteraction(std::uint32_t client_number, SOCKET client_socket, bool is_gsm);  // , std::mutex& server_mutex);
    ~ClientInteraction() { close(); }

    int exec();
    void close();
private:
    std::uint32_t _client_number;
    SOCKET _client_socket;
    Functions _functions;
    bool _is_gsm;

    bool get_answer(std::int32_t& bytesRecv, char* answer);
    bool send_message(const char* msg);
    bool send_message(const char* msg, SOCKET s);

    template<class TFunc, class TObj>
    auto bind(TFunc&& fptr, TObj& optr) -> decltype(std::bind(fptr, optr, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)) {
        return std::bind(fptr, optr, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    }
};
/* ================================================================================================================== */
#endif /* SERVERTHREAD_H */
