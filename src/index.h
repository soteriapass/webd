#pragma once

#include "page.h"
#include "client.h"
#include "conf.h"

#include <string>

class IndexPage : public IPage
{
public:
    IndexPage();

    virtual void PreContent(std::stringstream& ss) override;
    virtual void HeaderContent(std::stringstream& ss) override;
    virtual void Page(std::stringstream& ss) override;
};
