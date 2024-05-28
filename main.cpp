/**
@file main.cpp
*/

#include <iostream>

#include "Canbus.h"
#include "TCPSocket.h"
#include <thread>

/**
 * @brief main functie van het programma.
 * Functie die de canbus-verbinding en socket initialiseert en events afvangt.
 */
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

        switch (event->getType()) {
            case HUMIDITY:
                socket.sendMessage("humidity:" + event->getData());
                break;
            case BRAND:
                socket.sendMessage("brand:" + event->getData());
                break;
            case SLUISKNOP:
                socket.sendMessage("sluisknop:" + event->getData());
                break;
            case NOODKNOP:
                socket.sendMessage("noodknop:" + event->getData());
                break;
            case TEMP:
                socket.sendMessage("temp:" + event->getData());
                break;
        }
    }

    return 0;
}
