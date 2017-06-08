#pragma once

#include <fstream>
#include <sstream>
#include "parser.h"

class IPage
{
public:
    virtual void PreContent(std::stringstream& ss)=0;
    virtual void HeaderContent(std::stringstream& ss)=0;
    virtual void Page(std::stringstream& ss)=0;
    virtual void RegisterParsers(Parser& parser) { }

    std::string ReadTemplate(const std::string& templateName)
    {
        std::ifstream file("static/templates/" + templateName, std::ifstream::in);
        return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    }
};

