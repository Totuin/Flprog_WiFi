#include "flprogWifiClient.h"

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
#else
int FLProgWiFiClient::connect(IPAddress ip, uint16_t port)
{
    (void)ip;
    (void)port;
    return 0;
}

int FLProgWiFiClient::connect(const char *host, uint16_t port)
{
    (void)host;
    (void)port;
    return 0;
}

size_t FLProgWiFiClient::write(const uint8_t *buf, size_t size)
{
    (void)size;
    (void)buf;
    return 0;
}

size_t FLProgWiFiClient::write(uint8_t val)
{
    (void)val;
    return 0;
}
int FLProgWiFiClient::read( uint8_t *buf, size_t size)
{
    (void)size;
    (void)buf;
    return 0;
}

#endif
