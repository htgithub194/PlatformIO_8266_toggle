#ifndef LIST_DEVICE_H
#define LIST_DEVICE_H

#include "Common.h"
#include "Device.h"

class ListDevice
{
public:
  Device listDevice[MAX_DEVICE];

  void updateDevice(char *name, char stt, IPAddress _ip);

  void setDeviceStatus(const char *name, char stt);

  String generateGetMessage();
};

#endif 