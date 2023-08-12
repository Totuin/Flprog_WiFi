#include "flprogEsp8266Wifi.h"
#ifdef ARDUINO_ARCH_ESP8266

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
            clientSubnet = WiFi.subnetMask();
            clientGateway = WiFi.gatewayIP();
            clientDns = WiFi.dnsIP();
            WiFi.macAddress(clientMac);
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
    wifi_set_macaddr(STATION_IF, clientMac);
    if (clientIsDhcp)
    {
        WiFi.config(0U, 0U, 0U, 0U, 0U);
    }
    else
    {
        if (clientGateway == IPAddress(0, 0, 0, 0))
        {
            clientGateway = clientIp;
            clientGateway[3] = 1;
        }
        if (clientDns == IPAddress(0, 0, 0, 0))
        {
            clientDns = clientIp;
            clientDns[3] = 1;
        }
        WiFi.config(clientIp, clientGateway, clientSubnet, clientDns, clientDns);
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
    wifi_set_macaddr(SOFTAP_IF, apMac);
    if (apGateway == IPAddress(0, 0, 0, 0))
    {
        apGateway = apIp;
        apGateway[3] = 1;
    }

    WiFi.softAPConfig(apIp, apGateway, apSubnet);
    WiFi.softAP(apSsid, apPassword);
    isCanStartServer = true;
}

#endif