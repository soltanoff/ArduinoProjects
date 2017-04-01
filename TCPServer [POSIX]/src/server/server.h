#ifndef SERVER_H
#define SERVER_H
/* ================================================================================================================== */
#include "../core/clientinteraction.h"
#include "../core/connection.h"
/* ================================================================================================================== */
extern std::vector<SOCKET> GSM_MODULES_SOCKETS;
enum class CLIENT_TYPES : std::uint32_t {
    simple=1,
    gsm
};

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

    bool is_gsm_client(const SOCKET& AcceptSocket, const int& client_number);
    void accept_socket(SOCKET& AcceptSocket, sockaddr_in& ClientInfo);
    void connect_user(const SOCKET& AcceptSocket, const sockaddr_in& ClientInfo, const std::uint32_t& count);
};
/* ================================================================================================================== */
#endif /* SERVER_H */
