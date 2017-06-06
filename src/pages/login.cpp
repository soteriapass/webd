#include "login.h"
#include "log.h"
#include "utilities.h"

#include <Poco/Net/HTMLForm.h>

LoginPage::LoginPage(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
: super(request, response)
, m_Need2fa(false)
{
    if(request.getMethod() == "POST")
    {
        Poco::Net::HTMLForm form(request, request.stream());

        for(auto iter : form)
        {
            if(iter.first == "username")
            {
                m_Username = iter.second;
            }
            else if(iter.first == "password")
            {
                m_Password = iter.second;
            }
            else if(iter.first == "token")
            {
                m_Token = iter.second;
            }
        }
    }
    
    if(!GetIsAuthenticated())
    {
        if(DoLogin())
        {
            SetupCookie(request, response, GetClient().GetAuthToken());
        }
    }
}

void LoginPage::PreContentImpl(std::stringstream& ss)
{
    if(GetIsAuthenticated())
    {
//        ss << "Set-Cookie:Token=" << GetClient().GetAuthToken() << ";" << std::endl;
    }
}

void LoginPage::HeaderContentImpl(std::stringstream& ss)
{
    if(GetIsAuthenticated())
    {
        std::string content = ReadTemplate("login_header_forward.html");
        replace(content, "$BASE_URL", GetConf().get_base_server_path());
        ss << content;
    }
}

void LoginPage::PageImpl(std::stringstream& ss)
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
            logging::get() << "grpc: " << GetClient().GetLastError() << std::endl;
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

