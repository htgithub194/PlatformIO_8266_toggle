#ifndef USER_H
#define USER_H

#include "Common.h"

class User
{
public:
  IPAddress ip;
  int port;
  int32_t lastScan;

  User()
  {
    port = 0;
    lastScan = -60000;
  }
};

#endif