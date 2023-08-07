#pragma once
#include "flprogUtilites.h"

class FLProgAbstractWiFi
{
public:
    void setApSsid(char *_apSsid) { apSsid = _apSsid; };
    void setApPassword(char *_apPassword) { apPassword = _apPassword; };
    void setClientSsidd(char *_clientSsid) { clientSsid = _clientSsid; };
    void setClientPassword(char *_clientPassword) { clientPassword = _clientPassword; };

protected:
    char *apSsid = 0;
    char *apPassword = 0;
    char *clientSsid = 0;
    char *clientPassword = 0;
};
