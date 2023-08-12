#include "flprofWifiUdp.h"

//----------------------------------FlprogAbstractWifiUDP-------------------

uint8_t FLProgAbstractWiFiUDP::begin(uint16_t port)
{
    (void)port;
    return 0;
}

uint8_t FLProgAbstractWiFiUDP::beginMulticast(IPAddress addr, uint16_t port)
{
    (void)port;
    (void)addr;
    return 0;
}

uint8_t FLProgAbstractWiFiUDP::beginMulticast(IPAddress interfaceAddr, IPAddress multicast, uint16_t port)
{
    (void)interfaceAddr;
    (void)multicast;
    (void)port;
    return 0;
}

int FLProgAbstractWiFiUDP::beginPacket(IPAddress ip, uint16_t port)
{
    (void)ip;
    (void)port;
    return 0;
}

int FLProgAbstractWiFiUDP::beginPacket(const char *host, uint16_t port)
{
    (void)host;
    (void)port;
    return 0;
}

int FLProgAbstractWiFiUDP::beginPacketMulticast(IPAddress multicastAddress, uint16_t port, IPAddress interfaceAddress, int ttl)
{
    (void)multicastAddress;
    (void)port;
    (void)interfaceAddress;
    (void)ttl;
    return 0;
}

size_t FLProgAbstractWiFiUDP::write(uint8_t data)
{
    (void)data;
    return 0;
}

size_t FLProgAbstractWiFiUDP::write(const uint8_t *buffer, size_t size)
{
    (void)buffer;
    (void)size;
    return 0;
}
int FLProgAbstractWiFiUDP::read(unsigned char *buffer, size_t len)
{
    (void)buffer;
    (void)len;
    return 0;
}
