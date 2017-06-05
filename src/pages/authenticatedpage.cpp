#include "authenticatedpage.h"

AuthenticatedPage::AuthenticatedPage(const Net::Http::Request& request, Net::Http::ResponseWriter& response)
: m_Conf("/etc/pswmgr/pswmgr.conf")
, m_Client(m_Conf, PasswordManagerClient::GetChannel(m_Conf, m_Conf.get_authentication_address_and_port()))
{
    m_Authenticated = HandleCookie(request, response, m_Client);

    if(m_Authenticated && !response.cookies().has("token"))
    {
        auto cookie = Net::Http::Cookie("token", m_Client.GetAuthToken());
        response.cookies().add(cookie);
    }
}

bool AuthenticatedPage::HandleCookie(const Net::Http::Request& request, Net::Http::ResponseWriter& response, PasswordManagerClient& client)
{
    if(request.cookies().has("token"))
    {
        client.SetAuthToken(request.cookies().get("token").value);
       
        bool need2fa;
        client.Authenticate("", "", "", need2fa, false);
        return true;
    }
    return false;
}
