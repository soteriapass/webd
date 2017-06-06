#pragma once

#include <string>
#include <map>

class HttpQuery
{
public:
    HttpQuery(const std::string& uri);

    bool has(const std::string& str) const;
    std::string get(const std::string& str) const;

private:
    std::map<std::string, std::string> m_Queries;
};
