#include "flprogRP2040Wifi.h"

#ifdef ARDUINO_ARCH_RP2040
#ifdef ARDUINO_RASPBERRY_PI_PICO_W

//-----------------------------FLProgOnBoardWifi---------------------------
void FLProgOnBoardWifi::pool()
{
    clientStatus = WiFi.status() == WL_CONNECTED;

    if (isNeedReconect || apIsNeedReconect)
    {
        reconnect();
    }
    if (clientStatus)
    {
        if (needUpdateClientData)
        {
            ip = WiFi.localIP();
            apIp = ip;
            subnetIp = WiFi.subnetMask();
            apSubnetIp = subnetIp;
            gatewayIp = WiFi.gatewayIP();
            apGatewayIp = gatewayIp;
            dnsIp = gatewayIp;
            apDnsIp = dnsIp;
            needUpdateClientData = false;
            WiFi.macAddress(macAddress);
            WiFi.macAddress(apMacaddress);
        }
    }
    else
    {
        needUpdateClientData = true;
        if (clientWorkStatus)
        {
            clientReconnect();
        }
    }
}

void FLProgOnBoardWifi::reconnect()
{
    if (apWorkStatus)
    {
        mode = WIFI_AP;
    }
    else
    {
        if (clientWorkStatus)
        {
            mode = WIFI_STA;
        }
        else
        {
            mode = WIFI_OFF;
        }
    }
    WiFi.mode(mode);
    if (clientStatus)
    {
        WiFi.disconnect();
    }
    if (mode == WIFI_OFF)
    {
        isNeedReconect = false;
        apIsNeedReconect = false;
        return;
    }
    if (mode == WIFI_AP)
    {
        WiFi.begin(apSsid, apPassword);
        WiFi.beginAP(apSsid, apPassword);
        isNeedReconect = false;
        apIsNeedReconect = false;
        isCanStartServer = true;
        return;
    }
    WiFi.setHostname("Flprog-PicoW2");
    if (isDhcp)
    {
        WiFi.config(IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0));
    }
    else
    {
        if (ip == IPAddress(0, 0, 0, 0))
        {
            WiFi.config(IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0));
        }
        else
        {
            if (gatewayIp == IPAddress(0, 0, 0, 0))
            {
                gatewayIp = ip;
                gatewayIp[3] = 1;
            }
            if (dnsIp == IPAddress(0, 0, 0, 0))
            {
                dnsIp = ip;
                dnsIp[3] = 1;
            }
            WiFi.config(ip, dnsIp, gatewayIp, subnetIp);
        }
    }
    WiFi.begin(clientSsid, clientPassword);

    isCanStartServer = true;
    lastReconnectTime = millis();
    isNeedReconect = false;
    apIsNeedReconect = false;
}

void FLProgOnBoardWifi::clientReconnect()
{
    if (!clientWorkStatus)
    {
        return;
    }
    if (!flprog::isTimer(lastReconnectTime, reconnectPeriod))
    {
        return;
    }
    lastReconnectTime = millis();
    if (isDhcp)
    {
        WiFi.config(IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0));
    }
    else
    {
        if (gatewayIp == IPAddress(0, 0, 0, 0))
        {
            gatewayIp = ip;
            gatewayIp[3] = 1;
        }
        if (dnsIp == IPAddress(0, 0, 0, 0))
        {
            dnsIp = ip;
            dnsIp[3] = 1;
        }
        WiFi.config(ip, dnsIp, gatewayIp, subnetIp);
    }

    WiFi.begin(clientSsid, clientPassword);
    isCanStartServer = true;
}

void FLProgOnBoardWifi::clientOn()
{
    if (clientWorkStatus)
    {
        return;
    }
    clientWorkStatus = true;
    apWorkStatus = false;
    isNeedReconect = true;
}

void FLProgOnBoardWifi::apOn()
{
    if (apWorkStatus)
    {
        return;
    }
    apWorkStatus = true;
    clientWorkStatus = false;
    apIsNeedReconect = true;
}
#endif
#endif