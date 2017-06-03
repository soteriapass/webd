#pragma once

#include <sstream>

class IPage
{
public:
    virtual void PreContent(std::stringstream& ss)=0;
    virtual void HeaderContent(std::stringstream& ss)=0;
    virtual void Page(std::stringstream& ss)=0;
};

