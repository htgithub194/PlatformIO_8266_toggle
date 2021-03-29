#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "AppContext.h"
#include "Device.h"
#include "Common.h"

void setup()
{
  //Serial.begin(9600);
  //Serial.println();

  // APP CONTEXT
  AppContext* pAppContext = AppContext::getInstance();
  pAppContext->setChipId(ESP.getChipId());
  // DISCONECT WIFI
  WiFi.disconnect();

  // SETUP DEVICE
  pAppContext->setupDevice();

  pAppContext->connectWifi();

  pAppContext->initUdp();
  delay(3000); 
}

void loop()
{
  AppContext* pAppContext = AppContext::getInstance();
  pAppContext->setDelayTime(200);
  // WiFiUDP* pUdp = pAppContext->getUdp();

  // update HARDWARE status
  pAppContext->checkHardWareChanged();

  pAppContext->checkUdpCommand();

  // update SOFTWARE status
  if (WiFi.status() != WL_CONNECTED)
  {
    pAppContext->connectWifi();
    // pUdp->flush();
    // delay(500);
    // return;
  }

  delay(pAppContext->getDelayTime());
}
