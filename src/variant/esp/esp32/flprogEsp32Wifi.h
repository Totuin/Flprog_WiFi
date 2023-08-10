#pragma once
#include "flprogWiFi.h"
#ifdef ARDUINO_ARCH_ESP32


class FLProgOnBoardWifi : public FLProgAbstracttWiFiInterface
{
public:
    virtual void pool();

protected:
    wifi_mode_t mode = WIFI_AP_STA;
    uint32_t lastReconnectTime = flprog::timeBack(5000);
    virtual void reconnect();
    virtual void clientReconnect();
    virtual void apReconnect();
};
#endif