#include "httpquery.h"

#include "utilities.h"

HttpQuery::HttpQuery(const std::string& uri)
{
    int index = uri.find('?');
    if(index != std::string::npos)
    {
        auto queryString = uri.substr(index+1);
        auto queryPairs = split_string(queryString, '&');
        for(const std::string& splitString : queryPairs)
        {
            auto querySplit = split_string(splitString, '=');
            m_Queries[querySplit[0]] = querySplit[1];
        }
    }
}

bool HttpQuery::has(const std::string& str) const
{
    return m_Queries.find(str) != m_Queries.end();
}

std::string HttpQuery::get(const std::string& str) const
{
    if(!has(str))
        return {};

    return m_Queries.find(str)->second;
}
