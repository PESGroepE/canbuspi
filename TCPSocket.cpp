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

            uint8_t sluisdeuren[8] = {0, 0};
            const char *deuren = body.c_str();
            if (deuren[0]=='1') {
                sluisdeuren[0]=1;
            }
            if (deuren[1]=='1') {
                sluisdeuren[1]=1;
            }
            uint8_t *ps = sluisdeuren;
            can->sendMessage(12, 2, ps);

            uint8_t trappenhuis[8] = {0};
            if (deuren[2]=='1') {
                trappenhuis[0]=1;
            }
            uint8_t *pt = trappenhuis;
            can->sendMessage(13, 1, pt);
        }
        if (data.substr(0, d)=="brand") {
            std::string body = data.substr(d+1, data.size());
            std::cout<<body<<std::endl;

            if (body=="1") {
                uint8_t candata[8] = {1};
                can->sendMessage(2, 1, candata);
            } else {
                uint8_t candata[8] = {0};
                can->sendMessage(2, 1, candata);
            }
        }
    }
}

int TCPSocket::sendMessage(std::string data) {
    return send(clientSocket, data.c_str(), strlen(data.c_str()), 0);
}

