#include "Common.h"
#include "AppContext.h"
#include "WifiHelper.h"

void setup()
{
  Serial.begin(9600);
  Serial.println();

  AppContext *pAppContext = AppContext::getInstance();
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

  // EEPROM_ADDRESS_VERSION
  unsigned char checkVersion;
  EEPROM.begin(1);
  EEPROM.get(EEPROM_ADDRESS_VERSION, checkVersion);
  EEPROM.end();

  if (checkVersion != 194)
  {
    EEPROM.begin(1);
    EEPROM.put(EEPROM_ADDRESS_VERSION, 194);    
    EEPROM.commit();
    EEPROM.end();

    delay(10);

    EEPROM.begin(EEPROM_SIZE_SECTOR);
    EEPROM.put(EEPROM_ADDRESS_WIFI_NAME, "TP-LINK_5424");
    EEPROM.commit();
    delay(10);
    EEPROM.put(EEPROM_ADDRESS_WIFI_PW, "02791739");
    EEPROM.commit();
    delay(10);
    EEPROM.end();
  }

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