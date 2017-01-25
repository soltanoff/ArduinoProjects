#ifndef DATABASE_H
#define DATABASE_H

#include <mysql/mysql.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::string> QueryResult;
typedef std::vector<std::vector<std::string>> QueryResultList;

class CDBConnection {
public:
    CDBConnection() {};
    CDBConnection(
            const std::string server,
            const std::string database,
            const std::string user,
            const std::string password,
            const unsigned int port = 0
    );
    ~CDBConnection() { close(); };

    bool connect(
            const std::string server,
            const std::string database,
            const std::string user,
            const std::string password,
            const unsigned int port = 0
    );
    void reconnnect();
    void close();

    MYSQL_RES* query(const char* stmt);
    QueryResult get_record(const char* stmt);
    QueryResultList get_record_list(const char* stmt);
private:
    MYSQL* _connection;

    unsigned int _port;
    std::string _server;
    std::string _database;

    std::string _user;
    std::string _password;
};
#endif /* DATABASE_H */
