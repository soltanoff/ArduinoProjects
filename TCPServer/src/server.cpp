#include "../lib/server.h"


void thread_routine(int client_number, SOCKET client_socket) {
    ClientInteraction client(client_number, client_socket);


    while (true) {
        int code = client.user_interact();

        if (code == 1) continue;
        if (code == -1) break;
    }
    shutdown(client_socket, 0);
}

Server::Server()
{
    /* ================================================================= */
    // WSADATA wsaData; // содержит информацию о реализации сокетов Windows
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    // MAKEWORD(2,2) данной функции запрашивает версию WinSock системы и
    // устанавливает ее как наивысшую допустимую версию сокетов Windows

    if (iResult != NO_ERROR)
    {
        std::cout << "[ERROR: WSADATA] Error at WSAStartup()\n";
        WSACleanup();
        system("pause");
        return;
    }

    //SOCKET m_socket; // создаем сокет
    m_socket = socket(AF_INET, SOCK_STREAM, ServerCfg::PROTOCOL);
    // в качестве параметров используются семейство интернет-адресов (IP),
    // потоковые сокеты и протокол TCP/IP.

    if (m_socket == INVALID_SOCKET)
    {
        std::cout << "[ERROR: SOCKET] Error at socket(): " << WSAGetLastError() << std::endl;
        // WSAGetLastError возвращает номер последней возникнувшей ошибки
        WSACleanup();
        system("pause");
        return;
    }
    std::cout << "[STATUS] Server ready.\n";
}

Server::~Server()
{
    // ServerThreads::close_threads();
    // CloseHandle(ServerThreads::ghMutex);
    shutdown(m_socket, 1);
    WSACleanup();
}

void Server::accept_socket(SOCKET &AcceptSocket, sockaddr_in &ClientInfo)
{
    int adrlen = sizeof(ClientInfo);
    AcceptSocket = (SOCKET) SOCKET_ERROR;

    while (AcceptSocket == SOCKET_ERROR)
        AcceptSocket = accept(m_socket, (sockaddr* ) &ClientInfo, &adrlen);
}

void Server::connect_user(SOCKET &AcceptSocket, sockaddr_in &ClientInfo, int count)
{
    std::cout << "[SERVER] Client #" << count + 1 << " connected. " << inet_ntoa(ClientInfo.sin_addr) << std::endl;
    send(AcceptSocket, "ACCEPT", strlen("ACCEPT"), 0);


    std::thread *thread = new std::thread(thread_routine, count, AcceptSocket);

    CLIENT_IPS.push_back(inet_ntoa(ClientInfo.sin_addr));
    CLIENT_SOCKETS.push_back(AcceptSocket);
    CLIENT_THREADS.push_back(thread);
}

int Server::try_open_server()
{
    // service содержит информация о семействе адресов,
    // IP адрес и номер порта
    service.sin_family = AF_INET; // семейство адресов »нтернет
    service.sin_addr.s_addr = INADDR_ANY;
    service.sin_port = htons(ServerCfg::PORT); // номер порта

    if (bind(m_socket, (SOCKADDR*) &service, sizeof(service)) == SOCKET_ERROR)
    {
        std::cout << "[ERROR: SOCKADDR] bind() failed.\n";
        closesocket(m_socket);
        WSACleanup();
        system("pause");
        return -1;
    }
    /* ========================================================================================================== */
    if (listen(m_socket, ServerCfg::BACKLOG) == SOCKET_ERROR)
    {
        std::cout << "[ERROR: LISTEN] Error listening on socket.\n";
        WSACleanup();
        system("pause");
        return -1;
    }
    return 0;
}

int Server::exec()
{
    int count = 0;

    while (true)
    {
        SOCKET AcceptSocket;
        sockaddr_in ClientInfo;

        accept_socket(AcceptSocket, ClientInfo);

        connect_user(AcceptSocket, ClientInfo, count);
        count++;
    }
}

void Server::start()
{
    std::cout << "[STATUS] Server started.\n";
    std::cout << "[SERVER] Waiting for a client to connect...\n";

    if (try_open_server() >= 0)
        exec();
}