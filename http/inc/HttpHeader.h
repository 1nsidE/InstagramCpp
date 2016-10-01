#ifndef HTTP_HEADER_H
#define HTTP_HEADER_H

#include <unordered_map>
#include <memory>
#include "Http.h"

namespace Http {
using HeadersMap = std::unordered_map<std::string, std::string>;

class EXPORT_HTTP HttpHeader {
public:
    virtual ~HttpHeader();

    const std::string& get_header(Header header) const noexcept;
    const std::string& operator[](Header header) const noexcept;
    std::string& operator[](Header header);

    const std::string& get_header(const std::string& header) const noexcept;
    const std::string& operator[](const std::string& header) const noexcept;
    std::string& operator[](const std::string& header);

    void add_header(Header header, const std::string& _val);
    void add_header(const std::string& header, const std::string& val);

    const std::string& get_data() const noexcept;
    void set_data(const std::string& data);
    void append_data(const std::string& _data);
    void append_data(const char* _data);
    void append_data(const char *_data, const size_t len);
    size_t data_len() const noexcept;

    bool contain_header(Header header) const noexcept;
    size_t content_len() const;

    void set_host(const std::string& host);
    const std::string& get_host() const noexcept;

    virtual std::string get_string() const;
protected:
    HttpHeader();
    HttpHeader(const HttpHeader& http_header);
    HttpHeader(HttpHeader&& http_header);

    HttpHeader& operator=(const HttpHeader& http_heade);
    HttpHeader& operator=(HttpHeader&& http_header);

    void add_header(const std::string& header);
private:
    HeadersMap headers_map {};

    using DataPtr = std::unique_ptr<std::string>;
    DataPtr data{};
};

}
#endif
