#include "login.h"
#include "utilities.h"

LoginPage::LoginPage(const Net::Http::Request& request, Net::Http::ResponseWriter& response)
: super(request, response)
, m_Need2fa(false)
{
    if(request.method() == Net::Http::Method::Post)
    {
        auto splitStrings = split_string(request.body(), '&');
        for(const std::string& splitString : splitStrings)
        {
            auto querySplit = split_string(splitString, '=');
            if(querySplit[0] == "username")
            {
                m_Username = querySplit[1];
            }
            else if(querySplit[0] == "password")
            {
                m_Password = unescape_text(querySplit[1]);
            }
            else if(querySplit[0] == "token")
            {
                m_Token = querySplit[1];
            }
        }
    }
    
    if(!GetIsAuthenticated())
    {
        DoLogin();
    }
}

void LoginPage::PreContent(std::stringstream& ss)
{
    if(GetIsAuthenticated())
    {
//        ss << "Set-Cookie:Token=" << GetClient().GetAuthToken() << ";" << std::endl;
    }
}

void LoginPage::HeaderContent(std::stringstream& ss)
{
    if(GetIsAuthenticated())
    {
        ss << "<meta http-equiv=\"refresh\" content=\"2; URL=" << GetConf().get_base_server_path() << "/?action=display\">" << std::endl;
    }
}

void LoginPage::Page(std::stringstream& ss)
{
    if(!m_Username.empty() && !m_Password.empty())
    {
        bool need2fa = false;
        std::string token;
    }

    if(!GetIsAuthenticated())
    {
        ss << "<h1>Login</h1>" << std::endl;
        if(!GetClient().GetLastError().empty())
        {
            ss << "<font color=\"red\">" << GetClient().GetLastError() << "</font><br/>" << std::endl;
        }
        ss << "<form method=\"post\" action=\"" << GetConf().get_base_server_path() << "/?action=login\">" << std::endl;
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
    else
    {
        ss << "<h1>Authenticated succeeded</h1>" << std::endl;
        ss << "If your browser doesn't automatically redirect you, please click <a href=\"/?action=display\">here</a>." << std::endl;
    }
}

bool LoginPage::DoLogin()
{
    if(m_Username.empty() || m_Password.empty())
    {
        SetIsAuthenticated(false);
        return false;
    }

    SetIsAuthenticated(GetClient().Authenticate(m_Username, m_Password, m_Token, m_Need2fa, false));
    return GetIsAuthenticated();
}

