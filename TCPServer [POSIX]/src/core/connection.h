/* =====================================================================================================================
 * File: connection.h
 * Description: Базовый интерфейс описывающий подключение к сети
 * Created: 01.02.2017
 * Author: soltanoff
 * ================================================================================================================== */
#ifndef CONNECTION_H
#define CONNECTION_H
/* ================================================================================================================== */
#include "../config/config.h"
/* ================================================================================================================== */
/*!
 * @interface IBaseConnection
 * Абстрактный класс описывающий основные поля и методы для реализации подключения по протоколу TCP/IP
 */
class IBaseConnection {
public:
    virtual ~IBaseConnection() = default;
    /*!
     * @public Метод осуществляющий инициализацию сокета и дальнейшего подключения к серверу.
     * @return 0 если открыть сокет получилось, иначе -1
     * @note Содержит в себе логику настроки сетевого подключения
     */
    virtual int try_open_socket() = 0;
    /*!
    * @public Метод позволяющий начать работу сетевой части.
    * @return None
    * @note запуск метода IBaseConnection::try_open_socket()
    */
    virtual void start() = 0;
protected:
    //! @protected сокет открытого подключения по протоколу TCP/IP
    SOCKET m_socket;
    //! @protected структура конфигураций подключения сети
    sockaddr_in service;
};
/* ================================================================================================================== */
#endif /* CONNECTION_H */
