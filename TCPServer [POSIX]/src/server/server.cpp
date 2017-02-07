#include "server.h"


void thread_routine(int client_number, SOCKET client_socket) {  // , std::mutex& main_mutex) {
    ClientInteraction client(client_number, client_socket); // , main_mutex);

    while (true) {
        try {
            int code = client.exec();
            if (code == -1) {
                client.close();
                return;
            }
        }
        catch (int) {
            client.close();
            return;
        }
        catch (...) {
            std::cout << "[ERROR] Server get error in thread_routine().\n";
            client.close();
            return;
        }
    }
}

CServer::CServer() {
    m_socket = socket(AF_INET, SOCK_STREAM, ServerCfg::PROTOCOL);
    // в качестве параметров используются семейство интернет-адресов (IP),
    // потоковые сокеты и протокол TCP/IP.

    if (m_socket < 0)
    {
        std::cout << "[ERROR: SOCKET] Error at socket()" << std::endl;
        /*
        #if defined(_WIN32) || defined(_WIN64)
                system("pause");
        #else
                system("sleep 1000");
        #endif
        */
        return;
    }

    std::cout << "[STATUS] Server ready.\n";
}

CServer::~CServer() {
    close();
}

void CServer::accept_socket(SOCKET& AcceptSocket, sockaddr_in& ClientInfo) {
    int adrlen = sizeof(ClientInfo);
    AcceptSocket = (SOCKET) SOCKET_ERROR;

    while (AcceptSocket == SOCKET_ERROR)
        AcceptSocket = accept(m_socket, (sockaddr* )& ClientInfo, (socklen_t *) &adrlen);
}

void CServer::connect_user(SOCKET& AcceptSocket, sockaddr_in& ClientInfo, int count) {
    std::cout << "[SERVER] Client #" << count + 1 << " connected. " << inet_ntoa(ClientInfo.sin_addr) << std::endl;
    send(AcceptSocket, "ACCEPT", strlen("ACCEPT"), 0);

    // std::thread* thread = new std::thread(thread_routine, count, AcceptSocket);
    std::shared_ptr<std::thread> thread(new std::thread(thread_routine, count, AcceptSocket));  // , _main_mutex));

    _client_ips.push_back(inet_ntoa(ClientInfo.sin_addr));
    _client_sockets.push_back(AcceptSocket);
    _client_threads.push_back(thread);
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
        // system("pause");
        return -1;
    }
    /* ========================================================================================================== */
    if (listen(m_socket, ServerCfg::BACKLOG) == SOCKET_ERROR)
    {
        std::cout << "[ERROR: LISTEN] Error listening on socket.\n";
        // system("pause");
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
            std::cout << "[ERROR] Server get error in CServer::exec().\n";
            close();
            return 0;
        }
    }
}

void CServer::start() {
    std::cout << "[STATUS] Server started.\n";
    std::cout << "[SERVER] Waiting for a client to connect...\n";

    if (try_open_socket() >= 0)
        exec();
}

void CServer::close() {
    shutdown(m_socket, 1);
}