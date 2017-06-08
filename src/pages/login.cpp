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

