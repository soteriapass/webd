#include "handler.h"
#include <sstream>
#include <iostream>

#include "pages/display.h"
#include "pages/filenotfound.h"
#include "pages/index.h"
#include "pages/login.h"

#include "log.h"
#include "utilities.h"

void PswmgrRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
    logging::get() << "[" << request.clientAddress().toString() << "][METHOD: " << request.getMethod() << "] request: " << request.getURI() << std::endl;

    std::string action;
    auto query = getQuery(request.getURI());
    if(query.has("action"))
    {
        action = query.get("action");
    }

    if(action.empty() && request.getURI() == "/")
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
    else if(request.getURI().rfind('.') != std::string::npos)
    {
        std::string resolvedResource = "static/" + request.getURI().substr(1);
        std::string ext = request.getURI().substr(request.getURI().rfind('.')+1);
        std::string contentType;
        if(ext == "js")
        {
            contentType = "application/javascript";
        }
        else if(ext == "css")
        {
            contentType = "text/css";
        }
        else if(ext == "html")
        {
            contentType = "text/html";
        }
        else if(ext == "png")
        {
            contentType = "image/png";
        }
        else if(ext == "jpg" || ext == "jpeg")
        {
            contentType = "image/jpeg";
        }

        if(!contentType.empty())
        {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            response.setContentType(contentType);

            std::ifstream file(resolvedResource, std::ifstream::in);
            std::string content = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

            std::ostream& out = response.send();
            out << content;
            out.flush();
        }
        else
        {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        }
        return;
    }
    else
    {
        page = new FileNotFoundPage();
    }

    response.setContentType("text/html");

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

    std::string pageContents = ss.str();
    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
    std::ostream& outStream = response.send();
    outStream << ss.str();
    outStream.flush();
}
