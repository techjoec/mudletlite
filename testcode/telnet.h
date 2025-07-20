
#pragma once
#include <string>

class TelnetConnection {
public:
    TelnetConnection(const std::string& host, int port);
    bool connect();
    bool read(std::string& output);
    void send(const std::string& input);

private:
    std::string host_;
    int port_;
    int sock_;
};
