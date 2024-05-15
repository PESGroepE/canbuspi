#ifndef CANBUSPI_CANBUS_H
#define CANBUSPI_CANBUS_H

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

class Canbus {
public:
    Canbus(char*);
    ~Canbus();
    int init();
    int sendMessage(__u32, __u8, __u8[8]);
    int listen();
private:
    char *interface;
    int s;
    struct sockaddr_can addr;
    struct ifreq ifr;
};


#endif //CANBUSPI_CANBUS_H
