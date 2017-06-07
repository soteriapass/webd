#pragma once

#include "page.h"
#include "client.h"
#include "conf.h"

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

class AuthenticatedPage : public IPage
{
public:
    AuthenticatedPage(const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

protected:
    bool GetIsAuthenticated() const             { return m_Authenticated; }
    void SetIsAuthenticated(bool authenticated) { m_Authenticated = authenticated; }

    PasswordManagerClient& GetClient() { return m_Client; }
    conf& GetConf() { return m_Conf; }

    static bool HandleCookie(const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, PasswordManagerClient& client);
    static void SetupCookie(const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, std::string token);
private:
    bool m_Authenticated;

    conf m_Conf;
    PasswordManagerClient m_Client;
};
