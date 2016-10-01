//
// Created by inside on 3/12/16.
//

#ifndef HTTPSERVER_HTTPREQUEST_H
#define HTTPSERVER_HTTPREQUEST_H

#include "HttpHeader.h"
#include "HttpUrl.h"

namespace Http {

class EXPORT_HTTP HttpRequest : public HttpHeader {
public:
    HttpRequest();
    HttpRequest(const HttpUrl& url, Method method = Method::GET);
    HttpRequest(HttpUrl&& url, Method method = Method::GET);
    HttpRequest(const HttpRequest& request);
    HttpRequest(HttpRequest&& request);

    virtual ~HttpRequest();
    
    HttpRequest& operator=(const HttpRequest& http_request);
    HttpRequest& operator=(HttpRequest&& http_request);

    void set_method(Http::Method _method);
    Http::Method get_method() const;

    void set_url(const HttpUrl& url, Method method = Method::GET);
    void set_url(HttpUrl&& url, Method method = Method::GET);
    const HttpUrl& get_url() const noexcept;

    virtual std::string get_string() const override;
private:
    class HttpClient;
    friend HttpClient;
    
    HttpRequest(const std::string& request);
    void parse(const std::string& request);
    
    Method m_method = Method::UNKNOWN;
    HttpUrl m_url{};
};

}

#endif //HTTPSERVER_HTTPREQUEST_H
