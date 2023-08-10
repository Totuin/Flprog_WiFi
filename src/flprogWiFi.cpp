#include "flprogWiFi.h"

void FLProgAbstracttWiFiInterface::setApSsid(String ssid)
{
    if (ssid.equals(String(apSsid)))
    {
        return;
    }
    ssid.toCharArray(apSsid, 40);
    apIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::setApPassword(String password)
{
    if (password.equals(String(apPassword)))
    {
        return;
    }
    password.toCharArray(apPassword, 40);
    apIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::setClientSsidd(String ssid)
{
    if (ssid.equals(String(clientSsid)))
    {
        return;
    }
    ssid.toCharArray(clientSsid, 40);
    clientIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::setClientPassword(String password)
{
    if (password.equals(String(clientPassword)))
    {
        return;
    }
    password.toCharArray(clientPassword, 40);
    clientIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::setApMac(uint8_t m0, uint8_t m1, uint8_t m2, uint8_t m3, uint8_t m4, uint8_t m5)
{
    if (flprog::applyMac(m0, m1, m2, m3, m4, m5, apMac))
    {
        apIsNeedReconect = true;
    }
}

void FLProgAbstracttWiFiInterface::setClientMac(uint8_t m0, uint8_t m1, uint8_t m2, uint8_t m3, uint8_t m4, uint8_t m5)
{
    if (flprog::applyMac(m0, m1, m2, m3, m4, m5, clientMac))
    {
        clientIsNeedReconect = true;
    }
}

void FLProgAbstracttWiFiInterface::setApIp(IPAddress ip)
{
    if (ip == apIp)
    {
        return;
    }
    apIp = ip;
    apIsNeedReconect = true;
}
void FLProgAbstracttWiFiInterface::setClientIp(IPAddress ip)
{
    if (ip == clientIp)
    {
        return;
    }
    clientIp = ip;
    clientIsNeedReconect = true;
    clientIsDhcp = false;
}

void FLProgAbstracttWiFiInterface::setApDns(IPAddress ip)
{
    if (ip == apDns)
    {
        return;
    }
    apDns = ip;
    apIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::setClientDns(IPAddress ip)
{
    if (ip == clientDns)
    {
        return;
    }
    clientDns = ip;
    clientIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::setApSubnet(IPAddress ip)
{
    if (ip == apSubnet)
    {
        return;
    }
    apSubnet = ip;
    apIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::setClientSubnet(IPAddress ip)
{
    if (ip == clientSubnet)
    {
        return;
    }
    clientSubnet = ip;
    clientIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::setApGateway(IPAddress ip)
{
    if (ip == apGateway)
    {
        return;
    }
    apGateway = ip;
    apIsNeedReconect = true;
}
void FLProgAbstracttWiFiInterface::setClientGateway(IPAddress ip)
{
    if (ip == clientGateway)
    {
        return;
    }
    clientGateway = ip;
    clientIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::clientOn()
{
    if (clientWorkStatus)
    {
        return;
    }
    clientWorkStatus = true;
    clientIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::clientOff()
{
    if (!clientWorkStatus)
    {
        return;
    }
    clientWorkStatus = false;
    clientIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::apOn()
{
    if (apWorkStatus)
    {
        return;
    }
    apWorkStatus = true;
    apIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::apOff()
{
    if (!apWorkStatus)
    {
        return;
    }
    apWorkStatus = false;
    apIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::setClientDhcp()
{
    if (clientIsDhcp)
    {
        return;
    }
    clientIsDhcp = true;
    clientIsNeedReconect = true;
}

void FLProgAbstracttWiFiInterface::resetClientDhcp()
{
    if (!clientIsDhcp)
    {
        return;
    }
    clientIsDhcp = false;
    clientIsNeedReconect = true;
}

//--------------------FLProgWiFiClient ----------------------
#ifdef FLPROG_WIFI_TCP_DEVICE
FLProgWiFiClient::FLProgWiFiClient(WiFiClient _client)
{
    client = _client;
}
#endif

uint8_t FLProgWiFiClient::connected()
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.connected();
#else
    return 0;
#endif
}

int FLProgWiFiClient::connect(IPAddress ip, uint16_t port)
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.connect(ip, port);
#else
    (void)ip;
    (void)port;
    return 0;
#endif
}
#ifdef ARDUINO_ARCH_ESP8266
int FLProgWiFiClient::connect(IPAddress ip, uint16_t port, int32_t timeout_ms)
{
    (void)timeout_ms;
    return connect(ip, port);
}
#else
int FLProgWiFiClient::connect(IPAddress ip, uint16_t port, int32_t timeout_ms)
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.connect(ip, port, timeout_ms);
#else
    (void)ip;
    (void)port;
    (void)itimeout_ms;
    return 0;
#endif
}
#endif

int FLProgWiFiClient::connect(const char *host, uint16_t port)
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.connect(host, port);
#else
    (void)host;
    (void)port;
    return 0;
#endif
}

#ifdef ARDUINO_ARCH_ESP8266
int FLProgWiFiClient::connect(const char *host, uint16_t port, int32_t timeout_ms)
{
    (void)timeout_ms;
    return connect(host, port);
}
#else
int FLProgWiFiClient::connect(const char *host, uint16_t port, int32_t timeout_ms)
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.connect(host, port, timeout_ms);
#else
    (void)host;
    (void)port;
    (void)timeout_ms;
    return 0;
#endif
}
#endif

size_t FLProgWiFiClient::write(uint8_t data)
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.write(data);
#else
    (void)data;
    return 0;
#endif
}

size_t FLProgWiFiClient::write(const uint8_t *buf, size_t size)
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.write(buf, size);
#else
    (void)buf;
    (void)size;
    return 0;
#endif
}
/*
size_t FLProgWiFiClient::write_P(PGM_P buf, size_t size)
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.write_P(buf, size);
#else
    (void)buf;
    (void)size;
    return 0;
#endif
}
*/
#ifdef ARDUINO_ARCH_ESP8266
size_t FLProgWiFiClient::write(Stream &stream)
{
    (void)stream;
    return 0;
}
#else
size_t FLProgWiFiClient::write(Stream &stream)
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.write(stream);
#else
    (void)stream;
    return 0;
#endif
}
#endif

int FLProgWiFiClient::available()
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.available();
#else
    return 0;
#endif
}

int FLProgWiFiClient::read()
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.read();
#else
    return 0;
#endif
}

int FLProgWiFiClient::read(uint8_t *buf, size_t size)
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.read(buf, size);
#else
    (void)buf;
    (void)size;
    return 0;
#endif
}

int FLProgWiFiClient::peek()
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.peek();
#else
    return 0;
#endif
}

void FLProgWiFiClient::flush()
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    client.flush();
#endif
}

void FLProgWiFiClient::stop()
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    client.stop();

#endif
}

#ifdef ARDUINO_ARCH_ESP8266
IPAddress FLProgWiFiClient::remoteIP()
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.remoteIP();
#else
    return IPAddress(0, 0, 0, 0);
#endif
}

uint16_t FLProgWiFiClient::remotePort()
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.remotePort();
#else
    return 0;
#endif
}

IPAddress FLProgWiFiClient::localIP()
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.localIP();
#else
    return IPAddress(0, 0, 0, 0);
#endif
}

uint16_t FLProgWiFiClient::localPort()
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.localPort();
#else
    return 0;
#endif
}
#else
IPAddress FLProgWiFiClient::remoteIP() const
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.remoteIP();
#else
    return IPAddress(0, 0, 0, 0);
#endif
}

IPAddress FLProgWiFiClient::remoteIP(int fd) const
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.remoteIP(fd);
#else
    return IPAddress(0, 0, 0, 0);
#endif
}

uint16_t FLProgWiFiClient::remotePort() const
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.remotePort();
#else
    return 0;
#endif
}

uint16_t FLProgWiFiClient::remotePort(int fd) const
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.remotePort(fd);
#else
    return 0;
#endif
}

IPAddress FLProgWiFiClient::localIP() const
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.localIP();
#else
    return IPAddress(0, 0, 0, 0);
#endif
}

IPAddress FLProgWiFiClient::localIP(int fd) const
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.localIP(fd);
#else
    return IPAddress(0, 0, 0, 0);
#endif
}

uint16_t FLProgWiFiClient::localPort() const
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.localPort();
#else
    return 0;
#endif
}

uint16_t FLProgWiFiClient::localPort(int fd) const
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    return client.localPort(fd);
#else
    return 0;
#endif
}

#endif

//----------------------------------FlprogEthernetServer-----------------
FlprogWiFiServer::FlprogWiFiServer(FLProgAbstracttWiFiInterface *sourse, int _port)
{
    port = _port;
#ifdef FLPROG_WIFI_TCP_DEVICE
    server = new WiFiServer(port);
#endif
    interface = sourse;
}

FLProgWiFiClient FlprogWiFiServer::accept()
{
#ifdef FLPROG_WIFI_TCP_DEVICE
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
#endif
    return FLProgWiFiClient();
}

void FlprogWiFiServer::begin(uint16_t port, int reuse_enable)
{
    (void)port;
    (void)reuse_enable;
}

void FlprogWiFiServer::setNoDelay(bool nodelay)
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    if (serverIsBegin)
    {
        server->setNoDelay(nodelay);
    }
#else
    (void)nodelay;
#endif
}

bool FlprogWiFiServer::getNoDelay()
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    if (serverIsBegin)
    {
        return server->getNoDelay();
    }
#endif
    return false;
}

bool FlprogWiFiServer::hasClient()
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    if (serverIsBegin)
    {
        return server->hasClient();
    }
#endif
    return false;
}
#ifndef ARDUINO_ARCH_ESP8266
size_t FlprogWiFiServer::write(const uint8_t *data, size_t len)
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    if (serverIsBegin)
    {
        return server->write(data, len);
    }
#else
    (void)data;
    (void)len;
#endif
    return 0;
}

size_t FlprogWiFiServer::write(uint8_t data)
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    if (serverIsBegin)
    {
        return server->write(data);
    }
#else
    (void)data;
#endif
    return 0;
}
#endif
void FlprogWiFiServer::end()
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    if (serverIsBegin)
    {
#ifdef ARDUINO_ARCH_ESP8266
        server->stop();
#else
        server->end();
#endif
    }
#endif
}

void FlprogWiFiServer::close()
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    if (serverIsBegin)
    {
        server->close();
    }
#endif
}

void FlprogWiFiServer::stop()
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    if (serverIsBegin)
    {
        server->stop();
    }
#endif
}

bool FlprogWiFiServer::listening()
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    if (serverIsBegin)
    {
        if (server)
        {
            return true;
        }
    }
#endif
    return false;
}
#ifndef ARDUINO_ARCH_ESP8266
int FlprogWiFiServer::setTimeout(uint32_t seconds)
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    if (serverIsBegin)
    {
        return server->setTimeout(seconds);
    }
#else
    (void)seconds;
#endif
    return 0;
}

void FlprogWiFiServer::stopAll()
{
#ifdef FLPROG_WIFI_TCP_DEVICE
    if (serverIsBegin)
    {
        server->stopAll();
    }
#endif
}
#endif
