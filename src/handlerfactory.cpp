#include "handlerfactory.h"
#include "handler.h"

Poco::Net::HTTPRequestHandler* PswmgrRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest &)
{
    return new PswmgrRequestHandler();
}
