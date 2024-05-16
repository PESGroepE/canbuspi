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
    }

    //uint8_t data[8] = {1};

    /*
    while (1) {
        uint8_t data[8] = {0, 1};
        uint8_t *p = data;
        can.sendMessage(12, 2, p);
        //can.sendMessage(2, 2, p);
        sleep(1);
        uint8_t data2[8] = {0, 0};
        uint8_t *p2 = data2;
        can.sendMessage(12, 2, p2);
        sleep(1);
        uint8_t data3[8] = {1, 0};
        uint8_t *p3 = data3;
        can.sendMessage(12, 2, p3);
        sleep(1);
        uint8_t data4[8] = {0, 0};
        uint8_t *p4 = data4;
        can.sendMessage(12, 2, p4);
        sleep(1);
    }
     */

    return 0;
}
