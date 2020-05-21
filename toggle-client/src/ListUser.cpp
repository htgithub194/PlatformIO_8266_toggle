#include "ListUser.h"
#include "AppContext.h"

void ListUser::addUser(IPAddress add, int port)
{
    int32_t now = millis();

    for (int i = 0; i < MAX_USER; i++)
    {
        if (listUser[i].ip == add)
        {
            listUser[i].port = port;
            listUser[i].lastScan = now;
            Serial.println("Update USER");
            return;
        }
    }

    for (int i = 0; i < MAX_USER; i++)
    {
        Serial.println(now);
        Serial.println(listUser[i].lastScan);
        if (now - listUser[i].lastScan > 60000)
        {
            listUser[i].ip = add;
            listUser[i].port = port;
            listUser[i].lastScan = now;
            Serial.println("ADD USER");
            return;
        }
    }
}

void ListUser::notifyAll(String &message)
{
    int32_t now = millis();

    for (int i = 0; i < MAX_USER; i++)
    {
        if (now - listUser[i].lastScan < 60000)
        {
            AppContext::getInstance()->mCommandHelper.sendUdpOne(listUser[i].ip, listUser[i].port, message);
            delay(10);
        }
    }
}