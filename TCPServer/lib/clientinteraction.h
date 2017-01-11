#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H
/* ================================================================================================================== */
#include "config.h"
/* ================================================================================================================== */
void thread_routine(int client_number, SOCKET client_socket);
/* ================================================================================================================== */
class ClientInteraction {
private:
    int _client_number;
    SOCKET _client_socket;
public:
    ClientInteraction(int client_number, SOCKET client_socket) :
            _client_number(client_number), _client_socket(client_socket) {}
    /* ============================================================================================================== */
    bool get_answer(int &bytesRecv, char *answer);
    bool send_message(const char *msg);
    int user_interact();
    /* ============================================================================================================== */
};
/* ================================================================================================================== */
#endif /* SERVERTHREAD_H */
