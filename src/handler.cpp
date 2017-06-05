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
    std::cout << "request: " << request.resource() << std::endl;

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
        page = new DisplayPage(request, response);
    }
    else if(request.resource().find('.') != std::string::npos)
    {
        std::string resolvedResource = "static/" + request.resource();
        Net::Http::serveFile(response, resolvedResource.c_str());
        return;
    }
    else
    {
        page = new FileNotFoundPage();
    }

    response.headers().add<Net::Http::Header::ContentType>(MIME(Text, Html));

    std::stringstream ss;
    ss << "<!DOCTYPE html>" << std::endl;
    ss << "<html>" << std::endl;
    ss << "<head>" << std::endl;
    ss << "<title>Soteria Pass</title>" << std::endl;
    page->HeaderContent(ss);
    ss << "</head>" << std::endl;
    ss << "<body class=\"hold-transition skin-blue sidebar-mini\">" << std::endl;
    page->Page(ss);
    ss << "</body>" << std::endl;
    ss << "</html>" << std::endl;

    delete page;
    page = nullptr;

    //This is the "proper" way to serve everything"
    /*
    std::string pageContents = ss.str();
    std::cout << "start to send response (size: " << pageContents.size() << ")" << std::endl;
    response.send(Net::Http::Code::Ok, pageContents);
    std::cout << "response sent for: " << request.resource() << std::endl;
    */

    //We do this as a hack, for now
    std::cout << "Creating file" << std::endl;
    std::ofstream file;
    file.open("temp.html");
    file << ss.str();
    file.close();
    Net::Http::serveFile(response, "temp.html");
    std::remove("temp.html");
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
