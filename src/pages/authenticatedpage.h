#pragma once

#include "page.h"
#include "styledpage.h"
#include "client.h"
#include "conf.h"

#include "pistache/http.h"

class AuthenticatedPage : public StyledPage
{
public:
    AuthenticatedPage(const Net::Http::Request& request, Net::Http::ResponseWriter& response);

protected:
    bool GetIsAuthenticated() const             { return m_Authenticated; }
    void SetIsAuthenticated(bool authenticated) { m_Authenticated = authenticated; }

    PasswordManagerClient& GetClient() { return m_Client; }
    conf& GetConf() { return m_Conf; }

    static bool HandleCookie(const Net::Http::Request& request, Net::Http::ResponseWriter& response, PasswordManagerClient& client);
private:
    bool m_Authenticated;

    conf m_Conf;
    PasswordManagerClient m_Client;
};
