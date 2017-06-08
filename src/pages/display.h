#pragma once

#include "page.h"
#include "authenticatedpage.h"

#include "client.h"
#include "conf.h"

#include <string>

class DisplayPage : public AuthenticatedPage
{
    typedef AuthenticatedPage super;
public:
    DisplayPage(const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

    virtual void PreContent(std::stringstream& ss) override;
    virtual void HeaderContent(std::stringstream& ss) override;
    virtual void Page(std::stringstream& ss) override;
    virtual void RegisterParsers(Parser& parser) override;

private:
    void DisplayPasswords(const std::string&, std::stringstream& ss);
};
