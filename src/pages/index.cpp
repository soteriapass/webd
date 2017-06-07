#include "index.h"

IndexPage::IndexPage()
{
}

void IndexPage::PreContent(std::stringstream& ss)
{
    ss << "<!DOCTYPE html>" << std::endl;
    ss << "<html>" << std::endl;
}

void IndexPage::HeaderContent(std::stringstream& ss)
{
    ss << "<head>" << std::endl;
    ss << "<title>Soteria Pass</title>" << std::endl;
    ss << "</head>" << std::endl;
}

void IndexPage::Page(std::stringstream& ss)
{
    ss << "<body class=\"hold-transition skin-blue sidebar-mini\">" << std::endl;
    ss << "<h1>Hello World</h1>" << std::endl;
    ss << "</body>" << std::endl;
    ss << "</html>" << std::endl;
}
