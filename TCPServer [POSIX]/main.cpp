#include <iostream>
#include <iomanip>
#include "src/server/server.h"
#include "src/client/client.h"
#include "src/core/database/database.h"

/*
void test_db() {
    CDBConnection db("localhost", "logger", "root", "dbpassword");

    QueryResult a = db.get_record("show tables");
    QueryResultList b = db.get_record_list("select * from Logger");


    std::cout << std::endl;
    for (auto it = a.begin(); it != a.end(); it++)
        std::cout << (*it) << " ";

    std::cout << std::endl;

    for (auto it = b.begin(); it != b.end(); it++) {
        for (auto col = (*it).begin(); col != (*it).end(); col++)
            std::cout << (*col) << " ";
        std::cout << std::endl;
    }
}
*/

int main(int argc, char* argv[])
{
    time_t t = time(NULL);
    tm* aTm = localtime(&t);
    std::cout
            << "[START] TIME: "
            << aTm->tm_year+1900 << "/" << std::setfill ('0') << std::setw (2)
            << aTm->tm_mon+1 << "/" << std::setfill ('0') << std::setw (2)
            << aTm->tm_mday << " " << std::setfill ('0') << std::setw (2)
            << aTm->tm_hour << ":" << std::setfill ('0') << std::setw (2)
            << aTm->tm_min << ":" << std::setfill ('0') << std::setw (2)
            << aTm->tm_sec << std::endl;

<<<<<<< HEAD
    CServer s;
    // CClient s;
=======
    // CServer s;
    CClient s;
>>>>>>> origin/master
    s.start();

    // test_db();
    return 0;
}