#ifndef RESET_HELPER
#define RESET_HELPER

#include "Common.h"

class ResetHelper
{
    char reset_pinIn;

public:
    ResetHelper(char _pinIn = 0);
    void checkResetButton();
};

#endif