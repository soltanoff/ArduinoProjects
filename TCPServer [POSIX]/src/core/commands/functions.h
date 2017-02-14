#ifndef SERVER_FUNCTIONS_H
#define SERVER_FUNCTIONS_H
/* ================================================================================================================== */
#include "../database/database.h"
#include "../../config/config.h"
#include <memory>
/* ================================================================================================================== */


class Functions
{
public:
    // ====================================================================================================================
    typedef std::vector<std::uint8_t> DataVector;
    // typedef std::function<void(DataVector)> FuncArg;
    typedef std::function<void(DataVector, SOCKET)> FuncArg;
    // ====================================================================================================================
    // COMMAND FUNCTIONS
    // cmd: None
    void unknown(DataVector arg, FuncArg result_cb, SOCKET s);
    // cmd: help
    void help(DataVector arg, FuncArg result_cb, SOCKET s);
    // cmd: test
    void test(DataVector arg, FuncArg result_cb, SOCKET s);
    // cmd: store <args>
    void store(DataVector arg, FuncArg result_cb, SOCKET s);
    // cmd: get_all
    void get_all(DataVector arg, FuncArg result_cb, SOCKET s);
    // cmd: get_read
    void get_read(DataVector arg, FuncArg result_cb, SOCKET s);
    // cmd: get_unread
    void get_unread(DataVector arg, FuncArg result_cb, SOCKET s);
    // cmd: set_read_all
    void set_read_all(DataVector arg, FuncArg result_cb, SOCKET s);
    // cmd: clear_db
    void clear_db(DataVector arg, FuncArg result_cb, SOCKET s);
private:
    // ====================================================================================================================
    // SERVICE FUNCTIONS
    // function: get database connection
    static std::unique_ptr<CDBConnection> get_db();
};

#endif //SERVER_FUNCTIONS_H
