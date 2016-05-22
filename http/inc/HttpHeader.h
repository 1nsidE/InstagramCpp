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

    virtual void add_header(Header header, const std::string& _val);
    virtual const std::string& get_header(Header header) const noexcept;
     
    HttpHeader& operator[](Header header) noexcept;
    HttpHeader& operator=(const std::string& value);
    
    const std::string& operator[](Header header) const noexcept;

    virtual std::string get_data();
    virtual const std::string& get_data() const noexcept;
    virtual void set_data(const std::string& data);
    virtual void append_data(const std::string& _data);
    virtual void append_data(const char* _data) noexcept;
    virtual void append_data(const char *_data, const size_t len);
    virtual size_t data_len() const noexcept;

    virtual bool contain_header(Header header) const noexcept;
    virtual size_t content_len() const;
    
    virtual std::string get_string() const;
protected:
    HttpHeader();
    HttpHeader(const HttpHeader& http_header);
    HttpHeader(HttpHeader&& http_header);
    
    virtual HttpHeader& operator=(const HttpHeader& http_heade);
    virtual HttpHeader& operator=(HttpHeader&& http_header);

    HeadersMap headers_map;
    std::string* data;

    Header tmp_header;
};

}
#endif
