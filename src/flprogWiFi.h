#pragma once
#include "Arduino.h"
#include "flprogUtilites.h"
#include "IPAddress.h"
#include "Server.h"

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

class FLProgAbstracttWiFiInterface
{
public:
    void setApSsid(String ssid);
    void setApPassword(String password);
    void setClientSsidd(String ssid);
    void setClientPassword(String password);
    void setApMac(uint8_t m0, uint8_t m1, uint8_t m2, uint8_t m3, uint8_t m4, uint8_t m5);
    void setClientMac(uint8_t m0, uint8_t m1, uint8_t m2, uint8_t m3, uint8_t m4, uint8_t m5);
    uint8_t *getApMac() { return apMac; }
    uint8_t *getClientMac() { return clientMac; }
    void setApIp(IPAddress ip);
    void setApIp(uint8_t ip0, uint8_t ip1, uint8_t ip2, uint8_t ip3) { setApIp(IPAddress(ip0, ip1, ip2, ip3)); };
    IPAddress getApIp() { return apIp; };
    void setClientIp(IPAddress ip);
    void setClientIp(uint8_t ip0, uint8_t ip1, uint8_t ip2, uint8_t ip3) { setClientIp(IPAddress(ip0, ip1, ip2, ip3)); };
    IPAddress getClientIp() { return clientIp; };
    IPAddress localIP() { return clientIp; };
    void setApDns(IPAddress ip);
    void setApDns(uint8_t ip0, uint8_t ip1, uint8_t ip2, uint8_t ip3) { setApDns(IPAddress(ip0, ip1, ip2, ip3)); };
    IPAddress getApDns() { return apDns; };
    void setClientDns(IPAddress ip);
    void setClientDns(uint8_t ip0, uint8_t ip1, uint8_t ip2, uint8_t ip3) { setClientDns(IPAddress(ip0, ip1, ip2, ip3)); };
    IPAddress getClientDns() { return clientDns; };
    IPAddress dnsIP() { return clientDns; };
    void setApSubnet(IPAddress ip);
    void setApSubnet(uint8_t ip0, uint8_t ip1, uint8_t ip2, uint8_t ip3) { setApSubnet(IPAddress(ip0, ip1, ip2, ip3)); };
    IPAddress getApSubnet() { return apSubnet; };
    void setClientSubnet(IPAddress ip);
    void setClientSubnet(uint8_t ip0, uint8_t ip1, uint8_t ip2, uint8_t ip3) { setClientSubnet(IPAddress(ip0, ip1, ip2, ip3)); };
    IPAddress getClientSubnet() { return clientSubnet; };
    IPAddress subnetMask() { return clientSubnet; };
    void setApGateway(IPAddress ip);
    void setApGateway(uint8_t ip0, uint8_t ip1, uint8_t ip2, uint8_t ip3) { setApGateway(IPAddress(ip0, ip1, ip2, ip3)); };
    IPAddress getApGatewayt() { return apGateway; };
    void setClientGateway(IPAddress ip);
    void setClientGateway(uint8_t ip0, uint8_t ip1, uint8_t ip2, uint8_t ip3) { setClientGateway(IPAddress(ip0, ip1, ip2, ip3)); };
    IPAddress getClientGateway() { return clientGateway; };
    IPAddress gatewayIP() { return clientGateway; };

    virtual void clientOn();
    void clientOff();
    virtual void apOn();
    void apOff();
    void setClientDhcp();
    void resetClientDhcp();
    bool getClientIsDhcp() { return clientIsDhcp; };
    bool getClientStatus() { return clientStatus; }
    virtual void pool() = 0;
    bool canStartServer() { return isCanStartServer; };
    virtual bool isImitation() { return false; }
    virtual bool isBusy() { return busy; };
    void setBusy() { busy = true; };
    void resetBusy() { busy = false; };
    virtual bool isReady() { return getClientStatus(); };

protected:
    uint8_t apMac[6] = {0, 0, 0, 0, 0, 0};
    uint8_t clientMac[6] = {0, 0, 0, 0, 0, 0};
    char apSsid[40] = "";
    char apPassword[40] = "";
    char clientSsid[40] = "";
    char clientPassword[40] = "";
    bool busy = false;

    IPAddress apIp = IPAddress(0, 0, 0, 0);
    IPAddress clientIp = IPAddress(0, 0, 0, 0);
    IPAddress apDns = IPAddress(0, 0, 0, 0);
    IPAddress clientDns = IPAddress(0, 0, 0, 0);
    IPAddress apSubnet = IPAddress(255, 255, 255, 0);
    IPAddress clientSubnet = IPAddress(255, 255, 255, 0);
    IPAddress apGateway = IPAddress(0, 0, 0, 0);
    IPAddress clientGateway = IPAddress(0, 0, 0, 0);

    bool apIsNeedReconect = false;
    bool apWorkStatus = false;
    bool clientIsNeedReconect = false;
    bool clientWorkStatus = false;
    bool clientStatus = false;
    bool clientIsDhcp = true;
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

#include "flprogWifiClient.h"
#include "flprogWifiServer.h"
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
