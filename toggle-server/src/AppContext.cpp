#include "AppContext.h"

AppContext *AppContext::pInstance = NULL;

AppContext *AppContext::getInstance()
{
    if (pInstance == NULL)
    {
        pInstance = new AppContext();
    }
    return pInstance;
}

void AppContext::setChipId(int32_t chipId)
{
    mChipId = chipId;
}

int32_t AppContext::getChipId()
{
    return mChipId;
}

WiFiUDP *AppContext::getUdp()
{
    return &mUdp;
}

void AppContext::initUdp()
{
    mUdp.begin(UDP_PORT);
}

unsigned int AppContext::getDelayTime()
{
    return mDelayTime;
}

void AppContext::setDelayTime(unsigned int value)
{
    mDelayTime = value;
}

void AppContext::setupDevice()
{
    mDeviceList[0] = new stDevice(DEV_1_NAME, DEV_1_PIN_IN, DEV_1_PIN_OUT);
    mDeviceList[1] = new stDevice(DEV_2_NAME, DEV_2_PIN_IN, DEV_2_PIN_OUT);
    mDeviceList[2] = new stDevice(DEV_3_NAME, DEV_3_PIN_IN, DEV_3_PIN_OUT);
    mDeviceList[3] = new stDevice(DEV_4_NAME, DEV_4_PIN_IN, DEV_4_PIN_OUT);
}

void AppContext::checkHardWareChanged()
{
    for (char i = 0; i < MAX_DEVICE; i++)
    {
        mDeviceList[i]->checkHardWareChanged();
    }
}

void AppContext::checkUdpCommand()
{
    // Handle command
    int packetSize = mUdp.parsePacket();
    if (packetSize <= 0)
        return;
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, mUdp.remoteIP().toString().c_str(), mUdp.remotePort());
    int len = mUdp.read(incomingPacket, sizeof(incomingPacket));
    if (len <= 0)
        return;

    incomingPacket[len] = 0;

    Serial.printf("UDP packet contents: %s\n", incomingPacket);

    for (char i = 0; i < MAX_DEVICE; i++)
    {
        mDeviceList[i]->checkUdpCommand(incomingPacket);
    }
}

void AppContext::sendUpdCommand()
{
    for (char i = 0; i < MAX_DEVICE; i++)
    {
        if (mDeviceList[i]->sendUpdCommand())
            break;
    }
}

void AppContext::setAllNeedUpdate()
{
    for (char i = 0; i < MAX_DEVICE; i++)
    {
        mDeviceList[i]->needUpdateNow = true;
    }
}