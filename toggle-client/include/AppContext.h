#ifndef APP_CONTEXT_H
#define APP_CONTEXT_H

#include "ListDevice.h"
#include "ListUser.h"
#include "WifiHelper.h"
#include "ResetHelper.h"
#include "CommandHelper.h"

class AppContext
{
    static AppContext *pInstance;

    AppContext();

public:
    // // FOR UDP
    CommandHelper mCommandHelper;

    // FOR RESET PIN
    ResetHelper mReset;

    // FOR WIFI CONNECTION
    int32_t timeOfLastScan;
    bool stopConnectWifi;
    bool isWifiConnecting;

    WifiHelper wifiHelper;
public:
    ListDevice  *pListDevice;
    ListUser    *pListUser;

    String      msgScanWifi;

public:
    static AppContext *getInstance();

    void init();

    void toResetMode();
};

#endif