#ifndef CANBUSPI_TCPSOCKET_H
#define CANBUSPI_TCPSOCKET_H

#include <string>
#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

#include "Canbus.h"

class TCPSocket {
public:
    TCPSocket(std::string, int, Canbus*);

    int init();
    void handle(std::string);
    int sendMessage(std::string);
private:
    std::string host;
    int port;
    int clientSocket;
    sockaddr_in serverAddress;
    Canbus *can;


};


#endif //CANBUSPI_TCPSOCKET_H
