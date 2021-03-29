#ifndef APP_CONTEXT_H
#define APP_CONTEXT_H

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "Common.h"
#include "Device.h"

class AppContext
{
    char incomingPacket[255];
    static AppContext *pInstance;
    IPAddress mServerIP;
    uint16_t mServerPort;

    String mStatusMessage;

    unsigned char mNumberOfDevices;

    unsigned char mNumberOfReconnect;

private:
    AppContext();

public:
    int32_t mChipId;
    WiFiUDP mUdp;

    unsigned int mDelayTime;

    stDevice *mDeviceList[MAX_DEVICE];

public:
    static AppContext *getInstance();

    int32_t getChipId();
    void setChipId(int32_t);

    WiFiUDP *getUdp();
    void initUdp();

    unsigned int getDelayTime();
    void setDelayTime(unsigned int);

    void setupDevice();

    void checkHardWareChanged();
    void checkUdpCommand();

    void updateStatusMessage();

    void sendUDP(const char *);
    void sendUDP();

    void registerDevice(stDevice *);

    void connectWifi();
};

#endif
