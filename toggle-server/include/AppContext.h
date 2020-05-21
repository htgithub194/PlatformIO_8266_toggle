#ifndef APP_CONTEXT_H
#define APP_CONTEXT_H

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "Common.h"
#include "Device.h"

class AppContext
{
    char incomingPacket[255];
    static AppContext* pInstance;

public:
    int32_t mChipId;
    WiFiUDP mUdp;

    unsigned int mDelayTime;

    stDevice* mDeviceList[MAX_DEVICE];

public:
    static AppContext* getInstance();

    int32_t getChipId();
    void setChipId(int32_t);

    WiFiUDP* getUdp();
    void initUdp();

    unsigned int getDelayTime();
    void setDelayTime(unsigned int);

    void setupDevice();

    void checkHardWareChanged();
    void checkUdpCommand();
    void sendUpdCommand();
    void setAllNeedUpdate();
};

#endif
