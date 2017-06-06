#include "index.h"

IndexPage::IndexPage()
{
}

void IndexPage::PreContent(std::stringstream& ss)
{
}

void IndexPage::HeaderContent(std::stringstream& ss)
{
}

void IndexPage::Page(std::stringstream& ss)
{
    ss << "<h1>Hello World</h1>" << std::endl;
}
