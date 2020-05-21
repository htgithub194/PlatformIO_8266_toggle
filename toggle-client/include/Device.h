#ifndef DEVICE_H
#define DEVICE_H

#include "Common.h"

class Device
{
public:
  IPAddress ip;
  String name;
  int32_t lastScan;
  char status;
  char updateNow;

  Device()
  {
    lastScan = -60000;
    status = 0;
    updateNow = false;
  }
};
#endif //DEVICE_H