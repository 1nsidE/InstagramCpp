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
    virtual ~HttpHeader() = default;
    
    virtual void add_header(Header header, const std::string& _val){
        headers_map[header] = _val;
    }

    virtual const std::string& get_header(Header header) const noexcept {
        static const std::string empty_header{""};
        if(headers_map.count(header)){
            return headers_map.at(header);
        }else{
            return empty_header;
        }
    }

    virtual std::string operator[](Header header) noexcept {
        return get_header(header);
    }

    virtual const std::string& operator[](Header header) const noexcept {
        return get_header(header);
    }
    
    virtual void set_data(const std::string& data) = 0;
    virtual std::string get_data() = 0;
    virtual const std::string& get_data() const = 0;

    virtual std::string get_string() const = 0;

protected:
    HttpHeader() = default;
    HttpHeader(const HttpHeader& http_header) : headers_map(http_header.headers_map){}
    HttpHeader(HttpHeader&& http_header) : headers_map(std::move(http_header.headers_map)){}
    HeadersMap headers_map;
};

}
#endif
