#include "login.h"
#include "utilities.h"

LoginPage::LoginPage(const Net::Http::Request& request)
: m_Authenticated(false)
, m_Need2fa(false)
, m_Client(m_Conf, PasswordManagerClient::GetChannel(m_Conf, m_Conf.get_authentication_address_and_port()))
{
    if(request.method() == Net::Http::Method::Post)
    {
        std::cout << request.body() << std::endl;
        auto splitStrings = split_string(request.body(), '&');
        for(const std::string& splitString : splitStrings)
        {
            auto querySplit = split_string(splitString, '=');
            std::cout << querySplit[0] << ":" << querySplit[1] << std::endl;
            if(querySplit[0] == "username")
            {
                std::cout << "username set" << std::endl;
                m_Username = querySplit[1];
            }
            else if(querySplit[0] == "password")
            {
                std::cout << "password set" << std::endl;
                m_Password = unescape_text(querySplit[1]);
                std::cout << "Password: " << m_Password << std::endl;
            }
            else if(querySplit[0] == "token")
            {
                std::cout << "token set" << std::endl;
                m_Token = querySplit[1];
            }
        }
    }
    DoLogin();
}

LoginPage::LoginPage(const std::string& username, const std::string& password, const std::string& token)
: m_Authenticated(false)
, m_Need2fa(false)
, m_Client(m_Conf, PasswordManagerClient::GetChannel(m_Conf, m_Conf.get_authentication_address_and_port()))
, m_Username(username)
, m_Password(password)
, m_Token(token)
{
    DoLogin();
}

void LoginPage::PreContent(std::stringstream& ss)
{
    if(m_Authenticated)
    {
        ss << "Set-Cookie:Token=" << m_Client.GetAuthToken() << ";" << std::endl;
    }
}

void LoginPage::HeaderContent(std::stringstream& ss)
{
    if(m_Authenticated)
    {
        ss << "<meta http-equiv=\"refresh\" content=\"0; url=\"/?action=display\"/>" << std::endl;
    }
}

void LoginPage::Page(std::stringstream& ss)
{
    if(!m_Username.empty() && !m_Password.empty())
    {
        bool need2fa = false;
        std::string token;
    }

    ss << "<h1>Login</h1>" << std::endl;
    if(!m_Authenticated && !m_Client.GetLastError().empty())
    {
        ss << "<font color=\"red\">" << m_Client.GetLastError() << "</font><br/>" << std::endl;
    }
    ss << "<form method=\"post\" action=\"/?action=login\">" << std::endl;
    if(!m_Username.empty())
    {
        ss << "    Username: <input type=\"text\" name=\"username\" value=\"" << m_Username << "\">" << std::endl;
    }
    else
    {
        ss << "    Username: <input type=\"text\" name=\"username\">" << std::endl;
    }
    ss << "    <p>" << std::endl;
    ss << "    Password: <input type=\"password\" name=\"password\">" << std::endl;
    ss << "    <p>" << std::endl;
    if(m_Need2fa)
    {
        ss << "    2FA: <input type=\"text\" name=\"token\">" << std::endl;
        ss << "    <p>" << std::endl;
    }
    ss << "    <input type=\"submit\" value=\"Login\">" << std::endl;
    ss << "</form>" << std::endl;
}

bool LoginPage::DoLogin()
{
    if(m_Username.empty() || m_Password.empty())
    {
        m_Authenticated = false;
        return false;
    }

    m_Authenticated = m_Client.Authenticate(m_Username, m_Password, m_Token, m_Need2fa, false);
    if(!m_Authenticated)
    {
        std::cout << "Authentication failed (" << m_Username << ", " << m_Password << ")" << std::endl;
    }
    return m_Authenticated;
}

