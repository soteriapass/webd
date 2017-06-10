#include "parser.h"
#include <iostream>
#include <fstream>

void Parser::Parse(const std::string& filename, std::stringstream& ss)
{
    std::ifstream file(filename, std::ifstream::in);
    std::string fileContents = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()); 
    int lastPos = 0;
    int startPos = fileContents.find('$', lastPos);
    const int firstStartPos = startPos;
    while(startPos != std::string::npos)
    {
        ss << fileContents.substr(lastPos, startPos - lastPos);

        lastPos = fileContents.find(';', startPos + 1) + 1;

        int paramStart = fileContents.find('(', startPos + 1);
        std::string function = fileContents.substr(startPos + 1, paramStart - startPos - 1);
        std::string param = fileContents.substr(paramStart + 2, lastPos - paramStart - 5);
        if(function == "require")
        {
            Require(param, ss);
        }
        else if(m_RegParsers.find(function) != m_RegParsers.end())
        {
            m_RegParsers[function](param, ss);
        }

        startPos = fileContents.find('$', lastPos + 2);
        if(startPos == firstStartPos)
        {
            break;
        }
    };

    if(lastPos != fileContents.size())
    {
        ss << fileContents.substr(lastPos);
    }
}

void Parser::RegisterParser(const std::string& name, std::function<void(const std::string&, std::stringstream&)> func)
{
    m_RegParsers[name] = func;
}

void Parser::Require(const std::string& filename, std::stringstream& ss)
{
    const std::string resolvedFilename = "static/" + filename;
    int extIndexStart = resolvedFilename.rfind('.');
    std::string ext = resolvedFilename.substr(extIndexStart + 1, extIndexStart - 1);
    if(ext == "cshtml")
    {
        Parse(resolvedFilename, ss);
    }
    else
    {
        std::ifstream file("static/" + filename, std::ifstream::in);
        std::string fileContents = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
        ss << fileContents;
    }
}
