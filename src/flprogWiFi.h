#pragma once
#include "flprogUtilites.h"

#ifdef ARDUINO_ARCH_ESP8266
#define FLPROG_WIFI_TCP_DEVICE
#include <ESP8266WiFi.h>
#endif

#ifdef ARDUINO_ARCH_ESP32
#define FLPROG_WIFI_TCP_DEVICE
#include "WiFi.h"
#endif

#ifdef ARDUINO_ARCH_RP2040
// #ifdef ARDUINO_RASPBERRY_PI_PICO_W
// #define FLPROG_WIFI_TCP_DEVICE
// #include "WiFi.h"
// #endif
#endif

class FLProgAbstracttWiFiInterface
{
public:
    void setApSsid(char *_apSsid) { apSsid = _apSsid; };
    void setApPassword(char *_apPassword) { apPassword = _apPassword; };
    void setClientSsidd(char *_clientSsid) { clientSsid = _clientSsid; };
    void setClientPassword(char *_clientPassword) { clientPassword = _clientPassword; };

protected:
    char *apSsid = 0;
    char *apPassword = 0;
    char *clientSsid = 0;
    char *clientPassword = 0;
};

#ifdef ARDUINO_ARCH_ESP8266
#include "variant\esp\esp8266\flprogEsp8266Wifi.h"
#endif