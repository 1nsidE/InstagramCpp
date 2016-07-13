#ifndef HTTP_HEADER_H
#define HTTP_HEADER_H

#include <string>
#include <unordered_map>
#include <memory>
#include "Http.h"

namespace Http{

using HeadersMap = std::unordered_map<Http::Header, std::string, Http::enum_hash>;

class HttpHeader{
public:
    virtual ~HttpHeader();

    const std::string& get_header(Header header) const noexcept;
    std::string& get_header(Header header);

    const std::string& operator[](Header header) const noexcept;
    std::string& operator[](Header header);

    void add_header(Header header, const std::string& _val);    

    const std::string& get_data() const noexcept;
    void set_data(const std::string& data);
    void append_data(const std::string& _data);
    void append_data(const char* _data);
    void append_data(const char *_data, const size_t len);
    size_t data_len() const noexcept;

    bool contain_header(Header header) const noexcept;

    virtual size_t content_len() const;
    virtual std::string get_string() const;
protected:
    HttpHeader();
    HttpHeader(const HttpHeader& http_header);
    HttpHeader(HttpHeader&& http_header);
    
    HttpHeader& operator=(const HttpHeader& http_heade);
    HttpHeader& operator=(HttpHeader&& http_header);

    HeadersMap headers_map{};
    std::string* data = nullptr;
};

}
#endif
