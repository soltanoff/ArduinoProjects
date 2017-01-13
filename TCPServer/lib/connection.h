#ifndef CONNECTION_H
#define CONNECTION_H
/* ================================================================================================================== */
#include "config.h"
/* ================================================================================================================== */
class BaseConnectionClass {
protected:
    WSADATA wsaData; // содержит информацию о реализации сокетов Windows
    SOCKET m_socket; // создаем сокет
    sockaddr_in service;
public:
    virtual int try_open_socket() = 0;
    virtual void start() = 0;
};
/* ================================================================================================================== */
#endif /* CONNECTION_H */
