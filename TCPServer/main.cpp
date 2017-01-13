#include <iostream>
#include <iomanip>
#include "lib/server.h"


int main()
{
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

    Server s;
    s.start();

    system("pause");
    return 0;
}