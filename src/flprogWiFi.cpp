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
    isNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::setClientPassword(String password)
{
    if (password.equals(String(clientPassword)))
    {
        return;
    }
    password.toCharArray(clientPassword, 40);
    isNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::apMac(uint8_t m0, uint8_t m1, uint8_t m2, uint8_t m3, uint8_t m4, uint8_t m5)
{
    if (flprog::applyMac(m0, m1, m2, m3, m4, m5, apMacaddress))
    {
        apIsNeedReconect = true;
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

void FLProgAbstracttWiFiInterface::apDns(IPAddress ip)
{
    if (ip == apDnsIp)
    {
        return;
    }
    apDnsIp = ip;
    apIsNeedReconect = true;
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


void FLProgAbstracttWiFiInterface::apGateway(IPAddress ip)
{
    if (ip == apGatewayIp)
    {
        return;
    }
    apGatewayIp = ip;
    apIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::clientOn()
{
    if (clientWorkStatus)
    {
        return;
    }
    clientWorkStatus = true;
    isNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::clientOff()
{
    if (!clientWorkStatus)
    {
        return;
    }
    clientWorkStatus = false;
    isNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::clientMode(bool val)
{
    if (!clientWorkStatus == val)
    {
        return;
    }
    clientWorkStatus = val;
    isNeedReconect = true;
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



