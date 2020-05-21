#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "AppContext.h"
#include "Device.h"
#include "Common.h"

const char *ssid =      "htwifi";
const char *password =  "88888888";

int32_t timeOfLastScan = -UPDATE_PERIOD;

void setup()
{
  Serial.begin(9600);
  Serial.println();

  // APP CONTEXT
  AppContext* pAppContext = AppContext::getInstance();
  pAppContext->setChipId(ESP.getChipId());
  // DISCONECT WIFI
  WiFi.disconnect();

  // SETUP DEVICE
  pAppContext->setupDevice();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("reconnect...");
  }
  Serial.println("Connected");

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  pAppContext->initUdp();
  delay(3000);
}

void loop()
{
  AppContext* pAppContext = AppContext::getInstance();
  pAppContext->setDelayTime(100);
  WiFiUDP* pUdp = pAppContext->getUdp();

  // update HARDWARE status
  pAppContext->checkHardWareChanged();

  pAppContext->checkUdpCommand();

  // update SOFTWARE status
  if (WiFi.status() != WL_CONNECTED)
  {
    pUdp->flush();
    delay(500);
    return;
  }

  if (millis() - timeOfLastScan > UPDATE_PERIOD)
  {
    timeOfLastScan = millis();
    pAppContext->setAllNeedUpdate();
  }

  pAppContext->sendUpdCommand();

  delay(pAppContext->getDelayTime());
}
