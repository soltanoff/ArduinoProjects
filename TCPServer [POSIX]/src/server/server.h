#ifndef SERVER_H
#define SERVER_H
/* ================================================================================================================== */
#include "../core/clientinteraction.h"
#include "../core/connection.h"
/* ================================================================================================================== */


class CServer: public IBaseConnection {
public:
    CServer();
    ~CServer();

    int try_open_socket();
    int exec();
    void start();
    void close();
private:
    std::vector<std::shared_ptr<std::thread>> _client_threads;
    std::vector<SOCKET> _client_sockets;
    std::vector<char*> _client_ips;
    // std::mutex _main_mutex;

    void accept_socket(SOCKET& AcceptSocket, sockaddr_in& ClientInfo);
    void connect_user(SOCKET& AcceptSocket, sockaddr_in& ClientInfo, int count);
};
/* ================================================================================================================== */
#endif /* SERVER_H */
