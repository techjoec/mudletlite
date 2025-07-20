
#include "telnet.h"

#ifdef _WIN32
  #include <winsock2.h>
  #include <ws2tcpip.h>
  #pragma comment(lib, "ws2_32.lib")
  #include <cstring>
#else
  #include <sys/socket.h>
  #include <arpa/inet.h>
  #include <netdb.h>
  #include <unistd.h>
  #include <cstring>
#endif

#include <iostream>

TelnetConnection::TelnetConnection(const std::string& host, int port)
    : host_(host), port_(port), sock_(-1) {}

bool TelnetConnection::connect() {
#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "WSAStartup failed.\n";
        return false;
    }
#endif

    struct hostent* server = gethostbyname(host_.c_str());
    if (!server) return false;

    struct sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_);
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_ < 0) return false;
    if (::connect(sock_, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        return false;

    return true;
}

bool TelnetConnection::read(std::string& output) {
    char buffer[2048];
#ifdef _WIN32
    int n = recv(sock_, buffer, sizeof(buffer) - 1, 0);
#else
    ssize_t n = recv(sock_, buffer, sizeof(buffer) - 1, 0);
#endif
    if (n <= 0) return false;
    buffer[n] = 0;
    output = std::string(buffer);
    return true;
}

void TelnetConnection::send(const std::string& input) {
    ::send(sock_, input.c_str(), static_cast<int>(input.size()), 0);
}
