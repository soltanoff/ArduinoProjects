#ifndef CONNECTION_H
#define CONNECTION_H
/* ================================================================================================================== */
#include "../config/config.h"
/* ================================================================================================================== */
class CBaseConnectionClass {
public:
    virtual int try_open_socket() = 0;
    virtual void start() = 0;

    ~CBaseConnectionClass() = default;
protected:
    // WSADATA wsaData; // содержит информацию о реализации сокетов Windows
    SOCKET m_socket; // создаем сокет
    sockaddr_in service;
};
/* ================================================================================================================== */
#endif /* CONNECTION_H */
