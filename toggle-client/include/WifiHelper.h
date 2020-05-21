#ifndef WIFI_HELPER_H
#define WIFI_HELPER_H

#include "Common.h"

class WifiHelper
{
    // EEPROM
    char EEPROM_wifiName[EEPROM_SIZE];
    char EEPROM_wifiPw[EEPROM_SIZE];

    bool isWifiConnecting;
    int32_t timeOfLastConnect;

public:
    WifiHelper();

    void storeWifi(const char *ssid, int ssid_length, const char *pw, int pw_length);

    void connectWifi();

    void disconnectWifi();

    void configAPMode();

    void configAP_STAMode();

    void scanWifi(String &msgScanWifi);

};

#endif