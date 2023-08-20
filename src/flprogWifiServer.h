#pragma once
#include "flprogUtilites.h"
#include "flprogWifiClient.h"

#ifdef ARDUINO_ARCH_ESP8266
#define FLPROG_WIFI_TCP_SERVER
#include "ESP8266WiFi.h"
#endif

#ifdef ARDUINO_ARCH_ESP32
#define FLPROG_WIFI_TCP_SERVER
#include "WiFi.h"
#endif

#ifdef ARDUINO_ARCH_RP2040
#ifdef ARDUINO_RASPBERRY_PI_PICO_W
#define FLPROG_WIFI_TCP_SERVER
#include "WiFi.h"
#endif
#endif



class FLProgAbstractWiFiServer : public FLProgAbstractTcpServer
{
public:
    virtual void begin(uint16_t port = 0) { (void)port; };
    virtual void begin(uint16_t port, int reuse_enable);
    virtual void setNoDelay(bool nodelay) { (void)nodelay; };
    virtual bool getNoDelay() { return false; };
    virtual bool hasClient() { return false; };
    virtual void end(){};
    virtual void close(){};
    virtual void stop(){};
    virtual bool listening() { return false; };
    operator bool() { return listening(); }
    virtual FLProgWiFiClient accept();

protected:
    FLProgAbstractTcpInterface *interface;
    bool serverIsBegin = false;
    int port = 80;
};

#ifdef FLPROG_WIFI_TCP_SERVER
class FLProgWiFiServer : public FLProgAbstractWiFiServer
{
public:
    FLProgWiFiServer(FLProgAbstractTcpInterface *sourse, int _port);
    virtual FLProgWiFiClient accept();
    virtual void begin(uint16_t port = 0);
    virtual void setNoDelay(bool nodelay);
    virtual bool getNoDelay();
    virtual bool hasClient();
    virtual void end();
    virtual void close();
    virtual void stop();
   // virtual bool listening();
    virtual FLProgWiFiClient *client() { return &cl; };
    virtual void setClient() { cl = accept(); };

protected:
    WiFiServer server=WiFiServer(port) ;
    FLProgWiFiClient cl;
};

#else
class FLProgWiFiServer : public FLProgAbstractWiFiServer
{
public:
    FLProgWiFiServer(FLProgAbstractTcpInterface *sourse, int _port);
};
#endif
