#include <iostream>

#include "Canbus.h"

int main() {
    std::cout << "CANbus Pi application" << std::endl;

    char interface[] = "can0";
    char *ip = interface;
    Canbus can(ip);

    if (can.init() < 0) {
        std::cout << "Failed to initialize canbus" << std::endl;
        return -1;
    }

    std::cout << "Can bus has been initialized" << std::endl;

    //TODO make tcp socket

    std::cout << "TCP socket has been initialized" << std::endl;



    std::cout << "Starting listeners" << std::endl;


    return 0;
}
