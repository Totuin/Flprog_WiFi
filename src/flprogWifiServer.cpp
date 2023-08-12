#include "flprogWifiServer.h"

//----------------------------------FlprogAbstractWiFiServer-----------------

void FlprogAbstractWiFiServer::begin(uint16_t port, int reuse_enable)
{
    (void)port;
    (void)reuse_enable;
}

FLProgWiFiClient FlprogAbstractWiFiServer::accept()
{
    return FLProgWiFiClient();
}

//----------------------------------FlprogWiFiServer-----------------
#ifdef FLPROG_WIFI_TCP_DEVICE
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
#else
FlprogWiFiServer::FlprogWiFiServer(FLProgAbstracttWiFiInterface *sourse, int _port)
{
    (void)sourse;
    (void)_port;
};
#endif