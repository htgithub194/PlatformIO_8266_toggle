#ifndef COMMON_H
#define COMMON_H


// config board
#define ONE_RELAY

#ifdef ONE_RELAY 

#define DEV_1_NAME '1'
#define DEV_1_PIN_IN D1
#define DEV_1_PIN_OUT D2

#define ENABLE_DEV_1

#define OUTPUT_ON HIGH
#define OUTPUT_OFF LOW
#endif

// config board
#ifdef NORMALBOARD

#define DEV_1_NAME '1'
#define DEV_1_PIN_IN D1
#define DEV_1_PIN_OUT D3

#define DEV_2_NAME '2'
#define DEV_2_PIN_IN D2
#define DEV_2_PIN_OUT D4

#define DEV_3_NAME '3'
#define DEV_3_PIN_IN D5
#define DEV_3_PIN_OUT D0

#define DEV_4_NAME '4'
#define DEV_4_PIN_IN D6
#define DEV_4_PIN_OUT D7

#define ENABLE_DEV_1
#define ENABLE_DEV_2
#define ENABLE_DEV_3
#define ENABLE_DEV_4

#define OUTPUT_ON LOW
#define OUTPUT_OFF HIGH
#endif






// config common
#define MAX_DEVICE 4
#define UDP_PORT 8888

#define ssid "Thong"
#define password "88888888"

#endif