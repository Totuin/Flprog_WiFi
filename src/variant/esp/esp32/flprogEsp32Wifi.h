#pragma once
#include "flprogWiFi.h"
#ifdef ARDUINO_ARCH_ESP32


class FLProgWiFiClient : public FLProgAbstractWiFiClient
{
public:
    FLProgWiFiClient(){};
    FLProgWiFiClient(WiFiClient _client);
    virtual uint8_t connected() { return client.connected(); };
    virtual int connect(IPAddress ip, uint16_t port) { return client.connect(ip, port); };
    virtual int connect(IPAddress ip, uint16_t port, int32_t timeout_ms);
    virtual int connect(const char *host, uint16_t port) { return client.connect(host, port); };
    virtual int connect(const char *host, uint16_t port, int32_t timeout_ms);
    virtual size_t write(uint8_t data) { return client.write(data); };
    virtual size_t write(const uint8_t *buf, size_t size) { return client.write(buf, size); };
    virtual int available() { return client.available(); };
    virtual int read() { return client.read(); };
    virtual int read(uint8_t *buf, size_t size) { return client.read(buf, size); };
    virtual int peek() { return client.peek(); };
    virtual void flush() { client.flush(); };
    virtual void stop() { client.stop(); };
    virtual IPAddress remoteIP() { return client.remoteIP(); };
    virtual uint16_t remotePort() { return client.remotePort(); };
    virtual IPAddress localIP() { return client.localIP(); };
    virtual uint16_t localPort() { return client.localPort(); };

    size_t write_P(PGM_P buf, size_t size) { return client.write_P(buf, size); };
    size_t write(Stream &stream) { return client.write(stream); };
    IPAddress remoteIP(int fd) { return client.remoteIP(fd); };
    uint16_t remotePort(int fd) { return client.remotePort(fd); };
    IPAddress localIP(int fd) { return client.localIP(fd); };
    uint16_t localPort(int fd) { return client.localPort(fd); };

protected:
    WiFiClient client;
};



class FlprogWiFiServer : public FlprogAbstractWiFiServer
{
public:
    FlprogWiFiServer(FLProgAbstracttWiFiInterface *sourse, int _port);
    FLProgWiFiClient accept();
    FLProgWiFiClient available() { return accept(); };
    virtual void setNoDelay(bool nodelay);
    virtual bool getNoDelay();
    virtual bool hasClient();
    virtual void end();
    virtual void close();
    virtual void stop();
    virtual bool listening();

    int setTimeout(uint32_t seconds);
    void stopAll();

protected:
    WiFiServer *server;
};

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