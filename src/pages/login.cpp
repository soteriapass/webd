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
        std::string content = ReadTemplate("login_header_forward.html");
        replace(content, "$BASE_URL", GetConf().get_base_server_path());
        ss << content;
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

        std::string content = ReadTemplate("login_body_form.html");
        replace(content, "$BASE_URL", GetConf().get_base_server_path());
        if(!m_Username.empty())
        {
            replace(content, "$USERNAME_FIELD", "value=\"" + m_Username + "\"");
        }
        else
        {
            replace(content, "$USERNAME_FIELD", "");
        }

        if(m_Need2fa)
        {
            std::string tfaContent = ReadTemplate("login_body_form_tfa.html");
            replace(content, "$TFA_AUTH", tfaContent);
        }
        else
        {
            replace(content, "$TFA_AUTH", "");
        }
        ss << content;
    }
    else
    {
        std::string content = ReadTemplate("login_body_forward.html");
        replace(content, "$BASE_URL", GetConf().get_base_server_path());
        ss << content;
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

