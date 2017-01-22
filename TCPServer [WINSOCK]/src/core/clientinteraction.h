#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H
/* ================================================================================================================== */
#include "../config/config.h"
#include "interaction.h"
/* ================================================================================================================== */
void thread_routine(int client_number, SOCKET client_socket);


class ClientInteraction: public BaseInteractionClass {
public:
    ClientInteraction(int client_number, SOCKET client_socket) :
            _client_number(client_number), _client_socket(client_socket) {}
    ~ClientInteraction() { close(); }

    int exec();
    void close();
private:
    int _client_number;
    SOCKET _client_socket;

    bool get_answer(int& bytesRecv, char* answer);
    bool send_message(const char* msg);
};
/* ================================================================================================================== */
#endif /* SERVERTHREAD_H */
