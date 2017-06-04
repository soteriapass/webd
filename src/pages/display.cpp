#include "display.h"

DisplayPage::DisplayPage(const Net::Http::Request& request, Net::Http::ResponseWriter& response)
: super(request, response)
{
}

void DisplayPage::PreContent(std::stringstream& ss)
{
}

void DisplayPage::HeaderContent(std::stringstream& ss)
{
    if(!GetIsAuthenticated())
    {
        ss << "<meta http-equiv=\"refresh\" content=\"2; URL=" << GetConf().get_base_server_path() << "/?action=login\">" << std::endl;
    }
    ss << "\t<script src=\"js/display.js\"></script>" << std::endl;
}

void DisplayPage::Page(std::stringstream& ss)
{
    if(!GetIsAuthenticated())
    {
        return;
    }

    ss << "\t<h1>Passwords</h1>" << std::endl;
    ss << "\t<table>" << std::endl;
    ss << "\t\t<tr>" << std::endl;
    ss << "\t\t\t<th>Account Name</th>" << std::endl;
    ss << "\t\t\t<th>Username</th>" << std::endl;
    ss << "\t\t\t<th>Password</th>" << std::endl;
    ss << "\t\t\t<th></th>" << std::endl;
    ss << "\t\t\t<th>Extra</th>" << std::endl;
    ss << "\t\t</tr>" << std::endl;

    unsigned int index = 0;
    for(auto entry : GetClient().ListPasswords())
    {
        ss << "\t\t<tr>" << std::endl;
        ss << "\t\t\t<td>" << entry.account_name() << "</td>" << std::endl;
        ss << "\t\t\t<td>" << entry.username() << "</td>" << std::endl;
        ss << "\t\t\t<form>" << std::endl;
        ss << "\t\t\t\t<td><input type=\"password\" placeholder=\"Password\" id=\"pwd" << index << "\" class=\"masked\" name=\"password\" value=\"" << entry.password() << "\"/></td>" << std::endl;
        ss << "\t\t\t\t<td><a href=\"#\" onclick=\"toggle_password('pwd" << index << "', 'showhide" << index << "');\" id=\"showhide" << index << "\">Show</a>" << std::endl;
        ss << "\t\t\t</form>" << std::endl;
        ss << "\t\t\t<td>" << entry.extra() << "</td>" << std::endl;
        ss << "\t\t</tr>" << std::endl;
        ++index;
    }
    ss << "\t</table>" << std::endl;
}
