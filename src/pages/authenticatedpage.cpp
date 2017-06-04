#include "authenticatedpage.h"

AuthenticatedPage::AuthenticatedPage(const Net::Http::Request& request, Net::Http::ResponseWriter& response)
: m_Conf("/etc/pswmgr/pswmgr.conf")
, m_Client(m_Conf, PasswordManagerClient::GetChannel(m_Conf, m_Conf.get_authentication_address_and_port()))
{
    m_Authenticated = HandleCookie(request, response, m_Client);

    if(m_Authenticated && !response.cookies().has("token"))
    {
        std::cout << "Authenticated, added token (" << m_Client.GetAuthToken() << ") to cookie" << std::endl;
        auto cookie = Net::Http::Cookie("token", m_Client.GetAuthToken());
        response.cookies().add(cookie);
    }
}

void AuthenticatedPage::PreContent(std::stringstream& ss)
{
}

void AuthenticatedPage::HeaderContent(std::stringstream& ss)
{
}

void AuthenticatedPage::Page(std::stringstream& ss)
{
}

bool AuthenticatedPage::HandleCookie(const Net::Http::Request& request, Net::Http::ResponseWriter& response, PasswordManagerClient& client)
{
    if(request.cookies().has("token"))
    {
        std::cout << "cookie for token was present (" << request.cookies().get("token").value << ")" << std::endl;
        client.SetAuthToken(request.cookies().get("token").value);
        return true;
    }
    return false;
}
