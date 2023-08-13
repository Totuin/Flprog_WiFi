#include "flprogRP2040Wifi.h"

#ifdef ARDUINO_ARCH_RP2040
#ifdef ARDUINO_RASPBERRY_PI_PICO_W

//-----------------------------FLProgOnBoardWifi---------------------------
void FLProgOnBoardWifi::pool()
{
    clientStatus = WiFi.status() == WL_CONNECTED;

    if (clientIsNeedReconect || apIsNeedReconect)
    {
        reconnect();
    }
    if (clientStatus)
    {
        if (needUpdateClientData)
        {
            clientIp = WiFi.localIP();
            apIp = clientIp;
            clientSubnetIp = WiFi.subnetMask();
            apSubnetIp = clientSubnetIp;
            clientGatewayIp = WiFi.gatewayIP();
            apGatewayIp = clientGatewayIp;
            clientDnsIp = clientGatewayIp;
            apDnsIp = clientDnsIp;
            needUpdateClientData = false;
            WiFi.macAddress(clientMacAddress);
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
        clientIsNeedReconect = false;
        apIsNeedReconect = false;
        return;
    }
    if (mode == WIFI_AP)
    {
        WiFi.begin(apSsid, apPassword);
        WiFi.beginAP(apSsid, apPassword);
        clientIsNeedReconect = false;
        apIsNeedReconect = false;
        isCanStartServer = true;
        return;
    }
    WiFi.setHostname("Flprog-PicoW2");
    if (clientIsDhcp)
    {
        WiFi.config(IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0));
    }
    else
    {
        if (clientIp == IPAddress(0, 0, 0, 0))
        {
            WiFi.config(IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0));
        }
        else
        {
            if (clientGatewayIp == IPAddress(0, 0, 0, 0))
            {
                clientGatewayIp = clientIp;
                clientGatewayIp[3] = 1;
            }
            if (clientDnsIp == IPAddress(0, 0, 0, 0))
            {
                clientDnsIp = clientIp;
                clientDnsIp[3] = 1;
            }
            WiFi.config(clientIp, clientDnsIp, clientGatewayIp, clientSubnetIp);
        }
    }
    WiFi.begin(clientSsid, clientPassword);

    isCanStartServer = true;
    lastReconnectTime = millis();
    clientIsNeedReconect = false;
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
    if (clientIsDhcp)
    {
        WiFi.config(IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0));
    }
    else
    {
        if (clientGatewayIp == IPAddress(0, 0, 0, 0))
        {
            clientGatewayIp = clientIp;
            clientGatewayIp[3] = 1;
        }
        if (clientDnsIp == IPAddress(0, 0, 0, 0))
        {
            clientDnsIp = clientIp;
            clientDnsIp[3] = 1;
        }
        WiFi.config(clientIp, clientDnsIp, clientGatewayIp, clientSubnetIp);
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
    clientIsNeedReconect = true;
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