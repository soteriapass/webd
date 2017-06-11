#include "authenticatedpage.h"
#include "log.h"

AuthenticatedPage::AuthenticatedPage(const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
: m_Conf("/etc/pswmgr/pswmgr.conf")
, m_Client(m_Conf, PasswordManagerClient::GetChannel(m_Conf, m_Conf.get_authentication_address_and_port()))
{
    m_Authenticated = HandleCookie(request, response, m_Client, m_TokenUsername);

    if(m_Authenticated)
    {
       SetupCookie(request, response, m_Client.GetAuthToken()); 
    }
}

bool AuthenticatedPage::HandleCookie(const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, PasswordManagerClient& client)
{
    std::string tokenUsername;
    return HandleCookie(request, response, client, tokenUsername);
}

bool AuthenticatedPage::HandleCookie(const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, PasswordManagerClient& client, std::string& tokenUsername)
{
    Poco::Net::NameValueCollection cookies;
    request.getCookies(cookies);
    if(cookies.has("token"))
    {
        const std::string& token = cookies.get("token");
        if(client.ValidateToken(token, tokenUsername))
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

void AuthenticatedPage::ReplaceUsername(const std::string&, std::stringstream& ss)
{
    ss << m_TokenUsername;
}

void AuthenticatedPage::RegisterParsers(Parser& parser) 
{ 
    auto func = [&](const std::string& p1, std::stringstream& ss)
    {
        ReplaceUsername(p1, ss);
    };
    parser.RegisterParser("username", func);
}
