#include "display.h"

DisplayPage::DisplayPage()
{
}

void DisplayPage::PreContent(std::stringstream& ss)
{
}

void DisplayPage::HeaderContent(std::stringstream& ss)
{
}

void DisplayPage::Page(std::stringstream& ss)
{
    ss << "<h1>Passwords</h1>" << std::endl;
}
