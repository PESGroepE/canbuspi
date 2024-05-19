#ifndef CANBUSPI_CANBUS_H
#define CANBUSPI_CANBUS_H

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include "Event.h"

/**
 * @brief Canbus klasse die gebruikt wordt voor communicatie met de STM32's.
 */
class Canbus {
public:
    /**
    * Construeer een nieuw Canbus object.
    * @brief Constructor.
    * @param interface Naam van de canbus interface.
    */
    Canbus(char*);

    /**
    * Deconstrueer dit Canbus object.
    * @brief Destructor.
    */
    ~Canbus();

    /**
    * @brief Initialiseer de canbus connectie.
    */
    int init();

    /**
    * @brief Stuur een bericht over de canbus verbinding.
    * @param id ID van het canbus-bericht.
    * @param lengte Aantal bytes die verstuurd worden.
    * @param data Array met bytes die de data vormen.
    */
    int sendMessage(__u32, __u8, __u8[8]);

    /**
    * @brief Ontvang een bericht over de canbus verbinding.
    * @param event Pointer naar het event object wat teruggestuurd moet worden.
    */
    int receive(Event *e);
private:
    /**
    * @brief Naam van de canbus interface.
    */
    char *interface;

    /**
    * @brief Adres van de socket.
    */
    int s;

    /**
    * @brief Naam van de socket.
    */
    struct sockaddr_can addr;

    /**
    * @brief Adres naar de socket.
    */
    struct ifreq ifr;
};


#endif //CANBUSPI_CANBUS_H
