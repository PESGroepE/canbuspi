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

/**
 * @brief TCPSocket klasse die gebruikt wordt om berichten uit te wisselen met de andere pi.
 */
class TCPSocket {
public:
    /**
    * Construeer een nieuw TCPSocket object.
    * @brief Constructor.
    * @param host IP waarmee verbonden moet worden.
    * @param port Poort waarop verbonden moet worden.
    * @param canbus Pointer naar Canbus interface.
    */
    TCPSocket(std::string, int, Canbus*);

    /**
    * @brief Initialiseer de socket door de verbinding te starten.
    */
    int init();

    /**
    * @brief Behandel nieuwe berichten die op de socket binnenkomen.
    */
    void handle(std::string);

    /**
    * @brief Stuur een bericht over de socket.
    * @param msg String met bericht wat de socket over moet.
    */
    int sendMessage(std::string);

private:
    /**
    * IP waarmee verbonden moet worden.
    */
    std::string host;

    /**
    * Poort waar op geluisterd moet worden.
    */
    int port;

    /**
    * Lokaal adres van de socket.
    */
    int clientSocket;

    /**
    * Adres waarmee de socket moet verbinden.
    */
    sockaddr_in serverAddress;

    /**
    * Pointer naar Canbus interface.
    */
    Canbus *can;


};


#endif //CANBUSPI_TCPSOCKET_H
