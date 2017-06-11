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

    virtual void RegisterParsers(Parser& parser) override;

    static bool HandleCookie(const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, PasswordManagerClient& client);
    static bool HandleCookie(const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, PasswordManagerClient& client, std::string& username);
    static void SetupCookie(const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, std::string token);

private:
    void ReplaceUsername(const std::string&, std::stringstream& ss);
private:
    bool m_Authenticated;
    std::string m_TokenUsername;

    conf m_Conf;
    PasswordManagerClient m_Client;
};
