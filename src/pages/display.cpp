#include "display.h"
#include "log.h"
#include "utilities.h"

DisplayPage::DisplayPage(const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
: super(request, response)
{
}

void DisplayPage::PreContent(std::stringstream& ss)
{
}

void DisplayPage::HeaderContent(std::stringstream& ss)
{
/*
    if(!GetIsAuthenticated())
    {
        logging::get() << "\tRedirecting to login page" << std::endl;
        ss << "<meta http-equiv=\"refresh\" content=\"2; URL=" << GetConf().get_base_server_path() << "/?action=login\">" << std::endl;
    }
    ss << "\t<script src=\"js/display.js\"></script>" << std::endl;
*/
}

void DisplayPage::Page(std::stringstream& ss)
{
    if(!GetIsAuthenticated())
    {
        return;
    }
}

void DisplayPage::RegisterParsers(Parser& parser)
{
    super::RegisterParsers(parser);
    auto func = [&](const std::string& p1, std::stringstream& ss)
    {
        DisplayPasswords(p1, ss);
    };
    parser.RegisterParser("display_passwords", func);

    auto func2 = [&](const std::string& p1, std::stringstream& ss)
    {
        FillHeader(p1, ss);
    };
    parser.RegisterParser("header", func2);

    auto func3 = [&](const std::string& p1, std::stringstream& ss)
    {
        AddActiveTag(p1, ss);
    };
    parser.RegisterParser("is_active", func3);
}

void DisplayPage::DisplayPasswords(const std::string&, std::stringstream& ss)
{
    if(!GetIsAuthenticated())
    {
        return;
    }

    std::stringstream ps;

    unsigned int index = 0;
    auto passwords = GetClient().ListPasswords();
    for(auto entry : passwords)
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
    ss << ps.str();
}

void DisplayPage::FillHeader(const std::string&, std::stringstream& ss)
{
    if(!GetIsAuthenticated())
    {
        logging::get() << "\tRedirecting to login page" << std::endl;
        ss << "<meta http-equiv=\"refresh\" content=\"2; URL=" << GetConf().get_base_server_path() << "/login.cshtml?action=login\">" << std::endl;
    }
    ss << "\t<script src=\"js/display.js\"></script>" << std::endl;
}

void DisplayPage:: AddActiveTag(const std::string& page, std::stringstream& ss)
{
    if(page == "display")
    {
        ss << " class=\"active\"";
    }
}
