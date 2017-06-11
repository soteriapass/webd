#include "authenticatedpage.h"
#include "log.h"

AuthenticatedPage::AuthenticatedPage(const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
: m_Conf("/etc/pswmgr/pswmgr.conf")
, m_Client(m_Conf, PasswordManagerClient::GetChannel(m_Conf, m_Conf.get_authentication_address_and_port()))
{
    m_Authenticated = HandleCookie(request, response, m_Client);

    if(m_Authenticated)
    {
       SetupCookie(request, response, m_Client.GetAuthToken()); 
    }
}

bool AuthenticatedPage::HandleCookie(const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, PasswordManagerClient& client)
{
    Poco::Net::NameValueCollection cookies;
    request.getCookies(cookies);
    if(cookies.has("token"))
    {
        const std::string& token = cookies.get("token");
        if(client.ValidateToken(token))
        {
            client.SetAuthToken(token);
 
            bool need2fa;
            client.Authenticate("", "", "", need2fa, false);
            return true;
        }
    }
    return false;
}

void AuthenticatedPage::SetupCookie(const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, std::string token)
{
    Poco::Net::HTTPCookie cookie("token", token);
    response.addCookie(cookie);
}
