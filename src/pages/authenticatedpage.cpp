#include "authenticatedpage.h"

AuthenticatedPage::AuthenticatedPage(const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
: m_Conf("/etc/pswmgr/pswmgr.conf")
, m_Client(m_Conf, PasswordManagerClient::GetChannel(m_Conf, m_Conf.get_authentication_address_and_port()))
{
    m_Authenticated = HandleCookie(request, response, m_Client);

    Poco::Net::NameValueCollection cookies;
    request.getCookies(cookies);
    if(m_Authenticated)
    {
        Poco::Net::HTTPCookie cookie("token", m_Client.GetAuthToken());
        response.addCookie(cookie);
    }
}

bool AuthenticatedPage::HandleCookie(const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, PasswordManagerClient& client)
{
    Poco::Net::NameValueCollection cookies;
    request.getCookies(cookies);
    if(cookies.has("token"))
    {
        client.SetAuthToken(cookies.get("token"));
 
        bool need2fa;
        return client.Authenticate("", "", "", need2fa, false);
    }
    return false;
}
