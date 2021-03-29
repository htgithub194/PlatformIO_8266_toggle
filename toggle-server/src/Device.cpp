#include "Device.h"
#include "AppContext.h"
#include "Common.h"

ICACHE_RAM_ATTR void interruptFunction()
{
    // update HARDWARE status
    AppContext *pAppContext = AppContext::getInstance();
    pAppContext->checkHardWareChanged();
    //Serial.println("INTERRUPT");
}

stDevice::stDevice(char devName, char _pinIn, char _pinOut)
{
    dev_pinIn = _pinIn;
    dev_pinOut = _pinOut;
    timePinInChanged = millis();

    currentPinIn = readPinIN();

    memset(dev_Name, 0, sizeof(dev_Name));
    int32_t chipId = AppContext::getInstance()->getChipId();
    sprintf(dev_Name, "%d_%c", chipId, devName);

    pinMode(dev_pinOut, OUTPUT);
    pinMode(dev_pinIn, INPUT_PULLUP);

    turnOFF();

    AppContext::getInstance()->registerDevice(this);

    attachInterrupt(digitalPinToInterrupt(_pinIn), interruptFunction, CHANGE);
}

void stDevice::checkHardWareChanged()
{
    int32_t now = millis();

    if (currentPinIn == readPinIN())
    {
        timePinInChanged = now;
    }
    else if (now - timePinInChanged > 200)
    {
        currentPinIn = readPinIN();
        isTurnON() ? turnOFF() : turnON();
    }
}

void stDevice::checkUdpCommand(const char *cmd)
{
    char parseCmd_Dev_Name[16];
    char parseCmd_OnOff[8];

    memset(parseCmd_Dev_Name, 0, sizeof(parseCmd_Dev_Name));
    memset(parseCmd_OnOff, 0, sizeof(parseCmd_OnOff));

    sscanf(cmd, "%s %s", parseCmd_Dev_Name, parseCmd_OnOff);

    if (strcmp(parseCmd_Dev_Name, dev_Name))
    {
        return;
    }

    parseCmd_OnOff[0] == '1' ? turnON() : turnOFF();
}

String stDevice::generateUpdCommand()
{
    String ret;

    ret += "upd ";
    ret += dev_Name;
    ret += ' ';
    ret += isTurnON() ? '1' : '0';

    return ret;
}

void stDevice::turnON()
{
    digitalWrite(dev_pinOut, OUTPUT_ON);
    AppContext::getInstance()->updateStatusMessage();
}

void stDevice::turnOFF()
{
    digitalWrite(dev_pinOut, OUTPUT_OFF);
    AppContext::getInstance()->updateStatusMessage();
}

char stDevice::isTurnON()
{
    return digitalRead(dev_pinOut) == OUTPUT_ON ? 1 : 0;
}

char stDevice::readPinIN() {
    return digitalRead(dev_pinIn);
}