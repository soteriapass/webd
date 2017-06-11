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
                m_Need2fa = true;
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
}

void LoginPage::RegisterParsers(Parser& parser)
{
    auto func = [&](const std::string& p1, std::stringstream& ss)
    {
        ShowErrorMessage(p1, ss);
    };
    parser.RegisterParser("error_msg", func);

    auto func2 = [&](const std::string& p1, std::stringstream& ss)
    {
        ShowStatusMessage(p1, ss);
    };
    parser.RegisterParser("status_msg", func2);

    auto func3 = [&](const std::string& p1, std::stringstream& ss)
    {
        ShowFormUsername(p1, ss);
    };
    parser.RegisterParser("form_username", func3);

    auto func4 = [&](const std::string& p1, std::stringstream& ss)
    {
        ShowFormPassword(p1, ss);
    };
    parser.RegisterParser("form_password", func4);

    auto func5 = [&](const std::string& p1, std::stringstream& ss)
    {
        AddTwoFactorAuthFromElem(p1, ss);
    };
    parser.RegisterParser("two_factor_auth_form", func5);
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

void LoginPage::ShowErrorMessage(const std::string&, std::stringstream& ss)
{
    if(!GetClient().GetLastError().empty())
    {
        ss << "<p class=\"login-box-msg\"><font color=\"red\">" << GetClient().GetLastError() << "</font></p>" << std::endl;
    }
}

void LoginPage::ShowStatusMessage(const std::string&, std::stringstream& ss)
{
    if(m_Need2fa)
    {
        ss << "<p class=\"login-box-msg\">Two Factor Authentication Required</p>" << std::endl;
    }
}

void LoginPage::ShowFormUsername(const std::string&, std::stringstream& ss)
{
    if(!m_Username.empty())
    {
        ss << "value=\"" << m_Username << "\"";
    }
}

void LoginPage::ShowFormPassword(const std::string&, std::stringstream& ss)
{
    if(!m_Password.empty())
    {
        ss << "value=\"" << m_Password << "\"";
    }
}

void LoginPage::AddTwoFactorAuthFromElem(const std::string&, std::stringstream& ss)
{
    if(m_Need2fa && !GetIsAuthenticated())
    {
        ss << "      <div class=\"form-group has-feedback\">" << std::endl;
        ss << "      <input type=\"text\" name=\"token\" class=\"form-control\" placeholder=\"Two Factor Auth\">" << std::endl;
        ss << "      </div>" << std::endl;
    }
}
