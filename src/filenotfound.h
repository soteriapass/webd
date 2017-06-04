#pragma once

#include "page.h"
#include "client.h"
#include "conf.h"

#include <string>

class FileNotFoundPage : public IPage
{
public:
    FileNotFoundPage();

    virtual void PreContent(std::stringstream& ss) override;
    virtual void HeaderContent(std::stringstream& ss) override;
    virtual void Page(std::stringstream& ss) override;

private:
    conf m_Conf;
};

