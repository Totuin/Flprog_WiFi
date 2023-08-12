#include "flprogWifiClient.h"

//--------------------FLProgAbstractWiFiClient ----------------------

int FLProgAbstractWiFiClient::connect(IPAddress ip, uint16_t port)
{
    (void)ip;
    (void)port;
    return 0;
}

int FLProgAbstractWiFiClient::connect(IPAddress ip, uint16_t port, int32_t timeout_ms)
{
    (void)ip;
    (void)port;
    (void)timeout_ms;
    return 0;
}

int FLProgAbstractWiFiClient::connect(const char *host, uint16_t port)
{
    (void)host;
    (void)port;
    return 0;
}

int FLProgAbstractWiFiClient::connect(const char *host, uint16_t port, int32_t timeout_ms)
{
    (void)host;
    (void)port;
    (void)timeout_ms;
    return 0;
}

size_t FLProgAbstractWiFiClient::write(uint8_t data)
{
    (void)data;
    return 0;
}

size_t FLProgAbstractWiFiClient::write(const uint8_t *buf, size_t size)
{
    (void)buf;
    (void)size;
    return 0;
}

int FLProgAbstractWiFiClient::read(uint8_t *buf, size_t size)
{
    (void)buf;
    (void)size;
    return 0;
}

//-------------------------FLProgWiFiClient-----------------------------
#ifdef FLPROG_WIFI_TCP_CLIENT
FLProgWiFiClient::FLProgWiFiClient(WiFiClient _client)
{
    client = _client;
}
int FLProgWiFiClient::connect(IPAddress ip, uint16_t port, int32_t timeout_ms)
{
    (void)timeout_ms;
    return connect(ip, port);
}

int FLProgWiFiClient::connect(const char *host, uint16_t port, int32_t timeout_ms)
{
    (void)timeout_ms;
    return connect(host, port);
}
#endif