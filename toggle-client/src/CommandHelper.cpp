#include "CommandHelper.h"
#include "AppContext.h"

CommandHelper::CommandHelper()
{
}

void CommandHelper::parseUdpPacket()
{
    AppContext  *pAppContext    = AppContext::getInstance();
    ListDevice  *pListDevice    = pAppContext->pListDevice;
    ListUser    *pListUser      = pAppContext->pListUser;

    int packetSize = Udp.parsePacket();

    if (!packetSize)
    {
        return;
    }

    // receive incoming UDP packets
    ESP.getFreeHeap();

    int len = Udp.read(incomingPacket, sizeof(incomingPacket));
    if (len <= 0)
    {
        return;
    }

    incomingPacket[len] = 0;

    Serial.printf("UDP packet contents: %s\n", incomingPacket);

    memset(cmd_TYPE,    0, sizeof(cmd_TYPE));
    memset(cmd_DEV,     0, sizeof(cmd_DEV));
    memset(cmd_STT,     0, sizeof(cmd_STT));

    sscanf(incomingPacket, "%s %s %s", cmd_TYPE, cmd_DEV, cmd_STT);

    char strPort[16];
    memset(strPort, 0, sizeof(strPort));
    int port = 0;
    sscanf(incomingPacket, "%s %s", cmd_TYPE, strPort);
    port = atoi(strPort);

    // UPDATE ON/OFF
    if (strcmp(cmd_TYPE, CMD_UPDATE) == 0)
    {
        pListDevice->updateDevice(cmd_DEV, cmd_STT[0], Udp.remoteIP());
    }

    // TOGGLE
    if (strcmp(cmd_TYPE, CMD_TOGGLE) == 0)
    {
        pListDevice->setDeviceStatus(cmd_DEV, cmd_STT[0]);
    }

    // GET ON/OFF STATUS
    if (strcmp(cmd_TYPE, CMD_GET) == 0)
    {
        if (port <= 0)
            return;

        pListUser->addUser(Udp.remoteIP(), port);

        // send to 1 USER
        String msg = pListDevice->generateGetMessage();
        Udp.beginPacket(Udp.remoteIP(), port);
        Udp.write(msg.c_str());
        Udp.endPacket();
        delay(50);
    }

    if (strcmp(cmd_TYPE, "wif") == 0)
    {
        if (port <= 0)
            return;

        Udp.beginPacket(Udp.remoteIP(), port);
        Udp.write(AppContext::getInstance()->msgScanWifi.c_str());
        Udp.endPacket();
    }

    if (strcmp(cmd_TYPE, "stw") == 0)
    {
        char ssid[EEPROM_SIZE];
        char pw[EEPROM_SIZE];
        // char strPort[16];

        sscanf(incomingPacket, "%s %*s %s %s", cmd_TYPE, ssid, pw);
        Serial.println("STW: ");
        Serial.println(ssid);
        Serial.println(pw);

        ssid[sizeof(ssid) - 1] = 0;
        pw[sizeof(pw) - 1] = 0;

        String subSSID = String(ssid);
        subSSID.replace("&HT_SPACE&", " ");

        String subPw = String(pw);
        subPw.replace("&HT_SPACE&", " ");

        Serial.println(subSSID);
        Serial.println(subPw);

        pAppContext->wifiHelper.storeWifi(subSSID.c_str(), subSSID.length(), subPw.c_str(), subPw.length());
    }
}

void CommandHelper::sendUdpOne(IPAddress& ip, int port, String &msg)
{
    Serial.println("sendUdpOne: ");
    Serial.println(ip.toString());
    Serial.println(port);
    Serial.println(msg);
    Serial.println("");
    Udp.beginPacket(ip, port);
    Udp.write(msg.c_str());
    Udp.endPacket();
}

void CommandHelper::init()
{
    Serial.printf("UDP server on port %d\n", DEVICE_UDP_PORT);
    Udp.begin(DEVICE_UDP_PORT);
    delay(1000);
}