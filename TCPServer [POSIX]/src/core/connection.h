#ifndef CONNECTION_H
#define CONNECTION_H
/* ================================================================================================================== */
#include "../config/config.h"
/* ================================================================================================================== */
class IBaseConnection {
public:
    virtual int try_open_socket() = 0;
    virtual void start() = 0;

    ~IBaseConnection() = default;
protected:
    SOCKET m_socket; // создаем сокет
    sockaddr_in service;
};
/* ================================================================================================================== */
#endif /* CONNECTION_H */
