#include "scheduler.h"
#include "functions.h"


// ====================================================================================================================
// SERVICE FUNCTIONS
// function: get database connection
std::unique_ptr<CDBConnection> Functions::get_db() {
    return std::make_unique<CDBConnection>(
            ServerCfg::DB_ADDRESS,
            ServerCfg::DATABASE,
            ServerCfg::DB_USER,
            ServerCfg::DB_PASSWORD
    );
}
// ====================================================================================================================
// COMMAND FUNCTIONS
// cmd: None
void Functions::unknown(DataVector arg, FuncArg result_cb, SOCKET s) {
    std::string str = {" > unknown command"};
    result_cb(DataVector(str.begin(), str.end() + 1), s);
}

// cmd: help
void Functions::help(DataVector arg, FuncArg result_cb, SOCKET s) {
    std::string str = {"\n\rAvailable commands:\n\r"
                        "> test [{arg}] \t\t - function of the test. Return message.\n\r"
                        "> store {arg} \t\t - method of storing in DB send {args}.\n\r"
                        "> get_all \t\t\t - get all stored messages.\n\r"
                        "> get_read \t\t\t - get all read messages.\n\r"
                        "> get_unread \t\t - get all unread messages.\n\r"
                        "> set_read_all \t\t - set all messages as read.\n\r"
                        "> clear_db \t\t\t - set all messages as deleted.\n\r"};
    result_cb(std::vector<std::uint8_t>(str.begin(), str.end() + 1), s);
}

// cmd: test
void Functions::test(DataVector arg, FuncArg result_cb, SOCKET s) {
    std::string str_arg(arg.begin(), arg.end());

    if (str_arg.empty())
        std::cout << "foo() executed. arg = nullptr :)" << std::endl;
    else
        std::cout << "foo() executed. arg = " << str_arg << std::endl;

    std::string str = {" > this is a test method"};
    result_cb(DataVector(str.begin(), str.end() + 1), s);
}

// cmd: store <args>
void Functions::store(DataVector arg, FuncArg result_cb, SOCKET s) {
    std::string str_arg(arg.begin(), arg.end());

    std::string str;
    if (!str_arg.empty()) {
        auto db = get_db();
        std::string query = "INSERT INTO Logger (message) VALUES (\'" + str_arg + "\')";
        db->query(query.c_str());
        str = " > stored";
    }
    else
        str = "not enough arguments.";

    result_cb(DataVector(str.begin(), str.end() + 1), s);
}

// cmd: get_all
void Functions::get_all(DataVector arg, FuncArg result_cb, SOCKET s) {
    std::string str_arg(arg.begin(), arg.end());
    std::string result;

    if (arg.empty()) {
        auto db = get_db();
        std::string query = ""
                "SELECT l.id, l.message "
                "FROM Logger l INNER JOIN State s ON l.id = s.id_logger ";
        QueryResultList records = db->get_record_list(query.c_str());

        for (auto it = records.begin(); it != records.end(); it++) {
            for (auto col = (*it).begin(); col != (*it).end(); col++)
                result += (*col) + " ";
            result += "\n";
        }
    }
    else
        result = " > getall execute without arguments";

    result_cb(DataVector(result.begin(), result.end() + 1), s);
}

// cmd: get_read
void Functions::get_read(DataVector arg, FuncArg result_cb, SOCKET s) {
    std::string str_arg(arg.begin(), arg.end());
    std::string result;

    if (arg.empty()) {
        auto db = get_db();
        std::string query = ""
                "SELECT l.id, l.message "
                "FROM Logger l INNER JOIN State s ON l.id = s.id_logger AND s.deleted = 0 "
                "WHERE s.is_read = 1";
        QueryResultList records = db->get_record_list(query.c_str());

        for (auto it = records.begin(); it != records.end(); it++) {
            for (auto col = (*it).begin(); col != (*it).end(); col++)
                result += (*col) + " ";
            result += "\n";
        }
    }
    else
        result = " > get_read execute without arguments";

    result_cb(DataVector(result.begin(), result.end() + 1), s);
}

// cmd: get_unread
void Functions::get_unread(DataVector arg, FuncArg result_cb, SOCKET s) {
    std::string str_arg(arg.begin(), arg.end());
    std::string result;

    if (arg.empty()) {
        auto db = get_db();
        std::string query = ""
                "SELECT l.id, l.message "
                "FROM Logger l INNER JOIN State s ON l.id = s.id_logger AND s.deleted = 0 "
                "WHERE s.is_read = 0";

        QueryResultList records = db->get_record_list(query.c_str());

        for (auto it = records.begin(); it != records.end(); it++) {
            for (auto col = (*it).begin(); col != (*it).end(); col++)
                result += (*col) + " ";
            result += "\n";
        }
        query = "UPDATE State SET is_read = 1, modify_date = CURRENT_TIMESTAMP";
        db->query(query.c_str());
    }
    else
        result = " > get_unread execute without arguments";

    result_cb(DataVector(result.begin(), result.end() + 1), s);
}

// cmd: set_read_all
void Functions::set_read_all(DataVector arg, FuncArg result_cb, SOCKET s) {
    std::string str_arg(arg.begin(), arg.end());
    std::string result;

    if (arg.empty()) {
        auto db = get_db();
        std::string query = "UPDATE State SET is_read = 1, modify_date = CURRENT_TIMESTAMP";
        db->query(query.c_str());
        result = " > all data is read";
    }
    else
        result = " > clear_db execute without arguments";

    result_cb(DataVector(result.begin(), result.end() + 1), s);
}

// cmd: clear_db
void Functions::clear_db(DataVector arg, FuncArg result_cb, SOCKET s) {
    std::string str_arg(arg.begin(), arg.end());
    std::string result;

    if (arg.empty()) {
        auto db = get_db();
        std::string query = "UPDATE State SET deleted = 1, modify_date = CURRENT_TIMESTAMP";
        db->query(query.c_str());
        result = " > database cleared";
    }
    else
        result = " > clear_db execute without arguments";

    result_cb(DataVector(result.begin(), result.end() + 1), s);
}
