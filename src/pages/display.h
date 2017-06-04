#pragma once

#include "page.h"
#include "client.h"
#include "conf.h"

#include <string>

class DisplayPage : public IPage
{
public:
    DisplayPage();

    virtual void PreContent(std::stringstream& ss) override;
    virtual void HeaderContent(std::stringstream& ss) override;
    virtual void Page(std::stringstream& ss) override;
};
