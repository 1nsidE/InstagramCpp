#ifndef HTTP_RESPONSE_HEADER
#define HTTP_RESPONSE_HEADER

#include "HttpHeader.h"

namespace Http {
    
class HttpClient;    

class EXPORT_HTTP HttpResponse : public HttpHeader {
public:
    HttpResponse();
    HttpResponse(const HttpResponse& response);
    HttpResponse(HttpResponse&& response);

    virtual ~HttpResponse() override;

    HttpResponse& operator=(HttpResponse&& httpResponse);
    HttpResponse& operator=(const HttpResponse& httpResponse);
    HttpResponse& operator=(const std::string& response);

    const std::string& status() const noexcept;
    int code() const noexcept;
    
    void setStatus(Http::Status status);
    void setStatus(const std::string& status, int code);

    std::string getString() const override;
private:
    friend class HttpClient;

    HttpResponse(const std::string& response);
    void parseResponse(const std::string& response);
    
    std::string m_status{};
    int m_code{-1};

    friend void swap(HttpResponse& first, HttpResponse& second);
};

}
#endif
