#include "utilities.h"
#include <vector>
#include <string>
#include <sstream>

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
    while(start_pos != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos = str.find(from);
    };
    return true;
}

std::string unescape_text(const std::string& str)
{
    std::string dst = str;
    replace(dst, "%20", " ");
    replace(dst, "%21", "!");
    replace(dst, "%22", "\"");
    replace(dst, "%23", "#");
    replace(dst, "%24", "$");
    replace(dst, "%25", "%");
    replace(dst, "%26", "&");
    replace(dst, "%27", "\'");
    replace(dst, "%28", "(");
    replace(dst, "%29", ")");
    replace(dst, "%2A", "*");
    replace(dst, "%2B", "+");
    replace(dst, "%2C", ",");
    replace(dst, "%2D", "-");
    replace(dst, "%2E", ".");
    replace(dst, "%2F", "/");
    replace(dst, "%3A", ":");
    replace(dst, "%3B", ";");
    replace(dst, "%3C", "<");
    replace(dst, "%3D", "=");
    replace(dst, "%3E", ">");
    replace(dst, "%3F", "?");
    replace(dst, "%40", "@");
    return dst;
}
