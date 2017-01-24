#include <iostream>
#include <iomanip>
// #include "src/server/server.h"
#include "src/client/client.h"
/*#include <QSqlQuery>
#include <QSqlDatabase>
#include <QtCore/QDateTime>
#include <QtCore/QCoreApplication>*/


int main(int argc, char* argv[])
{
    // QCoreApplication app(argc, argv);
    time_t t = time(NULL);
    tm* aTm = localtime(&t);
    std::cout
            << "[START] TIME: "  // %04d/%02d/%02d %02d:%02d:%02d\n",
            << aTm->tm_year+1900 << "/" << std::setfill ('0') << std::setw (2)
            << aTm->tm_mon+1 << "/" << std::setfill ('0') << std::setw (2)
            << aTm->tm_mday << " " << std::setfill ('0') << std::setw (2)
            << aTm->tm_hour << ":" << std::setfill ('0') << std::setw (2)
            << aTm->tm_min << ":" << std::setfill ('0') << std::setw (2)
            << aTm->tm_sec << std::endl;

    // CServer s;
    CClient s;
    s.start();
    /*QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("logger");
    db.setUserName("dbuser");
    db.setPassword("dbpassword");
    db.open();

    QSqlQuery* query = new QSqlQuery(db);
    query->exec("SELECT * FROM logger");

    db.close();*/
    // system("pause");
    return 0;
}