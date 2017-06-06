#include <signal.h>

#include <iostream>
#include <chrono>
#include <thread>

#include "log.h"
#include "utilities.h"

#include "handlerfactory.h"

#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Util/ServerApplication.h>

class PswmgrServerApp : public Poco::Util::ServerApplication
{
protected:
    int main(const std::vector<std::string> &)
    {
        Poco::Net::HTTPServerParams* pParams = new Poco::Net::HTTPServerParams();
        pParams->setMaxQueued(128);
        pParams->setMaxThreads(16);

        Poco::Net::ServerSocket svs(9090);
        Poco::Net::HTTPServer s(new PswmgrRequestHandlerFactory, svs, pParams);

        s.start();
        logging::get() << "Soteria Password Web Server started" << std::endl;

        waitForTerminationRequest();  // wait for CTRL-C or kill

        logging::get() << "Shutting down..." << std::endl;
        s.stop();

        return Application::EXIT_OK;
    }
};

int main(int argc, char** argv) 
{
    conf _conf;
    if(!logging::init(_conf))
    {
        std::cout << "Couldn't initialize logging" << std::endl;
        return -1;
    }

    PswmgrServerApp app;
    auto ret = app.run(argc, argv);

    logging::destroy();

    return ret;
}
