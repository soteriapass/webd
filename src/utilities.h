#pragma once

#include <string>
#include <vector>

#include "httpquery.h"

std::vector<std::string> split_string(std::string str, char character);
bool replace(std::string& str, const std::string& from, const std::string& to); 
std::string unescape_text(const std::string& str);
HttpQuery getQuery(const std::string& str);
