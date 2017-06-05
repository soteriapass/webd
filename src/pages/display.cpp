#include "display.h"
#include "utilities.h"

DisplayPage::DisplayPage(const Net::Http::Request& request, Net::Http::ResponseWriter& response)
: super(request, response)
{
}

void DisplayPage::PreContentImpl(std::stringstream& ss)
{
}

void DisplayPage::HeaderContentImpl(std::stringstream& ss)
{
    if(!GetIsAuthenticated())
    {
        ss << "<meta http-equiv=\"refresh\" content=\"2; URL=" << GetConf().get_base_server_path() << "/?action=login\">" << std::endl;
    }
    ss << "\t<script src=\"js/display.js\"></script>" << std::endl;
}

void DisplayPage::PageImpl(std::stringstream& ss)
{
    if(!GetIsAuthenticated())
    {
        return;
    }

    std::string bodyContent = ReadTemplate("display_body_general.html");

    std::stringstream ps;

    unsigned int index = 0;
    for(auto entry : GetClient().ListPasswords())
    {
        std::string entryContent = ReadTemplate("display_body_password_entry.html");

        replace(entryContent, "$ACCOUNT_NAME", entry.account_name());
        replace(entryContent, "$USERNAME", entry.username());
        replace(entryContent, "$PASSWORD", entry.password());
        replace(entryContent, "$EXTRA", entry.extra());

        std::stringstream intString;
        intString << index;
        replace(entryContent, "$INDEX", intString.str());

        ps << entryContent << std::endl;
        ++index;
    }
    replace(bodyContent, "$PASSWORD_ENTRIES", ps.str());
    ss << bodyContent;
}
