#include "Device.h"
#include "AppContext.h"
#include "Common.h"

stDevice::stDevice(char devName, char _pinIn, char _pinOut)
{
    dev_pinIn = _pinIn;
    dev_pinOut = _pinOut;
    currentPinIn = digitalRead(dev_pinIn);
    timePinInChanged = millis();
    needUpdateNow = true;

    memset(dev_Name, 0, sizeof(dev_Name));
    int32_t chipId = AppContext::getInstance()->getChipId();
    sprintf(dev_Name, "%d_%c", chipId, devName);

    pinMode(dev_pinOut, OUTPUT);
    pinMode(dev_pinIn, INPUT_PULLUP);
    digitalWrite(dev_pinOut, HIGH);
}

void stDevice::checkHardWareChanged()
{
    int32_t now = millis();
    char currentBtn = digitalRead(dev_pinIn);
    if (currentBtn == currentPinIn)
    {
        timePinInChanged = now;
    }
    else if (now - timePinInChanged > 200)
    {
        currentPinIn = currentBtn;
        char currentPinOut = digitalRead(dev_pinOut);
        currentPinOut = (currentPinOut == LOW) ? HIGH : LOW;
        digitalWrite(dev_pinOut, currentPinOut);
        needUpdateNow = true;
    }
}

void stDevice::checkUdpCommand(const char *cmd)
{
    char parseCmd_Dev_Name[16];
    char parseCmd_OnOff[8];

    memset(parseCmd_Dev_Name,   0, sizeof(parseCmd_Dev_Name));
    memset(parseCmd_OnOff,      0, sizeof(parseCmd_OnOff));

    sscanf(cmd, "%s %s", parseCmd_Dev_Name, parseCmd_OnOff);

    if (strcmp(parseCmd_Dev_Name, dev_Name))
    {
        return;
    }

    digitalWrite(dev_pinOut, parseCmd_OnOff[0] == '1' ? LOW : HIGH);
    needUpdateNow = true;
}

String stDevice::generateUpdCommand()
{
    String ret;

    ret += "upd ";
    ret += dev_Name;
    ret += ' ';
    ret += digitalRead(dev_pinOut) ? '0' : '1';

    return ret;
}

bool stDevice::sendUpdCommand()
{
    if (needUpdateNow)
    {
        needUpdateNow = false;

        AppContext *pAppContext = AppContext::getInstance();
        WiFiUDP *pUdp = pAppContext->getUdp();

        String Message = generateUpdCommand();
        pUdp->beginPacket(UDP_IP, UDP_PORT);
        pUdp->write(Message.c_str());
        pUdp->endPacket();

        pAppContext->setDelayTime(50);
        return true;
    }
    return false;
}