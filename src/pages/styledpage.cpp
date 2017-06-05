#include "styledpage.h"
#include "utilities.h"

#include <iostream>

void StyledPage::PreContent(std::stringstream& ss)
{
    PreContentImpl(ss);
}

void StyledPage::HeaderContent(std::stringstream& ss)
{
    ss << ReadTemplate("header.html");
    HeaderContentImpl(ss);
}

void StyledPage::Page(std::stringstream& ss)
{
    ss << ReadTemplate("body_start.html");
    std::string content = ReadTemplate("content.html");

    std::stringstream contentStringStream;
    PageImpl(contentStringStream);

    replace(content, "$BREADCRUMB", "");
    replace(content, "$CONTENT", contentStringStream.str());

    ss << content << std::endl;

    ss << ReadTemplate("body_end.html");
    ss << ReadTemplate("scripts.html");
}
