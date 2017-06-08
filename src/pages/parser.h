#pragma once

#include <string>
#include <sstream>
#include <functional>
#include <map>

class Parser
{
public:
    void Parse(const std::string& filename, std::stringstream& ss);
    void RegisterParser(const std::string& name, std::function<void(const std::string&, std::stringstream&)> func);

private:
    void Require(const std::string& filename, std::stringstream& ss);

private:
    std::map<std::string, std::function<void(const std::string&, std::stringstream&)>> m_RegParsers;
};
