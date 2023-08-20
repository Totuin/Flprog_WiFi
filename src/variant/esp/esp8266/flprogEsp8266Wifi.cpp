#include "flprogEsp8266Wifi.h"
#ifdef ARDUINO_ARCH_ESP8266

//-----------------------------FLProgOnBoardWifi---------------------------
void FLProgOnBoardWifi::pool()
{
    if (isNeedReconect || apIsNeedReconect)
    {
        reconnect();
    }
    clientStatus = WiFi.status() == WL_CONNECTED;
    if (clientStatus)
    {
        isCanStartServer = true;
        if (needUpdateClientData)
        {
            ip = WiFi.localIP();
            subnetIp = WiFi.subnetMask();
            gatewayIp = WiFi.gatewayIP();
            dnsIp = WiFi.dnsIP();
            WiFi.macAddress(macAddress);
            needUpdateClientData = false;
        }
    }
    else
    {
        isCanStartServer = false;
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
    apReconnect();
    clientReconnect();
}

void FLProgOnBoardWifi::clientReconnect()
{
    if (!isNeedReconect)
    {
        return;
    }
    isNeedReconect = false;
    if (!clientWorkStatus)
    {
        if (clientStatus)
        {
            WiFi.disconnect();
        }
        return;
    }
    wifi_set_macaddr(STATION_IF, macAddress);
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
            WiFi.config(ip, gatewayIp, subnetIp, dnsIp, dnsIp);
        }
    }
    WiFi.begin(clientSsid, clientPassword);
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
    wifi_set_macaddr(SOFTAP_IF, apMacaddress);
    if (apGatewayIp == IPAddress(0, 0, 0, 0))
    {
        apGatewayIp = apIp;
        apGatewayIp[3] = 1;
    }

    WiFi.softAPConfig(apIp, apGatewayIp, apSubnetIp);
    WiFi.softAP(apSsid, apPassword);
    if (!clientWorkStatus)
    {
        isCanStartServer = true;
    }
}

#endif