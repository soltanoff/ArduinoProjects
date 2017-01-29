#include "scheduler.h"


// ====================================================================================================================
// SERVICE FUNCTIONS
// function: get database connection
CDBConnection* get_db() {
    return new CDBConnection(
            ServerCfg::DB_ADDRESS,
            ServerCfg::DATABASE,
            ServerCfg::DB_USER,
            ServerCfg::DB_PASSWORD
    );
}
// ====================================================================================================================
// COMMAND FUNCTIONS
// cmd: help
std::string help(const std::string arg) {
    return std::string(
            "\nAvailable commands:\n"
                    "> test [{arg}] \t\t - function of the test. Return message.\n"
                    "> store {arg} \t\t - method of storing in DB send {args}.\n"
                    "> get_all \t\t\t - get all stored messages.\n"
                    "> get_read \t\t\t - get all read messages.\n"
                    "> get_unread \t\t - get all unread messages.\n"
                    "> set_read_all \t\t - set all messages as read.\n"
                    "> clear_db \t\t\t - set all messages as deleted.\n"
    );
}

// cmd: test
std::string test(const std::string arg) {
    if (arg.empty())
        std::cout << "foo() executed. arg = nullptr :)" << std::endl;
    else
        std::cout << "foo() executed. arg = " << arg << std::endl;

    return std::string(" > this is a test method");
}

// cmd: store <args>
std::string store(const std::string arg) {
    if (!arg.empty()) {
        CDBConnection *db = get_db();
        std::string query = "INSERT INTO Logger (message) VALUES (\'" + arg + "\')";
        db->query(query.c_str());
        delete db;
        return std::string(" > stored");
    }
    return std::string("not enough arguments.");
}

// cmd: get_all
std::string get_all(const std::string arg) {
    if (arg.empty()) {
        CDBConnection *db = get_db();
        std::string query = ""
                "SELECT l.id, l.message "
                "FROM Logger l INNER JOIN State s ON l.id = s.id_logger ";

        QueryResultList records = db->get_record_list(query.c_str());

        std::string result;
        for (auto it = records.begin(); it != records.end(); it++) {
            for (auto col = (*it).begin(); col != (*it).end(); col++)
                result += (*col) + " ";
            result += "\n";
        }

        delete db;
        return result;
    }
    return std::string(" > getall execute without arguments");
}

// cmd: get_read
std::string get_read(const std::string arg) {
    if (arg.empty()) {
        CDBConnection *db = get_db();
        std::string query = ""
                "SELECT l.id, l.message "
                "FROM Logger l INNER JOIN State s ON l.id = s.id_logger AND s.deleted = 0 "
                "WHERE s.is_read = 1";

        QueryResultList records = db->get_record_list(query.c_str());

        std::string result;
        for (auto it = records.begin(); it != records.end(); it++) {
            for (auto col = (*it).begin(); col != (*it).end(); col++)
                result += (*col) + " ";
            result += "\n";
        }

        delete db;
        return result;
    }
    return std::string(" > get_read execute without arguments");
}

// cmd: get_unread
std::string get_unread(const std::string arg) {
    if (arg.empty()) {
        CDBConnection *db = get_db();
        std::string query = ""
                "SELECT l.id, l.message "
                "FROM Logger l INNER JOIN State s ON l.id = s.id_logger AND s.deleted = 0 "
                "WHERE s.is_read = 0";

        QueryResultList records = db->get_record_list(query.c_str());

        std::string result;
        for (auto it = records.begin(); it != records.end(); it++) {
            for (auto col = (*it).begin(); col != (*it).end(); col++)
                result += (*col) + " ";
            result += "\n";
        }

        query = ""
                "UPDATE "
                "Logger l INNER JOIN State s ON l.id = s.id_logger AND s.deleted = 0 "
                "SET s.is_read = 1, modify_date = CURRENT_TIMESTAMP "
                "WHERE s.is_read = 0 ";

        db->query(query.c_str());

        delete db;
        return result;
    }
    return std::string(" > get_read execute without arguments");
}

// cmd: set_read_all
std::string set_read_all(const std::string arg) {
    if (arg.empty()) {
        CDBConnection *db = get_db();
        std::string query = "UPDATE State SET is_read = 1, modify_date = CURRENT_TIMESTAMP";
        db->query(query.c_str());
        delete db;
        return std::string(" > all data is read");
    }
    return std::string(" > clear_db execute without arguments");
}

// cmd: clear_db
std::string clear_db(const std::string arg) {
    if (arg.empty()) {
        CDBConnection *db = get_db();
        std::string query = "UPDATE State SET deleted = 1, modify_date = CURRENT_TIMESTAMP";
        db->query(query.c_str());
        delete db;
        return std::string(" > database cleared");
    }
    return std::string(" > clear_db execute without arguments");
}
