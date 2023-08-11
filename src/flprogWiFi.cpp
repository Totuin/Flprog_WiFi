#include "flprogWiFi.h"

void FLProgAbstracttWiFiInterface::setApSsid(String ssid)
{
    if (ssid.equals(String(apSsid)))
    {
        return;
    }
    ssid.toCharArray(apSsid, 40);
    apIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::setApPassword(String password)
{
    if (password.equals(String(apPassword)))
    {
        return;
    }
    password.toCharArray(apPassword, 40);
    apIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::setClientSsidd(String ssid)
{
    if (ssid.equals(String(clientSsid)))
    {
        return;
    }
    ssid.toCharArray(clientSsid, 40);
    clientIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::setClientPassword(String password)
{
    if (password.equals(String(clientPassword)))
    {
        return;
    }
    password.toCharArray(clientPassword, 40);
    clientIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::setApMac(uint8_t m0, uint8_t m1, uint8_t m2, uint8_t m3, uint8_t m4, uint8_t m5)
{
    if (flprog::applyMac(m0, m1, m2, m3, m4, m5, apMac))
    {
        apIsNeedReconect = true;
    }
}

void FLProgAbstracttWiFiInterface::setClientMac(uint8_t m0, uint8_t m1, uint8_t m2, uint8_t m3, uint8_t m4, uint8_t m5)
{
    if (flprog::applyMac(m0, m1, m2, m3, m4, m5, clientMac))
    {
        clientIsNeedReconect = true;
    }
}

void FLProgAbstracttWiFiInterface::setApIp(IPAddress ip)
{
    if (ip == apIp)
    {
        return;
    }
    apIp = ip;
    apIsNeedReconect = true;
}
void FLProgAbstracttWiFiInterface::setClientIp(IPAddress ip)
{
    if (ip == clientIp)
    {
        return;
    }
    clientIp = ip;
    clientIsNeedReconect = true;
    clientIsDhcp = false;
}

void FLProgAbstracttWiFiInterface::setApDns(IPAddress ip)
{
    if (ip == apDns)
    {
        return;
    }
    apDns = ip;
    apIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::setClientDns(IPAddress ip)
{
    if (ip == clientDns)
    {
        return;
    }
    clientDns = ip;
    clientIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::setApSubnet(IPAddress ip)
{
    if (ip == apSubnet)
    {
        return;
    }
    apSubnet = ip;
    apIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::setClientSubnet(IPAddress ip)
{
    if (ip == clientSubnet)
    {
        return;
    }
    clientSubnet = ip;
    clientIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::setApGateway(IPAddress ip)
{
    if (ip == apGateway)
    {
        return;
    }
    apGateway = ip;
    apIsNeedReconect = true;
}
void FLProgAbstracttWiFiInterface::setClientGateway(IPAddress ip)
{
    if (ip == clientGateway)
    {
        return;
    }
    clientGateway = ip;
    clientIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::clientOn()
{
    if (clientWorkStatus)
    {
        return;
    }
    clientWorkStatus = true;
    clientIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::clientOff()
{
    if (!clientWorkStatus)
    {
        return;
    }
    clientWorkStatus = false;
    clientIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::apOn()
{
    if (apWorkStatus)
    {
        return;
    }
    apWorkStatus = true;
    apIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::apOff()
{
    if (!apWorkStatus)
    {
        return;
    }
    apWorkStatus = false;
    apIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::setClientDhcp()
{
    if (clientIsDhcp)
    {
        return;
    }
    clientIsDhcp = true;
    clientIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::resetClientDhcp()
{
    if (!clientIsDhcp)
    {
        return;
    }
    clientIsDhcp = false;
    clientIsNeedReconect = true;
}

//--------------------FLProgWiFiClient ----------------------

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

//----------------------------------FlprogAbstractWiFiServer-----------------

void FlprogAbstractWiFiServer::begin(uint16_t port, int reuse_enable)
{
    (void)port;
    (void)reuse_enable;
}

#ifndef FLPROG_WIFI_TCP_DEVICE
FLProgWiFiClient FlprogAbstractWiFiServer::accept()
{
    return FLProgWiFiClient();
}
#endif

//----------------------------------FlprogWiFiServer-----------------

#ifndef FLPROG_WIFI_TCP_DEVICE
FlprogWiFiServer::FlprogWiFiServer(FLProgAbstracttWiFiInterface *sourse, int _port)
{
    (void)sourse;
    (void)_port;
};
#endif