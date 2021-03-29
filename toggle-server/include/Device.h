#ifndef DEVICE_H
#define DEVICE_H

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

class stDevice
{
public:
  char dev_pinIn;
  char dev_pinOut;
  char currentPinIn;
  char dev_Name[16];
  int32_t timePinInChanged;

public:
  stDevice(char devName, char _pinIn, char _pinOut);

  void checkHardWareChanged();

  void checkUdpCommand(const char *cmd);

  char isTurnON();
  char readPinIN();

  void turnON();
  void turnOFF();

  String generateUpdCommand();
};

#endif