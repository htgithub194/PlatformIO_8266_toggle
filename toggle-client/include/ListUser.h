#ifndef LIST_USER_H
#define LIST_USER_H

#include "User.h"
#include "Common.h"

class ListUser
{
  User listUser[MAX_USER];

public:
  void addUser(IPAddress add, int port);
  void notifyAll(String &message);
};

#endif