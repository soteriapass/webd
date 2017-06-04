#include "filenotfound.h"

FileNotFoundPage::FileNotFoundPage()
{
}

void FileNotFoundPage::PreContent(std::stringstream& ss)
{
}

void FileNotFoundPage::HeaderContent(std::stringstream& ss)
{
    ss << "<meta http-equiv=\"refresh\" content=\"0; URL=" << m_Conf.get_base_server_path() << "/404.html\">" << std::endl;
}

void FileNotFoundPage::Page(std::stringstream& ss)
{
}
