#include "pistache/endpoint.h"
#include "pistache/http_header.h"
#include "pistache/router.h"

class HelloHandler : public Net::Http::Handler {
public:

    HTTP_PROTOTYPE(HelloHandler)

    void Init(Net::Http::Endpoint& endpoint);

    void onRequest(const Net::Http::Request& request, Net::Http::ResponseWriter response);
    void onLogin(const Net::Rest::Request& request, Net::Http::ResponseWriter response);
private:
    Net::Rest::Router m_Router;
};

