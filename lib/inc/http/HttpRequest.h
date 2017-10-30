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

    virtual ~HttpRequest() override;
    
    HttpRequest& operator=(const HttpRequest& httpRequest);
    HttpRequest& operator=(HttpRequest&& httpRequest);

    void setMethod(Http::Method method);
    Http::Method method() const;

    void setUrl(const HttpUrl& url);
    void setUrl(HttpUrl&& url);

    const HttpUrl& getUrl() const noexcept;

    std::string getString() const override;
private:
    friend class HttpClient;
    
    HttpRequest(const std::string& request);
    void parse(const std::string& request);
    
    Method m_method = Method::UNKNOWN;
    HttpUrl m_url{};

    friend void swap(HttpRequest& first, HttpRequest& second);
};

}

#endif //HTTPSERVER_HTTPREQUEST_H
