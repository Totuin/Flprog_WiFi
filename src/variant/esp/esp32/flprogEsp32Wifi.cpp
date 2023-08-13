#include "flprogEsp32Wifi.h"
#ifdef ARDUINO_ARCH_ESP32

//-----------------------------FLProgOnBoardWifi---------------------------
void FLProgOnBoardWifi::pool()
{
    if (clientIsNeedReconect || apIsNeedReconect)
    {
        reconnect();
    }
    clientStatus = WiFi.status() == WL_CONNECTED;
    if (clientStatus)
    {
        if (needUpdateClientData)
        {
            clientIp = WiFi.localIP();
            clientSubnetIp = WiFi.subnetMask();
            clientGatewayIp = WiFi.gatewayIP();
            clientDnsIp = WiFi.dnsIP();
            needUpdateClientData = false;
        }
    }
    else
    {
        needUpdateClientData = true;
    }
}

void FLProgOnBoardWifi::reconnect()
{

    if (WiFi.getAutoConnect() != true)
    {
        WiFi.setAutoConnect(true);
    }
    WiFi.setAutoReconnect(true);
    if (apWorkStatus)
    {
        if (clientWorkStatus)
        {
            mode = WIFI_AP_STA;
        }
        else
        {
            mode = WIFI_AP;
        }
    }
    else
    {
        if (clientWorkStatus)
        {
            mode = WIFI_STA;
        }
    }
    WiFi.mode(mode);
    clientReconnect();
    apReconnect();
}

void FLProgOnBoardWifi::clientReconnect()
{
    if (!clientIsNeedReconect)
    {
        return;
    }
    clientIsNeedReconect = false;
    if (!clientWorkStatus)
    {
        if (clientStatus)
        {
            WiFi.disconnect();
        }
        return;
    }

    esp_wifi_set_mac(WIFI_IF_STA, clientMacAddress);

    if (clientIsDhcp)
    {
        WiFi.config(0U, 0U, 0U, 0U, 0U);
    }
    else
    {
        if (clientIp == IPAddress(0, 0, 0, 0))
        {
            WiFi.config(0U, 0U, 0U, 0U, 0U);
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
            WiFi.config(clientIp, clientGatewayIp, clientSubnetIp, clientDnsIp, clientDnsIp);
        }
    }
    WiFi.begin(clientSsid, clientPassword);
    isCanStartServer = true;
}

void FLProgOnBoardWifi::apReconnect()
{
    if (!apIsNeedReconect)
    {
        return;
    }
    apIsNeedReconect = false;
    if (!apWorkStatus)
    {
        WiFi.softAPdisconnect();
        return;
    }
    esp_wifi_set_mac(WIFI_IF_AP, apMacaddress);
    if (apGatewayIp == IPAddress(0, 0, 0, 0))
    {
        apGatewayIp = apIp;
        apGatewayIp[3] = 1;
    }
    WiFi.softAPConfig(apIp, apGatewayIp, apSubnetIp);
    WiFi.softAP(apSsid, apPassword);
    isCanStartServer = true;
    WiFi.softAPConfig(apIp, apGatewayIp, apSubnetIp);
}

#endif