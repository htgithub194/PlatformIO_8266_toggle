#include "WifiHelper.h"
#include "AppContext.h"

WifiHelper::WifiHelper()
{
    isWifiConnecting = false;
    timeOfLastConnect = millis();
}

void WifiHelper::storeWifi(const char *ssid, int ssid_length, const char *pw, int pw_length)
{
    memset(EEPROM_wifiName, 0, sizeof(EEPROM_wifiName));
    memset(EEPROM_wifiPw, 0, sizeof(EEPROM_wifiPw));

    memcpy(EEPROM_wifiName, ssid, ssid_length);
    memcpy(EEPROM_wifiPw, pw, pw_length);

    // EEPROM
    EEPROM.begin(EEPROM_SIZE_SECTOR);
    EEPROM.put(EEPROM_ADDRESS_WIFI_NAME, EEPROM_wifiName);
    delay(10);
    EEPROM.commit();
    EEPROM.put(EEPROM_ADDRESS_WIFI_PW, EEPROM_wifiPw);
    delay(10);
    EEPROM.commit();
    EEPROM.end();

    delay(100);
    connectWifi();
}

void WifiHelper::connectWifi()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        isWifiConnecting = false;
        return;
    }

    if (isWifiConnecting && millis() - timeOfLastConnect < CONNECT_WIFI_TIME)
    {
        return;
    }

    memset(EEPROM_wifiName, 0, sizeof(EEPROM_wifiName));
    memset(EEPROM_wifiPw, 0, sizeof(EEPROM_wifiPw));

    EEPROM.begin(EEPROM_SIZE_SECTOR);
    EEPROM.get(EEPROM_ADDRESS_WIFI_NAME, EEPROM_wifiName);
    delay(10);
    EEPROM.get(EEPROM_ADDRESS_WIFI_PW, EEPROM_wifiPw);
    EEPROM.end();

    Serial.println("connectWifi: ");
    Serial.println(EEPROM_wifiName);
    Serial.println(EEPROM_wifiPw);
    Serial.println("");

    WiFi.begin(EEPROM_wifiName, EEPROM_wifiPw);
    timeOfLastConnect = millis();
    isWifiConnecting = true;
}

void WifiHelper::disconnectWifi()
{
    WiFi.softAPdisconnect();
    WiFi.disconnect();
    delay(3000);
}

void WifiHelper::configAPMode()
{
    Serial.println("configAP_STAMode");
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(HUB_IP_ADDR, HUB_IP_ADDR, SUB_NET_MASK);
    delay(1000);
    WiFi.softAP(WIFI_SETTING_NAME, WIFI_SETTING_PW);
    Serial.print("AP IP: ");
    Serial.println(WiFi.softAPIP());
}

void WifiHelper::configAP_STAMode()
{
    Serial.println("configAP_STAMode");
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAPConfig(HUB_IP_ADDR, HUB_IP_ADDR, SUB_NET_MASK);
    WiFi.softAP(WIFI_NAME, WIFI_PW);
    Serial.print("softAPIP: ");
    Serial.println(WiFi.softAPIP());
}

void WifiHelper::scanWifi(String &msgScanWifi)
{
    Serial.println("scan start");
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0)
    {
        Serial.println("no networks found");
    }
    else
    {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i)
        {
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
            msgScanWifi += WiFi.SSID(i);
            msgScanWifi += "&HT_SPACE&";
            msgScanWifi += WiFi.RSSI(i);
            msgScanWifi += "&HT_SPACE&";
            delay(10);
        }
    }
}