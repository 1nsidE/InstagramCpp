//
// Created by inside on 3/12/16.
//

#ifndef HTTPSERVER_HTTPREQUEST_H
#define HTTPSERVER_HTTPREQUEST_H

#include <map>
#include "HttpHeader.h"
#include "HttpUrl.h"

namespace Http{

class HttpRequest : public HttpHeader{
public:
    HttpRequest();
    HttpRequest(const HttpRequest& request);
    HttpRequest(HttpRequest&& request);
	
    virtual ~HttpRequest();

	HttpRequest& operator=(const HttpRequest& http_request);
	HttpRequest& operator=(HttpRequest&& http_request);

    void set_method(Http::Method _method);
	Http::Method get_method() const;
    void set_url(const HttpUrl& url);
    void set_url(HttpUrl&& url);
    const HttpUrl& get_url() const;

    virtual std::string get_string() const override;
private:
	Http::Method method;
    HttpUrl url;
};

}

#endif //HTTPSERVER_HTTPREQUEST_H
