#include "flprogEsp32Wifi.h"
#ifdef ARDUINO_ARCH_ESP32

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
        if (needUpdateClientData)
        {
            ip = WiFi.localIP();
            subnetIp = WiFi.subnetMask();
            gatewayIp = WiFi.gatewayIP();
            dnsIp = WiFi.dnsIP();
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

    esp_wifi_set_mac(WIFI_IF_STA, macAddress);

    if (isDhcp)
    {
        WiFi.config(IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0));
    }
    else
    {
        if (ip == IPAddress(0, 0, 0, 0))
        {
            WiFi.config(IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0), IPAddress(0, 0, 0, 0));
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