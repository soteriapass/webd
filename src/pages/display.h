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
    DisplayPage(const Net::Http::Request& request, Net::Http::ResponseWriter& response);

    virtual void PreContent(std::stringstream& ss) override;
    virtual void HeaderContent(std::stringstream& ss) override;
    virtual void Page(std::stringstream& ss) override;
};
