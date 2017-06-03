#pragma once

#include <string>

std::vector<std::string> split_string(std::string str, char character)
{
    std::vector<std::string> strings;
    std::istringstream f(str);
    std::string s;
    while (getline(f, s, character))
    {
        strings.push_back(s);
    }
    return strings;
}

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

std::string unescape_text(const std::string& str)
{
    std::string dst = str;
    replace(dst, "%20", " ");
    replace(dst, "%21", "!");
    replace(dst, "%22",	"\"");
    replace(dst, "%23",	"#");
    replace(dst, "%24",	"$");
    replace(dst, "%25",	"%");
    replace(dst, "%26",	"&");
    replace(dst, "%27",	"\'");
    replace(dst, "%28",	"(");
    replace(dst, "%29",	")");
    replace(dst, "%2A",	"*");
    replace(dst, "%2B",	"+");
    replace(dst, "%2C",	",");
    replace(dst, "%2D",	"-");
    replace(dst, "%2E",	".");
    replace(dst, "%2F",	"/");
    return dst;
}
