/**
@file TCPSocket.cpp
*/

#include "TCPSocket.h"

TCPSocket::TCPSocket(std::string h, int p, Canbus *c):host(h),port(p),can(c) {

}

int TCPSocket::init() {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    inet_pton(AF_INET, host.c_str(), &serverAddress.sin_addr);

    int status = connect(clientSocket, (struct sockaddr*)&serverAddress,
            sizeof(serverAddress));
    return status;
}

void TCPSocket::handle(std::string) {
    while(1) {
        char buffer[128] = { 0 };
        recv(clientSocket, buffer, sizeof(buffer), 0);
        std::string data = buffer;
        std::cout<<data<<std::endl;
        int d = data.find(':');
        if (data.substr(0, d)=="deuren") {
            std::string body = data.substr(d+1, data.size());
            std::cout<<body<<std::endl;
            if (body=="000") {
                uint8_t candata[8] = {0, 0};
                uint8_t *p = candata;
                can->sendMessage(12, 2, p);
            } else if (body=="100") {
                uint8_t candata[8] = {1, 0};
                uint8_t *p = candata;
                can->sendMessage(12, 2, p);
            } else if (body=="010") {
                uint8_t candata[8] = {0, 1};
                uint8_t *p = candata;
                can->sendMessage(12, 2, p);
            }
        }
    }
}

int TCPSocket::sendMessage(std::string data) {
    return send(clientSocket, data.c_str(), strlen(data.c_str()), 0);
}

