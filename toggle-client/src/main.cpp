#include "Common.h"
#include "AppContext.h"
#include "WifiHelper.h"

void setup()
{
  Serial.begin(9600);
  Serial.println();


  AppContext* pAppContext = AppContext::getInstance();
  pAppContext->init();

  pAppContext->wifiHelper.disconnectWifi();

  pAppContext->wifiHelper.configAP_STAMode();

  pAppContext->mCommandHelper.init();

  //  // EEPROM
  //  EEPROM.begin(EEPROM_SIZE_SECTOR);
  //  EEPROM.put(EEPROM_ADDRESS_WIFI_NAME, EEPROM_test);
  //  delay(10);
  //  EEPROM.commit();
  //  EEPROM.put(EEPROM_ADDRESS_WIFI_PW, EEPROM_test1);
  //  EEPROM.commit();
  //  delay(10);
  //  EEPROM.end();
}

void loop()
{
  AppContext *pAppContext = AppContext::getInstance();

  // check Reset
  pAppContext->mReset.checkResetButton();

  // check connect wifi
  pAppContext->wifiHelper.connectWifi();

  // check UDP command
  pAppContext->mCommandHelper.parseUdpPacket();

  // delay
  delay(200);
}