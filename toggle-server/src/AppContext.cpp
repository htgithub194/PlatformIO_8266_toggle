#include "AppContext.h"

AppContext *AppContext::pInstance = NULL;

AppContext::AppContext()
{
    mNumberOfDevices = 0;
    mNumberOfReconnect = 0;
}

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
#if defined(ENABLE_DEV_1)
    new stDevice(DEV_1_NAME, DEV_1_PIN_IN, DEV_1_PIN_OUT);
#endif

#if defined(ENABLE_DEV_2)
    new stDevice(DEV_2_NAME, DEV_2_PIN_IN, DEV_2_PIN_OUT);
#endif

#if defined(ENABLE_DEV_3)
    new stDevice(DEV_3_NAME, DEV_3_PIN_IN, DEV_3_PIN_OUT);
#endif

#if defined(ENABLE_DEV_4)
    new stDevice(DEV_4_NAME, DEV_4_PIN_IN, DEV_4_PIN_OUT);
#endif
}

void AppContext::checkHardWareChanged()
{
    for (char i = 0; i < mNumberOfDevices; i++)
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
    //Serial.printf("Received %d bytes from %s, port %d\n", packetSize, mUdp.remoteIP().toString().c_str(), mUdp.remotePort());

    int len = mUdp.read(incomingPacket, sizeof(incomingPacket));
    if (len <= 0)
        return;

    incomingPacket[len] = 0;

    //Serial.printf("UDP packet contents: %s\n", incomingPacket);

    if (!strcmp(incomingPacket, "get"))
    {
        mServerIP = mUdp.remoteIP();
        mServerPort = mUdp.remotePort();
        updateStatusMessage();
        return;
    }

    for (int i = 0; i < mNumberOfDevices; i++)
    {
        mDeviceList[i]->checkUdpCommand(incomingPacket);
    }
}

void AppContext::sendUDP(const char *msg)
{
    mUdp.beginPacket(mServerIP, mServerPort);
    mUdp.write(msg);
    mUdp.endPacket();
}

void AppContext::sendUDP()
{
    sendUDP(mStatusMessage.c_str());
}

void AppContext::updateStatusMessage()
{
    mStatusMessage.clear();

    for (char i = 0; i < mNumberOfDevices; i++)
    {
        mStatusMessage += mDeviceList[i]->generateUpdCommand();
        mStatusMessage += '\n';
    }

    sendUDP(mStatusMessage.c_str());
}

void AppContext::registerDevice(stDevice *pDevice)
{
    if (mNumberOfDevices < MAX_DEVICE)
    {
        mDeviceList[mNumberOfDevices++] = pDevice;
        updateStatusMessage();
    }
}

void AppContext::connectWifi()
{
    //Serial.printf("Connecting to %s ", ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        //Serial.println("reconnect...");
    }

    //Serial.println("");
    //Serial.println("WiFi connected");
    //Serial.print("IP address: ");
    //Serial.println(WiFi.localIP());
}