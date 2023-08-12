#pragma once
#include "flprogWiFi.h"
#ifdef ARDUINO_ARCH_ESP8266

class FLProgOnBoardWifi : public FLProgAbstracttWiFiInterface
{
public:
    virtual void pool();

protected:
    WiFiMode mode = WIFI_AP_STA;
    virtual void reconnect();
    virtual void clientReconnect();
    virtual void apReconnect();
};
#endif