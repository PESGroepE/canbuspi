#include "Canbus.h"

#include <iostream>
#include <cstdio>
#include <cstring>
#include <unistd.h>

#include "Event.h"

Canbus::Canbus(char *i):interface(i) {

}

Canbus::~Canbus() {
    if (close(s) < 0) {
        std::cout<<"Failed to close canbus socket"<<std::endl;
    }
}

int Canbus::init() {
    s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (s<0) return s;

    strcpy(ifr.ifr_name, interface);
    ioctl(s, SIOCGIFINDEX, &ifr);

    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        return -1;
    }

    std::cout<<"Started canbus socket"<<std::endl;
    return 0;
}

int Canbus::sendMessage(__u32 id, __u8 size, __u8 data[8]) {
    struct can_frame frame;
    frame.can_id = id;
    frame.can_dlc = size;
    memcpy(frame.data, data, 8);

    if (write(s, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
        return 1;
    }

    return 0;
}

int Canbus::receive(Event *e) {
    int nbytes;
    struct can_frame frame;

    nbytes = read(s, &frame, sizeof(struct can_frame));

    if (nbytes < 0) {
        std::cout << "Failed to read from canbus socket" << std::endl;
        return -1;
    }

    switch (frame.can_id) {
        case 2: //brandalarm
            int brand;
            brand = frame.data[0];
            std::cout << "brandalarm: " << brand << std::endl;
            e->setData(std::to_string(brand));
            e->setType(BRAND);
            break;
        case 5: //temp
            float temp;
            memcpy(&temp, frame.data, 4);
            std::cout << "temperatuur: " << temp << std::endl;
            break;
        case 6: //humidity
            float humidity;
            memcpy(&humidity, frame.data, 4);
            std::cout << "luchtvochtigheid: " << humidity << std::endl;
            e->setData(std::to_string(humidity));
            e->setType(HUMIDITY);
            return 1;
        case 10: //noodknop-sluis
            std::cout << "sluis noodknop ingedrukt" << std::endl;
            e->setType(NOODKNOP);
            e->setData(std::to_string(frame.data[0]));
            break;
        case 11: //binnen-sluis
            std::cout << "sluis knop ingedrukt" << std::endl;
            e->setType(SLUISKNOP);
            e->setData(std::to_string(frame.data[0]));
            break;
        default:
            printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);

            for (int i = 0; i < frame.can_dlc; i++)
                printf("%02X ", frame.data[i]);

            printf("\n");
    }

    return 0;
}