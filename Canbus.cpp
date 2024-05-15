#include "Canbus.h"

#include <iostream>
#include <cstdio>
#include <cstring>
#include <unistd.h>

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

int Canbus::listen() {
    int s, i;
    int nbytes;
    struct can_frame frame;

    nbytes = read(s, &frame, sizeof(struct can_frame));

    if (nbytes < 0) {
        std::cout<<"Failed to read from canbus socket"<<std::endl;
        return -1;
    }

    printf("0x%03X [%d] ",frame.can_id, frame.can_dlc);

    for (i = 0; i < frame.can_dlc; i++)
        printf("%02X ",frame.data[i]);

    return 0;
}