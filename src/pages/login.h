#pragma once

#include "authenticatedpage.h"
#include "page.h"

#include "client.h"
#include "conf.h"

#include <string>

#include "pistache/http.h"

class LoginPage : public AuthenticatedPage
{
    typedef AuthenticatedPage super;
public:
    LoginPage(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

    virtual void PreContent(std::stringstream& ss) override;
    virtual void HeaderContent(std::stringstream& ss) override;
    virtual void Page(std::stringstream& ss) override;

    virtual void RegisterParsers(Parser& parser) override;
private:
    bool DoLogin();

    void ShowErrorMessage(const std::string&, std::stringstream& ss);
    void ShowStatusMessage(const std::string&, std::stringstream& ss);
    void ShowFormUsername(const std::string&, std::stringstream& ss);
    void ShowFormPassword(const std::string&, std::stringstream& ss);
    void AddTwoFactorAuthFromElem(const std::string&, std::stringstream& ss);
private:
    bool        m_Need2fa;
    std::string m_Username;
    std::string m_Password;
    std::string m_Token;
};
