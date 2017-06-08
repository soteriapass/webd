#include "handler.h"
#include <sstream>
#include <iostream>

#include "pages/display.h"
#include "pages/filenotfound.h"
#include "pages/index.h"
#include "pages/login.h"
#include "pages/parser.h"

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

    if(request.getURI().rfind('.') != std::string::npos)
    {
        int queryStart = request.getURI().rfind('?');
        if(queryStart == std::string::npos)
        {
            queryStart = request.getURI().size();
        }
        std::string resolvedResource = "static/" + request.getURI().substr(1, queryStart-1);

        int extIndexStart = request.getURI().rfind('.');
        std::string ext = request.getURI().substr(extIndexStart + 1, queryStart - extIndexStart - 1);
        std::string contentType;

        logging::get() << "\tResolved Resource: " << resolvedResource << std::endl;
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
        else if(ext == "cshtml")
        {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            response.setContentType("text/html");

            Parser parser;
            std::stringstream ss;
            if(page != nullptr)
            {
                page->RegisterParsers(parser);
            }
            parser.Parse(resolvedResource, ss);

            if(page != nullptr)
            {
                page->HeaderContent(ss);
                page->Page(ss);
            }

            std::ostream& out = response.send();
            out << ss.str();
            out.flush();
            return;
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
    if(page == nullptr)
    {
        page = new FileNotFoundPage();
    }

    response.setContentType("text/html");

    std::stringstream ss;
    page->HeaderContent(ss);
    page->Page(ss);

    delete page;
    page = nullptr;

    std::string pageContents = ss.str();
    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
    std::ostream& outStream = response.send();
    outStream << ss.str();
    outStream.flush();
}
