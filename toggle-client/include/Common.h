#ifndef COMMON_H
#define COMMON_H

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <WiFiUdp.h>

#define MAX_USER            20
#define MAX_DEVICE          50

#define SUB_NET_MASK        IPAddress(255, 255, 255, 0)
#define HUB_IP_ADDR         IPAddress(192, 168, 94, 1)
#define DEVICE_UDP_PORT     8888

// RESET BUTTON
#define RESET_PIN_IN        D1
#define STT_ON              '1'
#define STT_OFF             '0'
#define RESET_BTN_TIME      3000

// WIFI SETTUP
#define WIFI_NAME           "htwifi"
#define WIFI_PW             "88888888"
#define CONNECT_WIFI_TIME   10000  

#define WIFI_SETTING_NAME   "thiet_lap_wifi"
#define WIFI_SETTING_PW     "00000000"
#define MSG_SCAN            "ACK#wfi#"

// EEPROM
#define EEPROM_SIZE                     128
#define EEPROM_SIZE_SECTOR              (EEPROM_SIZE * 2)
#define EEPROM_ADDRESS_WIFI_NAME        0
#define EEPROM_ADDRESS_WIFI_PW          (EEPROM_ADDRESS_WIFI_NAME + EEPROM_SIZE)
#define EEPROM_ADDRESS_VERSION          (EEPROM_ADDRESS_WIFI_PW + EEPROM_SIZE)

// UDP COMMAND
#define CMD_GET             "get"
#define CMD_TOGGLE          "tog"
#define CMD_UPDATE          "upd"

#endif