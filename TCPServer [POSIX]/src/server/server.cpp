#include <cstring>
#include "server.h"


void thread_routine(int client_number, SOCKET client_socket) {
    ClientInteraction client(client_number, client_socket);

    while (true) {
        try {
            int code = client.exec();
            if (code == -1) return;
        }
        catch (int) {
            client.close();
            return;
        }
        catch (...) {
            std::cout << "[ERROR] CServer get error in thread_routine().\n";
            client.close();
            return;
        }
    }
}

CServer::CServer() {
<<<<<<< HEAD
=======
    // WSADATA wsaData; // содержит информацию о реализации сокетов Windows
    // int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    // MAKEWORD(2,2) данной функции запрашивает версию WinSock системы и
    // устанавливает ее как наивысшую допустимую версию сокетов Windows

    // if (iResult != NO_ERROR)
    // {
    //    std::cout << "[ERROR: WSADATA] Error at WSAStartup()\n";
    //    WSACleanup();
    //    system("pause");
    //    return;
    // }

    //SOCKET m_socket; // создаем сокет
>>>>>>> origin/master
    m_socket = socket(AF_INET, SOCK_STREAM, ServerCfg::PROTOCOL);
    // в качестве параметров используются семейство интернет-адресов (IP),
    // потоковые сокеты и протокол TCP/IP.

    if (m_socket < 0)
    {
        std::cout << "[ERROR: SOCKET] Error at socket()" << std::endl;
        system("pause");
        return;
    }
    std::cout << "[STATUS] CServer ready.\n";
}

CServer::~CServer() {
<<<<<<< HEAD
=======
    // ServerThreads::close_threads();
    // CloseHandle(ServerThreads::ghMutex);
>>>>>>> origin/master
    close();
}

void CServer::accept_socket(SOCKET& AcceptSocket, sockaddr_in& ClientInfo) {
    int adrlen = sizeof(ClientInfo);
    AcceptSocket = (SOCKET) SOCKET_ERROR;

    while (AcceptSocket == SOCKET_ERROR)
        AcceptSocket = accept(m_socket, (sockaddr* )& ClientInfo, (socklen_t *) &adrlen);
}

void CServer::connect_user(SOCKET& AcceptSocket, sockaddr_in& ClientInfo, int count) {
<<<<<<< HEAD
    std::cout << "[SERVER] Client #" << count + 1 << " connected. " << inet_ntoa(ClientInfo.sin_addr) << std::endl;
=======
    std::cout << "[SERVER] CClient #" << count + 1 << " connected. " << inet_ntoa(ClientInfo.sin_addr) << std::endl;
>>>>>>> origin/master
    send(AcceptSocket, "ACCEPT", strlen("ACCEPT"), 0);

    // std::thread* thread = new std::thread(thread_routine, count, AcceptSocket);
    std::shared_ptr<std::thread> thread(new std::thread(thread_routine, count, AcceptSocket));

    CLIENT_IPS.push_back(inet_ntoa(ClientInfo.sin_addr));
    CLIENT_SOCKETS.push_back(AcceptSocket);
    CLIENT_THREADS.push_back(thread);
}

int CServer::try_open_socket() {
    // service содержит информация о семействе адресов,
    // IP адрес и номер порта
    service.sin_family = AF_INET; // семейство адресов »нтернет
    service.sin_addr.s_addr = INADDR_ANY;
    service.sin_port = htons(ServerCfg::PORT); // номер порта

    if (bind(m_socket, (sockaddr*)& service, sizeof(service)) == SOCKET_ERROR)
    {
        std::cout << "[ERROR: sockaddr] bind() failed.\n";
        system("pause");
        return -1;
    }
    /* ========================================================================================================== */
    if (listen(m_socket, ServerCfg::BACKLOG) == SOCKET_ERROR)
    {
        std::cout << "[ERROR: LISTEN] Error listening on socket.\n";
        system("pause");
        return -1;
    }
    return 0;
}

int CServer::exec() {
    int count = 0;

    while (true)
    {
        try {
            SOCKET AcceptSocket;
            sockaddr_in ClientInfo;

            accept_socket(AcceptSocket, ClientInfo);

            connect_user(AcceptSocket, ClientInfo, count);
            count++;
        }
        catch (...){
<<<<<<< HEAD
            std::cout << "[ERROR] Server get error in CServer::exec().\n";
=======
            std::cout << "[ERROR] CServer get error in CServer::exec().\n";
>>>>>>> origin/master
            close();
            return 0;
        }
    }
}

void CServer::start() {
<<<<<<< HEAD
    std::cout << "[STATUS] Server started.\n";
=======
    std::cout << "[STATUS] CServer started.\n";
>>>>>>> origin/master
    std::cout << "[SERVER] Waiting for a client to connect...\n";

    if (try_open_socket() >= 0)
        exec();
}

void CServer::close() {
    shutdown(m_socket, 1);
}