#include "parser.h"
#include <iostream>
#include <fstream>

void Parser::Parse(const std::string& filename, std::stringstream& ss)
{
    std::ifstream file(filename, std::ifstream::in);
    std::string fileContents = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()); 
    int lastPos = 0;
    int startPos = fileContents.find('$', lastPos);
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

        startPos = fileContents.find('$', lastPos + 2);
    };

    if(lastPos != fileContents.size())
    {
        ss << fileContents.substr(lastPos);
    }
}

void Parser::Require(const std::string& filename, std::stringstream& ss)
{
    std::ifstream file("static/" + filename, std::ifstream::in);
    std::string fileContents = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    ss << fileContents;
}
