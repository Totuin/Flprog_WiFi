#pragma once
#include "flprogWiFi.h"

class FLProgAbstractWiFiUDP
{
public:
    virtual uint8_t begin(uint16_t port);
    virtual uint8_t beginMulticast(IPAddress addr, uint16_t port);
    virtual void stop(){};
    virtual uint8_t beginMulticast(IPAddress interfaceAddr, IPAddress multicast, uint16_t port);
    virtual int beginPacket(IPAddress ip, uint16_t port);
    virtual int beginPacket(const char *host, uint16_t port);
    virtual int beginPacketMulticast(IPAddress multicastAddress, uint16_t port, IPAddress interfaceAddress, int ttl = 1);
    virtual int endPacket() { return 0; };
    virtual size_t write(uint8_t data);
    virtual size_t write(const uint8_t *buffer, size_t size);
    virtual int parsePacket() { return 0; };
    virtual int available() { return 0; };
    virtual int read() { return 0; };
    virtual int read(unsigned char *buffer, size_t len);
    virtual int peek() { return 0; };
    virtual void flush(){};
    virtual IPAddress remoteIP() { return IPAddress(0, 0, 0, 0); };
    virtual uint16_t remotePort() { return 0; };
    virtual IPAddress destinationIP() { return IPAddress(0, 0, 0, 0); };
    virtual uint16_t localPort() { return 0; };
    virtual void stopAll(){};

    int read(char *buffer, size_t len) { return read((unsigned char *)buffer, len); };

protected:
    FLProgAbstracttWiFiInterface *interface;
};

#ifdef FLPROG_WIFI_TCP_DEVICE

class FLProgWiFiUDP : public FLProgAbstractWiFiUDP
{
public:
    FLProgWiFiUDP(FLProgAbstracttWiFiInterface *sourse) { interface = sourse; };
    virtual uint8_t begin(uint16_t port) { return udp.begin(port); };

    // virtual uint8_t beginMulticast(IPAddress addr, uint16_t port) { return udp.beginMulticast(addr, port); };
    // virtual uint8_t beginMulticast(IPAddress interfaceAddr, IPAddress multicast, uint16_t port) { return udp.beginMulticast(interfaceAddr, multicast, port); };

    virtual void stop() { udp.stop(); };
    virtual int beginPacket(IPAddress ip, uint16_t port) { return udp.beginPacket(ip, port); };
    virtual int beginPacket(const char *host, uint16_t port) { return udp.beginPacket(host, port); };

    // virtual int beginPacketMulticast(IPAddress multicastAddress, uint16_t port, IPAddress interfaceAddress, int ttl = 1) { return udp.beginPacketMulticast(multicastAddress, port, interfaceAddress, ttl); };

    virtual int endPacket() { return udp.endPacket(); };
    virtual size_t write(uint8_t data) { return udp.write(data); };
    virtual size_t write(const uint8_t *buffer, size_t size) { return udp.write(buffer, size); };
    virtual int parsePacket() { return udp.parsePacket(); };
    virtual int available() { return udp.available(); };
    virtual int read() { return udp.read(); };
    virtual int read(unsigned char *buffer, size_t len) { return udp.read(buffer, len); };
    virtual int peek() { return udp.peek(); };
    virtual void flush() { udp.flush(); };
    virtual IPAddress remoteIP() { return udp.remoteIP(); };
    virtual uint16_t remotePort() { return udp.remotePort(); };

    // virtual IPAddress destinationIP() { return udp.destinationIP(); };
    // virtual uint16_t localPort() { return udp.localPort(); };

    // virtual void stopAll() { udp.stopAll(); };

protected:
    WiFiUDP udp;
};

#else
class FLProgWiFiUDP : public FLProgAbstractWiFiUDP
{
public:
    FLProgWiFiUDP(FLProgAbstracttWiFiInterface *sourse) { interface = sourse; };
};
#endif