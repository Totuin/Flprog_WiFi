#include "flprogEsp32Wifi.h"
#ifdef ARDUINO_ARCH_ESP32

//-------------------------FLProgWiFiClient-----------------------------

FLProgWiFiClient::FLProgWiFiClient(WiFiClient _client)
{
    client = _client;
}

int FLProgWiFiClient::connect(IPAddress ip, uint16_t port, int32_t timeout_ms)
{
    return client.connect(ip, port, timeout_ms);
}

int FLProgWiFiClient::connect(const char *host, uint16_t port, int32_t timeout_ms)
{
    return client.connect(host, port, timeout_ms);
}

//-------------------------FlprogWiFiServer-----------------------------
FlprogWiFiServer::FlprogWiFiServer(FLProgAbstracttWiFiInterface *sourse, int _port)
{
    port = _port;
    server = new WiFiServer(port);
    interface = sourse;
}
FLProgWiFiClient FlprogWiFiServer::accept()
{
    if (serverIsBegin)
    {
        return FLProgWiFiClient(server->accept());
    }
    if (interface->canStartServer())
    {
        server->begin(port);
        serverIsBegin = true;
        return FLProgWiFiClient(server->accept());
    }
    return FLProgWiFiClient();
}

void FlprogWiFiServer::setNoDelay(bool nodelay)
{
    if (serverIsBegin)
    {
        server->setNoDelay(nodelay);
    }
}

bool FlprogWiFiServer::getNoDelay()
{
    if (serverIsBegin)
    {
        return server->getNoDelay();
    }
    return false;
}

bool FlprogWiFiServer::hasClient()
{
    if (serverIsBegin)
    {
        return server->hasClient();
    }
    return false;
}

void FlprogWiFiServer::end()
{
    if (serverIsBegin)
    {
        server->end();
    }
}
void FlprogWiFiServer::close()
{
    if (serverIsBegin)
    {
        server->close();
    }
}

void FlprogWiFiServer::stop()
{
    if (serverIsBegin)
    {
        server->stop();
    }
}

bool FlprogWiFiServer::listening()
{
    if (serverIsBegin)
    {
        if (server)
        {
            return true;
        }
    }
    return false;
}

int FlprogWiFiServer::setTimeout(uint32_t seconds)
{
    if (serverIsBegin)
    {
        return server->setTimeout(seconds);
    }
    return 0;
}

void FlprogWiFiServer::stopAll()
{
    if (serverIsBegin)
    {
        server->stopAll();
    }
}

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

    esp_wifi_set_mac(WIFI_IF_STA, clientMac);

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
    esp_wifi_set_mac(WIFI_IF_AP, apMac);
    if (apGateway == IPAddress(0, 0, 0, 0))
    {
        apGateway = apIp;
        apGateway[3] = 1;
    }
    WiFi.softAPConfig(apIp, apGateway, apSubnet);
    WiFi.softAP(apSsid, apPassword);
    isCanStartServer = true;
    WiFi.softAPConfig(apIp, apGateway, apSubnet);
}

#endif