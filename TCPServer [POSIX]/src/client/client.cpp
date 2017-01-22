#include <cstring>
#include "client.h"


Client::Client() {
    //WSADATA wsaData; // содержит информацию о реализации сокетов Windows
    // int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    // MAKEWORD(2,2) данной функции запрашивает версию WinSock системы и
    // устанавливает ее как наивысшую допустимую версию сокетов Windows,
    // котора¤ может использоваться.

    // if (iResult != NO_ERROR)
    // {
    //    std::cout << "[ERROR: WSADATA] Error at WSAStartup()\n";
    //    WSACleanup();
    //    system("pause");
    //    return;
    //}

    have_ip = false;

    //SOCKET m_socket; // создаем сокет
    m_socket = socket(AF_INET, SOCK_STREAM, ServerCfg::PROTOCOL);
    // ¬ качестве параметров используютс¤ семейство интернет-адресов (IP),
    // потоковые сокеты и протокол TCP/IP.

    if (m_socket < 0)  // == INVALID_SOCKET)
    {
        std::cout << "[ERROR: SOCKET] Error at socket()" << std::endl;  // : " << WSAGetLastError() << std::endl;
        // WSAGetLastError возвращает номер последней возникнувшей ошибки
        // WSACleanup();
        system("pause");
        return;
    }
    std::cout << "[STATUS] Client ready.\n";
}

Client::~Client() {
    close();
}

bool Client::send_message(const char* msg) {
    send(m_socket, msg, strlen(msg), 0);
    return true;
}

void Client::send_command() {
    char sendbuf[ServerCfg::BUFF_SIZE];
    std::cin.clear();
    std::cin.sync();
    std::cout << "[CLIENT] Command: ";

    std::cin.getline(sendbuf, 256);

    if (strcmp(sendbuf, "exit") == 0) {
        throw 0;
    }
    int bytesSent = send_message(sendbuf);
    if (bytesSent < 0)
        throw 0;
}

bool Client::get_answer(int& bytesRecv, char* answer) {
    bytesRecv = recv(m_socket, answer, ServerCfg::BUFF_SIZE, 0);
    if (bytesRecv == 0) {  // || bytesRecv == WSAECONNRESET) {
        std::cout << "[CLIENT] Connection closed.\n";
        throw 0;
    }
    if (bytesRecv < 0) {
        std::cout << "[CLIENT] Connection lost.\n";
        throw 0;
    }
    return true;
}

void Client::answer_control(char* answer) {
    while (true) {
        std::cin >> answer;
        if ((strlen(answer) > 1 ||
             (answer[0] != 'Y' && answer[0] != 'N' && answer[0] != 'y' && answer[0] != 'n'))) {
            std::cout << "Error, try again: [Y/N] ";
            continue;
        } else break;
    }
}

void Client::ipaddres_control(char* ip) {
    while (true) {
        std::cin >> ip;
        if (inet_addr(ip) == INADDR_NONE) {
            std::cout << "Error, try again: ";
            continue;
        } else break;
    }
}

int Client::try_open_socket() {
    char answear[128];
    char ipaddres[16];

    if (!have_ip) {
        std::cout << "[CLIENT] Do you want to enter server IP address? [Y/N] ";
        answer_control(answear);
        if (answear[0] == 'N' || answear[0] == 'n') {
            strcpy(ipaddres, ServerCfg::LOCALHOST);
            std::cout << "[CLIENT] Connecting to server...\n";
        } else {
            std::cout << "[CLIENT] Enter server IP addres: ";
            ipaddres_control(ipaddres);
            std::cout << "[CLIENT] Try to connect to %s...\n", ipaddres;
        }
        have_ip = true;
    }
    // service содержит информаци¤ о семействе адресов,
    // IP адрес и номер порта
    service.sin_family = AF_INET; // семейство адресов »нтернет
    service.sin_addr.s_addr = inet_addr(ipaddres); // локальный IP
    service.sin_port = htons(ServerCfg::PORT); // номер порта

    if (connect(m_socket, (sockaddr *)& service, sizeof(service)) == SOCKET_ERROR) {
        std::cout << "[ERROR: sockaddr] Connection failed.\n";
        // closesocket(m_socket);
        // WSACleanup();
        return -1;
    }
    return 0;
}

int Client::exec() {
    int bytesRecv = SOCKET_ERROR;
    char recvbuf[ServerCfg::BUFF_SIZE] = "";

    while (true) {
        try {
            get_answer(bytesRecv, recvbuf);

            std::cout << "[SERVER] Bytes recv: " << bytesRecv << " | [MSG: " << recvbuf << "]\n";
            send_command();
        }
        catch (int){
            std::cout << "[CLIENT] Terminate.\n";
            close();
            return 0;
        }
        catch (...){
            std::cout << "[CLIENT] Client get error in Client::exec().\n";
            close();
            return 0;
        }
    }
}

void Client::start() {
    std::cout << "[STATUS] Client started.\n";
    std::cout << "[CLIENT] Try to connect...\n";

    if (try_open_socket() >= 0)
        exec();
}

void Client::close() {
    shutdown(m_socket, 1);
    // WSACleanup();
}