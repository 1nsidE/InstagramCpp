#ifndef HTTP_RESPONSE_HEADER
#define HTTP_RESPONSE_HEADER

#include "HttpHeader.h"

namespace Http{

class HttpResponse : public HttpHeader{
public:
    HttpResponse();
    HttpResponse(HttpResponse& response);
    HttpResponse(HttpResponse&& response);

    virtual ~HttpResponse();

    HttpResponse& operator=(HttpResponse&& http_response);
	HttpResponse& operator=(const HttpResponse& http_response);
	
    virtual std::string get_string() const;
    Http::Status get_status() const;
    void set_status(Http::Status _status);
private:
    Http::Status status;
};

}

#endif
