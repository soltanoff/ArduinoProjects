#ifndef SERVER_H
#define SERVER_H
/* ================================================================================================================== */
#include "../core/clientinteraction.h"
#include "../core/connection.h"
/* ================================================================================================================== */


class CServer: public CBaseConnectionClass {
public:
    CServer();
    ~CServer();

    int try_open_socket();
    int exec();
    void start();
    void close();
private:
    void accept_socket(SOCKET& AcceptSocket, sockaddr_in& ClientInfo);
    void connect_user(SOCKET& AcceptSocket, sockaddr_in& ClientInfo, int count);
};
/* ================================================================================================================== */
#endif /* SERVER_H */
