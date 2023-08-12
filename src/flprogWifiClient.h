#pragma once
#include "Arduino.h"
#include "Client.h"
#include "flprogUtilites.h"

#ifdef ARDUINO_ARCH_ESP8266
#define FLPROG_WIFI_TCP_CLIENT
#include "ESP8266WiFi.h"
#endif

#ifdef ARDUINO_ARCH_ESP32
#define FLPROG_WIFI_TCP_CLIENT
#include "WiFi.h"
#endif

#ifdef ARDUINO_ARCH_RP2040
#ifdef ARDUINO_RASPBERRY_PI_PICO_W
#define FLPROG_WIFI_TCP_CLIENT
#include "WiFi.h"
#endif
#endif

class FLProgAbstractWiFiClient : public Client
{
public:
    virtual uint8_t connected() { return 0; };
    virtual int connect(IPAddress ip, uint16_t port);
    virtual int connect(IPAddress ip, uint16_t port, int32_t timeout_ms);
    virtual int connect(const char *host, uint16_t port);
    virtual int connect(const char *host, uint16_t port, int32_t timeout_ms);
    virtual size_t write(uint8_t data);
    virtual size_t write(const uint8_t *buf, size_t size);
    virtual int available() { return 0; };
    virtual int read() { return 0; };
    virtual int read(uint8_t *buf, size_t size);
    virtual int peek() { return 0; };
    virtual void flush(){};
    virtual void stop(){};
    virtual IPAddress remoteIP() { return IPAddress(0, 0, 0, 0); };
    virtual uint16_t remotePort() { return 0; };
    virtual IPAddress localIP() { return IPAddress(0, 0, 0, 0); };
    virtual uint16_t localPort() { return 0; };
    operator bool() { return connected(); }
    using Print::write;
};

#ifdef FLPROG_WIFI_TCP_CLIENT
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

protected:
    WiFiClient client;
};
#else
class FLProgWiFiClient : public FLProgAbstractWiFiClient
{
};
#endif