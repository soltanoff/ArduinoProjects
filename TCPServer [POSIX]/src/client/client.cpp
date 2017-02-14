#include "client.h"
#include <cstring>


CClient::CClient() {
    have_ip = false;
    m_socket = socket(AF_INET, SOCK_STREAM, ServerCfg::PROTOCOL);

    if (m_socket < 0)
    {
        std::cout << "[ERROR: SOCKET] Error at socket()" << std::endl;
        system("pause");
        return;
    }
    std::cout << "[STATUS] Client ready.\n";
}

CClient::~CClient() {
    close();
}

bool CClient::send_message(const char* msg) {
    send(m_socket, msg, strlen(msg), 0);
    return true;
}

void CClient::send_command() {
    std::string sendbuf;
    std::cout << "[CLIENT] Command: ";

    std::cin.clear();
    std::cin.sync();
    std::getline(std::cin, sendbuf);

    if (sendbuf.compare("exit") == 0) {
        throw 0;
    }
    int bytesSent = send_message(sendbuf.c_str());
    if (bytesSent < 0)
        throw 0;
}

bool CClient::get_answer(int& bytesRecv, char* answer) {
    bytesRecv = (int)recv(m_socket, answer, (size_t) ServerCfg::BUFF_SIZE, 0);
    if (bytesRecv == 0) {
        std::cout << "[CLIENT] Connection closed.\n";
        throw 0;
    }
    if (bytesRecv < 0) {
        std::cout << "[CLIENT] Connection lost.\n";
        throw 0;
    }
    return true;
}

void CClient::answer_control(char* answer) {
    while (true) {
        std::cin.getline(answer, 2, '\n');
        if ((strlen(answer) > 1 ||
             (answer[0] != 'Y' && answer[0] != 'N' && answer[0] != 'y' && answer[0] != 'n'))) {
            std::cout << "Error, try again: [Y/N] ";
            continue;
        } else break;
    }
}

void CClient::ipaddres_control(char* ip) {
    while (true) {
        std::cin.getline(ip, 17, '\n');
        if (inet_addr(ip) == INADDR_NONE) {
            std::cout << "Error, try again: ";
            continue;
        } else break;
    }
}

int CClient::try_open_socket() {
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
        return -1;
    }

    send_message("1");  // send client type
    return 0;
}

int CClient::exec() {
    int bytesRecv = SOCKET_ERROR;
    char recvbuf[ServerCfg::BUFF_SIZE] = "";

    while (true) {
        try {
            get_answer(bytesRecv, recvbuf);

            std::cout << "[SERVER] Bytes recv: " << bytesRecv << " > \n" << recvbuf << "\n";
            send_command();
        }
        catch (int){
            std::cout << "[CLIENT] Terminate.\n";
            close();
            return 0;
        }
        catch (...){
            std::cout << "[CLIENT] Client get error in CClient::exec().\n";
            close();
            return 0;
        }
    }
}

void CClient::start() {
    std::cout << "[STATUS] Client started.\n";
    std::cout << "[CLIENT] Try to connect...\n";

    if (try_open_socket() >= 0)
        exec();
}

void CClient::close() {
    shutdown(m_socket, 1);
}
