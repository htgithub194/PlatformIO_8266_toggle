#include "AppContext.h"

AppContext *AppContext::pInstance = NULL;

AppContext::AppContext()
  : mReset(RESET_PIN_IN)
{
}

AppContext *AppContext::getInstance()
{
  if (pInstance == NULL)
  {
    pInstance = new AppContext();
  }
  return pInstance;
}

void AppContext::init()
{
  // DATA MODEL
  pListUser = new ListUser();
  pListDevice = new ListDevice();
  if (NULL == pListUser || NULL == pListDevice)
  {
    ESP.reset();
  }
}

void AppContext::toResetMode()
{
  wifiHelper.disconnectWifi();
  msgScanWifi = MSG_SCAN;
  wifiHelper.scanWifi(msgScanWifi);
  wifiHelper.configAPMode();
}