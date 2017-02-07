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
    typedef std::function<void(DataVector)> FuncArg;
    // ====================================================================================================================
    // COMMAND FUNCTIONS
    // cmd: None
    void unknown(DataVector arg, FuncArg result_cb);
    // cmd: help
    void help(DataVector arg, FuncArg result_cb);
    // cmd: test
    void test(DataVector arg, FuncArg result_cb);
    // cmd: store <args>
    void store(DataVector arg, FuncArg result_cb);
    // cmd: get_all
    void get_all(DataVector arg, FuncArg result_cb);
    // cmd: get_read
    void get_read(DataVector arg, FuncArg result_cb);
    // cmd: get_unread
    void get_unread(DataVector arg, FuncArg result_cb);
    // cmd: set_read_all
    void set_read_all(DataVector arg, FuncArg result_cb);
    // cmd: clear_db
    void clear_db(DataVector arg, FuncArg result_cb);
    // cmd: shutdown
    void shutdown(DataVector arg, FuncArg result_cb);
private:
    // ====================================================================================================================
    // SERVICE FUNCTIONS
    // function: get database connection
    static std::unique_ptr<CDBConnection> get_db();
};

#endif //SERVER_FUNCTIONS_H
