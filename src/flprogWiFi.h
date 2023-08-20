#pragma once
#include "Arduino.h"
#include "flprogUtilites.h"
#include "IPAddress.h"

#ifdef ARDUINO_ARCH_ESP8266
#define FLPROG_WIFI_TCP_DEVICE
#include "ESP8266WiFi.h"
#include "WiFiUdp.h"
extern "C"
{
#include "user_interface.h"
}
#endif

#ifdef ARDUINO_ARCH_ESP32
#define FLPROG_WIFI_TCP_DEVICE
#include "WiFi.h"
#include <esp_wifi.h>
#endif

#ifdef ARDUINO_ARCH_RP2040
#ifdef ARDUINO_RASPBERRY_PI_PICO_W
#define FLPROG_WIFI_TCP_DEVICE
#include "WiFi.h"
#endif
#endif

#include "flprogWifiClient.h"
#include "flprogWifiServer.h"

class FLProgAbstracttWiFiInterface : public FLProgAbstractTcpInterface
{
public:
    void setApSsid(String ssid);
    void setApPassword(String password);
    void setClientSsidd(String ssid);
    void setClientPassword(String password);
    void apMac(uint8_t m0, uint8_t m1, uint8_t m2, uint8_t m3, uint8_t m4, uint8_t m5);
    uint8_t *apMac() { return apMacaddress; }
    void apLocalIP(IPAddress ip);
    void apLocalIP(uint8_t ip0, uint8_t ip1, uint8_t ip2, uint8_t ip3) { apLocalIP(IPAddress(ip0, ip1, ip2, ip3)); };
    IPAddress apLocalIP() { return apIp; };
    void apDns(IPAddress ip);
    void apDns(uint8_t ip0, uint8_t ip1, uint8_t ip2, uint8_t ip3) { apDns(IPAddress(ip0, ip1, ip2, ip3)); };
    IPAddress apDns() { return apDnsIp; };
    void apSubnet(IPAddress ip);
    void apSubnet(uint8_t ip0, uint8_t ip1, uint8_t ip2, uint8_t ip3) { apSubnet(IPAddress(ip0, ip1, ip2, ip3)); };
    IPAddress apSubnet() { return apSubnetIp; };
    void apGateway(IPAddress ip);
    void apGateway(uint8_t ip0, uint8_t ip1, uint8_t ip2, uint8_t ip3) { apGateway(IPAddress(ip0, ip1, ip2, ip3)); };
    IPAddress apGateway() { return apGatewayIp; };

    virtual void clientOn();
    void clientOff();
    void clientMode(bool val);
    bool clientMode() { return clientWorkStatus; };
    virtual void apOn();
    void apOff();
    void apMode(bool val);
    bool apMode() { return apWorkStatus; };
    bool canStartServer() { return isCanStartServer; };
    virtual bool isImitation() { return false; }
    virtual bool isReady() { return clientStatus; };
    virtual uint8_t type() { return FLPROG_WIFI_INTERFACE; }
    virtual FLProgWiFiServer *getServer(int port) { return new FLProgWiFiServer(this, port); };
    virtual Client *getClient() { return new FLProgWiFiClient(); };

protected:
    uint8_t apMacaddress[6] = {0, 0, 0, 0, 0, 0};
    char apSsid[40] = "";
    char apPassword[40] = "";
    char clientSsid[40] = "";
    char clientPassword[40] = "";

    IPAddress apIp = IPAddress(0, 0, 0, 0);
    IPAddress apDnsIp = IPAddress(0, 0, 0, 0);
    IPAddress apSubnetIp = IPAddress(255, 255, 255, 0);
    IPAddress apGatewayIp = IPAddress(0, 0, 0, 0);

    bool apIsNeedReconect = false;
    bool apWorkStatus = false;
    bool clientWorkStatus = false;
    bool clientStatus = false;
    bool needUpdateClientData = false;
    bool isCanStartServer = false;
};

#ifndef FLPROG_WIFI_TCP_DEVICE
class FLProgOnBoardWifi : public FLProgAbstracttWiFiInterface
{
public:
    virtual void pool(){};
    virtual bool isImitation() { return true; }
    virtual bool isReady() { return false; };
};
#endif

#include "flprofWifiUdp.h"

#ifdef ARDUINO_ARCH_ESP8266
#include "variant/esp/esp8266/flprogEsp8266Wifi.h"
#endif

#ifdef ARDUINO_ARCH_ESP32
#include "variant/esp/esp32/flprogEsp32Wifi.h"
#endif

#ifdef ARDUINO_ARCH_RP2040
#ifdef ARDUINO_RASPBERRY_PI_PICO_W
#include "variant/rp2040/flprogRP2040Wifi.h"
#endif
#endif
