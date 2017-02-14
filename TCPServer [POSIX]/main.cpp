#include "src/server/server.h"
#include "src/client/client.h"
#include <iostream>
#include <iomanip>

// TODO: [+] 1) disable client
// TODO: [+] 2) client disconnect
// TODO: [-] 3) client ping
// TODO: [?] 4) detect disconnected clients

int main(int argc, char* argv[]) {
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

    CServer s;
    // CClient s;
    s.start();

    return 0;
}