#pragma once

#include "page.h"
#include "client.h"
#include "conf.h"

#include <string>

#include "pistache/http.h"

class LoginPage : public IPage
{
public:
    LoginPage(const Net::Http::Request& request);

    virtual void PreContent(std::stringstream& ss) override;
    virtual void HeaderContent(std::stringstream& ss) override;
    virtual void Page(std::stringstream& ss) override;

private:
    bool DoLogin();

private:
    conf m_Conf;
    PasswordManagerClient m_Client;

    bool        m_Authenticated;
    bool        m_Need2fa;
    std::string m_Username;
    std::string m_Password;
    std::string m_Token;
};
