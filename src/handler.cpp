#include "handler.h"
#include <sstream>

#include "pages/display.h"
#include "pages/filenotfound.h"
#include "pages/index.h"
#include "pages/login.h"

void HelloHandler::Init(Net::Http::Endpoint& endpoint)
{
    Net::Rest::Routes::Get(m_Router, "/login", Net::Rest::Routes::bind(&HelloHandler::onLogin, this));

    endpoint.setHandler(m_Router.handler());
}

void HelloHandler::onRequest(const Net::Http::Request& request, Net::Http::ResponseWriter response)
{
    response.headers().add<Net::Http::Header::ContentType>(MIME(Text, Html));

    std::string action;
    if(request.query().has("action"))
    {
        action = request.query().get("action").get();
    }

    if(action.empty() && request.resource() == "/")
    {
        action = "index";
    }

    IPage* page = nullptr;
    if(action == "login")
    {
        page = new LoginPage(request, response);
    }
    else if(action == "index")
    {
        page = new IndexPage();
    }
    else if(action == "display")
    {
        page = new DisplayPage();
    }
    else if(request.resource().find('.') != std::string::npos)
    {
        std::string resolvedResource = "static/" + request.resource();
        Net::Http::serveFile(response, resolvedResource.c_str()).then([](ssize_t bytes) {;
        }, Async::NoExcept);
        return;
    }
    else
    {
        page = new FileNotFoundPage();
    }

    std::stringstream ss;
    ss << "<html>" << std::endl;
    ss << "<head>" << std::endl;
    ss << "<title>Soteria Pass</title>" << std::endl;
    page->HeaderContent(ss);
    ss << "</head>" << std::endl;
    ss << "<body>" << std::endl;
    page->Page(ss);
    ss << "</body>" << std::endl;
    ss << "</html>" << std::endl;

    delete page;
    page = nullptr;

    response.send(Net::Http::Code::Ok, ss.str());
}

void HelloHandler::onLogin(const Net::Rest::Request& request, Net::Http::ResponseWriter response)
{
    std::cout << "onLogin" << std::endl;
    response.headers().add<Net::Http::Header::ContentType>(MIME(Text, Html));

    std::stringstream ss;
/*    ss << "<html>" << std::endl;
    ss << "<head>" << std::endl;
    ss << "<title>Soteria Pass</title>" << std::endl;
    page.HeaderContent(ss);
    ss << "</head>" << std::endl;
    ss << "<body>" << std::endl;
    page.Page(ss);
    ss << "</body>" << std::endl;
    ss << "</html>" << std::endl;
*/
    response.send(Net::Http::Code::Ok, ss.str());
}
