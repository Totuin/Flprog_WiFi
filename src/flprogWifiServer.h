#pragma once
#include "flprogWifiClient.h"
#include "flprogWiFi.h"

class FlprogAbstractWiFiServer
{
public:
    void begin(uint16_t port = 0) { (void)port; };
    void begin(uint16_t port, int reuse_enable);
    virtual void setNoDelay(bool nodelay) { (void)nodelay; };
    virtual bool getNoDelay() { return false; };
    virtual bool hasClient() { return false; };
    virtual void end(){};
    virtual void close(){};
    virtual void stop(){};
    virtual bool listening() { return false; };
    operator bool() { return listening(); }
    virtual FLProgWiFiClient accept();
    virtual FLProgWiFiClient available() { return accept(); };

protected:
    FLProgAbstracttWiFiInterface *interface;
    bool serverIsBegin = false;
    int port = 80;
};

#ifdef FLPROG_WIFI_TCP_DEVICE
class FlprogWiFiServer : public FlprogAbstractWiFiServer
{
public:
    FlprogWiFiServer(FLProgAbstracttWiFiInterface *sourse, int _port);
    virtual FLProgWiFiClient accept();
    virtual FLProgWiFiClient available() { return accept(); };
    virtual void setNoDelay(bool nodelay);
    virtual bool getNoDelay();
    virtual bool hasClient();
    virtual void end();
    virtual void close();
    virtual void stop();
    virtual bool listening();

protected:
    WiFiServer *server;
};

#else
class FlprogWiFiServer : public FlprogAbstractWiFiServer
{
public:
    FlprogWiFiServer(FLProgAbstracttWiFiInterface *sourse, int _port);
};
#endif