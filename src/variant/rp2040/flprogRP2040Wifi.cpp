#include "flprogRP2040Wifi.h"

#ifdef ARDUINO_ARCH_RP2040
#ifdef ARDUINO_RASPBERRY_PI_PICO_W
//-------------------------FLProgWiFiClient-----------------------------
FLProgWiFiClient::FLProgWiFiClient(WiFiClient _client)
{
    client = _client;
}
int FLProgWiFiClient::connect(IPAddress ip, uint16_t port, int32_t timeout_ms)
{
    (void)timeout_ms;
    return connect(ip, port);
}

int FLProgWiFiClient::connect(const char *host, uint16_t port, int32_t timeout_ms)
{
    (void)timeout_ms;
    return connect(host, port);
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
        server->begin();
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
        server->stop();
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
            clientSubnet = WiFi.subnetMask();
            apSubnet = clientSubnet;
            clientGateway = WiFi.gatewayIP();
            apGateway = clientGateway;
            clientDns = clientGateway;
            apDns = clientDns;
            needUpdateClientData = false;
            WiFi.macAddress(clientMac);
            WiFi.macAddress(apMac);
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
        WiFi.config(clientIp, clientDns, clientGateway, clientSubnet);
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
        WiFi.config(clientIp, clientDns, clientGateway, clientSubnet);
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