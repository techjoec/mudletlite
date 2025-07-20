
#include "telnet.h"
#include <iostream>
#include <thread>

int main() {
    TelnetConnection conn("realmsofdespair.com", 4000);
    conn.connect();

    std::thread reader([&]() {
        std::string line;
        while (conn.read(line)) {
            std::cout << line;
        }
    });

    std::string input;
    while (std::getline(std::cin, input)) {
        conn.send(input + "\n");
    }

    reader.join();
    return 0;
}
