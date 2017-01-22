#ifndef CLIENT_H
#define CLIENT_H
/* ================================================================================================================== */
#include "../config/config.h"
#include "interaction.h"
#include "connection.h"
/* ================================================================================================================== */


class Client: public BaseInteractionClass, public BaseConnectionClass {
public:
    Client();
    ~Client();

    int try_open_socket();
    int exec();
    void start();
    void close();
private:
    bool have_ip;

    void send_command();
    bool send_message(const char* msg);
    bool get_answer(int& bytesRecv, char* answer);

    void answer_control(char* answer);
    void ipaddres_control(char* ip);
};

#endif /* CLIENT_CLIENT_H */
