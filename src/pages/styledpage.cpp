#include "styledpage.h"
#include "utilities.h"

#include <iostream>

void StyledPage::PreContent(std::stringstream& ss)
{
    PreContentImpl(ss);
}

void StyledPage::HeaderContent(std::stringstream& ss)
{
    std::cout << "HeaderContent" << std::endl;
    ss << ReadTemplate("header.html");
    HeaderContentImpl(ss);
    std::cout << "HeaderContent End" << std::endl;
}

void StyledPage::Page(std::stringstream& ss)
{
    std::cout << "Page" << std::endl;

    ss << ReadTemplate("body_start.html");
    std::string content = ReadTemplate("content.html");

    std::stringstream contentStringStream;
    PageImpl(contentStringStream);

    replace(content, "$BREADCRUMB", "");
    replace(content, "$CONTENT", contentStringStream.str());

    ss << content << std::endl;

    ss << ReadTemplate("body_end.html");
    ss << ReadTemplate("scripts.html");

    std::cout << "Page End" << std::endl;
}
