#ifndef COMMAND_HELPER_H
#define COMMAND_HELPER_H

#include "Common.h"

class CommandHelper
{
    char incomingPacket[255];
    char cmd_TYPE[8];
    char cmd_DEV[16];
    char cmd_STT[8];

public:
    WiFiUDP Udp;

public:

    void init();
    
    CommandHelper();

    void parseUdpPacket();

    void sendUdpOne(IPAddress& ip, int port, String &msg);
};

#endif