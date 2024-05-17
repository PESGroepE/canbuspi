#include <iostream>

#include "Canbus.h"
#include "TCPSocket.h"
#include <unistd.h>
#include <thread>

int main() {
    std::cout << "CANbus Pi application" << std::endl;

    char interface[] = "can0";
    Canbus can(interface);
    int canstatus = can.init();
    if (canstatus < 0) {
        std::cout << "Failed to initialize canbus: "<< canstatus << std::endl;
        return -1;
    }

    std::cout << "Can bus has been initialized" << std::endl;

    TCPSocket socket("10.0.10.1", 5000, &can);
    int socketstatus = socket.init();
    if (socketstatus < 0) {
        std::cout << "Failed to initialize socket: "<< socketstatus << std::endl;
        return -1;
    }

    std::cout << "TCP socket has been initialized" << std::endl;

    std::thread t1(&TCPSocket::handle, &socket, "params");
    std::cout << "Starting listeners" << std::endl;

    while(1) {
        Event *event = new Event();
        can.receive(event);

        if (event->getType() == HUMIDITY) {
            socket.sendMessage("humidity:" + event->getData());
        }
        if (event->getType() == BRAND) {
            socket.sendMessage("brand:" + event->getData());
        }
        if (event->getType() == NOODKNOP) {
            socket.sendMessage("noodknop:" + event->getData());
        }
        if (event->getType() == SLUISKNOP) {
            socket.sendMessage("sluisknop:" + event->getData());
        }

    }

    return 0;
}
