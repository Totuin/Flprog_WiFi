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

void FLProgAbstracttWiFiInterface::apMac(uint8_t m0, uint8_t m1, uint8_t m2, uint8_t m3, uint8_t m4, uint8_t m5)
{
    if (flprog::applyMac(m0, m1, m2, m3, m4, m5, apMacaddress))
    {
        apIsNeedReconect = true;
    }
}

void FLProgAbstracttWiFiInterface::mac(uint8_t m0, uint8_t m1, uint8_t m2, uint8_t m3, uint8_t m4, uint8_t m5)
{
    if (flprog::applyMac(m0, m1, m2, m3, m4, m5, clientMacAddress))
    {
        clientIsNeedReconect = true;
    }
}

void FLProgAbstracttWiFiInterface::apLocalIP(IPAddress ip)
{
    if (ip == apIp)
    {
        return;
    }
    apIp = ip;
    apIsNeedReconect = true;
}
void FLProgAbstracttWiFiInterface::localIP(IPAddress ip)
{
    if (ip == clientIp)
    {
        return;
    }
    clientIp = ip;
    clientIsNeedReconect = true;
    clientIsDhcp = false;
}

void FLProgAbstracttWiFiInterface::apDns(IPAddress ip)
{
    if (ip == apDnsIp)
    {
        return;
    }
    apDnsIp = ip;
    apIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::dns(IPAddress ip)
{
    if (ip == clientDnsIp)
    {
        return;
    }
    clientDnsIp = ip;
    clientIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::apSubnet(IPAddress ip)
{
    if (ip == apSubnetIp)
    {
        return;
    }
    apSubnetIp = ip;
    apIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::subnet(IPAddress ip)
{
    if (ip == clientSubnetIp)
    {
        return;
    }
    clientSubnetIp = ip;
    clientIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::apGateway(IPAddress ip)
{
    if (ip == apGatewayIp)
    {
        return;
    }
    apGatewayIp = ip;
    apIsNeedReconect = true;
}
void FLProgAbstracttWiFiInterface::gateway(IPAddress ip)
{
    if (ip == clientGatewayIp)
    {
        return;
    }
    clientGatewayIp = ip;
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

void FLProgAbstracttWiFiInterface::clientMode(bool val)
{
    if (!clientWorkStatus == val)
    {
        return;
    }
    clientWorkStatus = val;
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

void FLProgAbstracttWiFiInterface::apMode(bool val)
{
    if (apWorkStatus == val)
    {
        return;
    }
    apWorkStatus = val;
    apIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::setDhcp()
{
    if (clientIsDhcp)
    {
        return;
    }
    clientIsDhcp = true;
    clientIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::resetDhcp()
{
    if (!clientIsDhcp)
    {
        return;
    }
    clientIsDhcp = false;
    clientIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::dhcpMode(bool val)
{
    if (clientIsDhcp == val)
    {
        return;
    }
    clientIsDhcp = val;
    clientIsNeedReconect = true;
}