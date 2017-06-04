#pragma once

#include "page.h"
#include "authenticatedpage.h"

#include "client.h"
#include "conf.h"

#include <string>

#include "pistache/http.h"

class LoginPage : public AuthenticatedPage
{
    typedef AuthenticatedPage super;
public:
    LoginPage(const Net::Http::Request& request, Net::Http::ResponseWriter& response);

    virtual void PreContent(std::stringstream& ss) override;
    virtual void HeaderContent(std::stringstream& ss) override;
    virtual void Page(std::stringstream& ss) override;

private:
    bool DoLogin();

private:
    bool        m_Need2fa;
    std::string m_Username;
    std::string m_Password;
    std::string m_Token;
};
