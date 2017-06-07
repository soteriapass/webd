#pragma once

#include <string>
#include <sstream>

class Parser
{
public:
    void Parse(const std::string& filename, std::stringstream& ss);

private:
    void Require(const std::string& filename, std::stringstream& ss);
};
