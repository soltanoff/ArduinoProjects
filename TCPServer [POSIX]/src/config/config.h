/* =====================================================================================================================
 * File: config.h
 * Description: Файл основных конфигураций сервера
 * Created: 03.02.2017
 * Author: soltanoff
 * ================================================================================================================== */
#ifndef CONFIG_H
#define CONFIG_H
/* ================================================================================================================== */
#include <vector>
#include <time.h>
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <mutex>
/* ================================================================================================================== */
#define SOCKET int
#define SOCKET_ERROR -1
//! основной мьютекс, синхронизирующий ввод и вывод данных в консоль сервера
extern std::mutex MAIN_MUTEX;
/*!
 * @namespace ServerCfg
 * Основные константы конфигурации сервера
 */
namespace ServerCfg {
    //! локальный ip-адрес сервера
    const char LOCALHOST[] = "127.0.0.1";
    //! используемый порт сервера
    const std::uint16_t PORT = 8082;
    //! тип протокола сервера
    const std::uint16_t PROTOCOL = IPPROTO_TCP;
    //! флаг ошибки открытия сокета (ошибка прослушивания)
    const std::uint16_t BACKLOG = 1;
    //! размер буфера отправляемых и получаемых данных
    const std::uint16_t BUFF_SIZE = 4056;
    //! @details основные параметры базы данных сервера
    //! ip-адрес сервера
    const std::string DB_ADDRESS = "127.0.0.1";
    //! имя используемой базы данных
    const std::string DATABASE = "logger";
    //! логин пользователя БД
    const std::string DB_USER = "root";
    //! пароль пользователя БД
    const std::string DB_PASSWORD = "dbpassword";
    // const unsigned int port = 3306;
}
/* ================================================================================================================== */
#endif /* CONFIG_H */
