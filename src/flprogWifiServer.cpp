#include "flprogWifiServer.h"

//----------------------------------FlprogAbstractWiFiServer-----------------

void FLProgAbstractWiFiServer::begin(uint16_t port, int reuse_enable)
{
    (void)port;
    (void)reuse_enable;
}

FLProgWiFiClient FLProgAbstractWiFiServer::accept()
{
    return FLProgWiFiClient();
}

//----------------------------------FlprogWiFiServer-----------------
#ifdef FLPROG_WIFI_TCP_SERVER

void FLProgWiFiServer::begin(uint16_t _port)
{
    port = _port;
    serverIsBegin = false;
}

FLProgWiFiServer::FLProgWiFiServer(FLProgAbstractTcpInterface *sourse, int _port)
{
    port = _port;
    interface = sourse;
}

FLProgWiFiClient FLProgWiFiServer::accept()
{
    if (interface->canStartServer())
    {
        if (!serverIsBegin)
        {
            server.begin(port);
            serverIsBegin = true;
        }
        return FLProgWiFiClient(server.accept());
    }
    else
    {
        serverIsBegin = false;
    }
    if (serverIsBegin)
    {
        return FLProgWiFiClient(server.accept());
    }
    return FLProgWiFiClient();
}

void FLProgWiFiServer::setNoDelay(bool nodelay)
{
    if (serverIsBegin)
    {
        server.setNoDelay(nodelay);
    }
}

bool FLProgWiFiServer::getNoDelay()
{
    if (serverIsBegin)
    {
        return server.getNoDelay();
    }
    return false;
}

bool FLProgWiFiServer::hasClient()
{
    if (serverIsBegin)
    {
        return server.hasClient();
    }
    return false;
}

void FLProgWiFiServer::end()
{
    if (serverIsBegin)
    {
        server.stop();
    }
}

void FLProgWiFiServer::close()
{
    if (serverIsBegin)
    {
        server.close();
    }
}

void FLProgWiFiServer::stop()
{
    if (serverIsBegin)
    {
        server.stop();
    }
}
/*
bool FLProgWiFiServer::listening()
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
*/
#else
FLProgWiFiServer::FLProgWiFiServer(FLProgAbstractTcpInterface *sourse, int _port)
{
    (void)sourse;
    (void)_port;
};
#endif
