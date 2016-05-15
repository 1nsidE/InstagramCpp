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

    virtual void set_data(const std::string& _data);
    virtual std::string get_data();
    virtual const std::string& get_data() const;

    void append_data(const std::string& _data);
    void append_data(const char* _data);
    void append_data(const char *_data, const size_t len);

    size_t data_len() const noexcept;
    size_t get_content_len() const;
    bool contain_header(Http::Header header) noexcept;

    void set_status(Http::Status _status);
	Http::Status get_status() const;
private:
    std::string* data;
    Http::Status status;
};

}

#endif
