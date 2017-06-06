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
    Poco::Net::HTTPServer s(new PswmgrRequestHandlerFactory, Poco::Net::ServerSocket(9090), new Poco::Net::HTTPServerParams);

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
