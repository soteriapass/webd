#pragma once

#include <fstream>
#include <sstream>

class IPage
{
public:
    virtual void PreContent(std::stringstream& ss)=0;
    virtual void HeaderContent(std::stringstream& ss)=0;
    virtual void Page(std::stringstream& ss)=0;

    std::string ReadTemplate(const std::string& templateName)
    {
        std::ifstream file("static/templates/" + templateName, std::ifstream::in);
        return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    }
};

