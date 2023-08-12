#pragma once
#include "flprogWiFi.h"
#ifdef ARDUINO_ARCH_RP2040
#ifdef ARDUINO_RASPBERRY_PI_PICO_W

class FLProgOnBoardWifi : public FLProgAbstracttWiFiInterface
{
public:
    virtual void pool();
    virtual void apOn();
    virtual void clientOn();
   

protected:
    WiFiMode_t mode = WIFI_AP_STA;
    virtual void reconnect();
    virtual void clientReconnect();
    uint32_t reconnectPeriod = 20000;
    uint32_t lastReconnectTime = flprog::timeBack(reconnectPeriod);
};

#endif
#endif