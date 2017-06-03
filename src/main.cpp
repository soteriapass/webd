#include "handler.h"
#include <signal.h>

#include <iostream>
#include <chrono>
#include <thread>

#include "utilities.h"

bool stop = false;

void sighnd(int sig)
{
    stop = true;
}

int main() {
    signal(SIGINT,  sighnd);
    signal(SIGILL,  sighnd);
    signal(SIGKILL, sighnd);

    Net::Address addr(Net::Ipv4::any(), Net::Port(9090));

    auto opts = Net::Http::Endpoint::options().threads(1);
    //opts.flags(Net::Tcp::Options::InstallSignalHandler);
    Net::Http::Endpoint server(addr);
    server.init(opts);
    auto handler = std::make_shared<HelloHandler>();
    handler->Init(server);
    server.setHandler(handler);
    server.serveThreaded();
    while(!stop)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    //std::cout << "Calling server.shutdown();" << std::endl;
    server.shutdown();
}
