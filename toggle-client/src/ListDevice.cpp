#include "ListDevice.h"
#include "AppContext.h"

void ListDevice::updateDevice(char *name, char stt, IPAddress _ip)
{
    int32_t now = millis();

    for (int i = 0; i < MAX_DEVICE; i++)
    {
        if (listDevice[i].name == name)
        {
            listDevice[i].ip = _ip;
            listDevice[i].status = stt;
            listDevice[i].lastScan = now;

            if (listDevice[i].updateNow)
            {
                listDevice[i].updateNow = false;
                String msg = "ACK#";
                msg += listDevice[i].name;
                msg += ' ';
                msg += listDevice[i].status;
                AppContext::getInstance()->pListUser->notifyAll(msg);
            }

            Serial.println("Update DEVICE");
            return;
        }
    }

    for (int i = 0; i < MAX_DEVICE; i++)
    {
        if (now - listDevice[i].lastScan > 60000)
        {
            listDevice[i].ip = _ip;
            listDevice[i].name = name;
            listDevice[i].status = stt;
            listDevice[i].lastScan = now;
            listDevice[i].updateNow = false;
            Serial.println("ADD DEVICE");
            return;
        }
    }
}

void ListDevice::setDeviceStatus(const char *name, char stt)
{
    for (int i = 0; i < MAX_DEVICE; i++)
    {
        if (listDevice[i].name == name)
        {
            listDevice[i].updateNow = true;
            String msg = listDevice[i].name;
            msg += ' ';
            msg += stt == STT_ON ? STT_ON : STT_OFF;
            // Udp.beginPacket(listDevice[i].ip, DEVICE_UDP_PORT);
            // Udp.write(msg.c_str());
            // Udp.endPacket();
            AppContext::getInstance()->mCommandHelper.sendUdpOne(listDevice[i].ip, DEVICE_UDP_PORT, msg);
            return;
        }
    }
}

String ListDevice::generateGetMessage()
{
    String ret = "ACK#";
    int32_t now = millis();

    for (int i = 0; i < MAX_DEVICE; i++)
    {
        if (now - listDevice[i].lastScan < 60000)
        {
            ret += listDevice[i].name;
            ret += ' ';
            ret += listDevice[i].status;
            ret += '#';
        }
    }

    return ret;
}