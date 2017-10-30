#ifndef HTTP_HEADER_H
#define HTTP_HEADER_H

#include <unordered_map>
#include <memory>
#include <stddef.h>
#include "Http.h"

namespace Http {

class EXPORT_HTTP HttpHeader {
public:
    using HeadersMap = std::unordered_map<std::string, std::string>;
    virtual ~HttpHeader();

    const std::string& getHeader(Header header) const noexcept;
    const std::string& getHeader(const std::string& header) const noexcept;

    const std::string& operator[](Header header) const noexcept;
    const std::string& operator[](const std::string& header) const noexcept;

    std::string& operator[](Header header);
    std::string& operator[](const std::string& header);

    void addHeader(Header header, const std::string& _val);
    void addHeader(const std::string& header, const std::string& val);

    const std::string& body() const noexcept;
    void setBody(const std::string& body);
    void appendBody(const std::string& _body);
    void appendBody(const char* _body);
    void appendBody(const char *_body, const std::size_t len);
    std::size_t bodySize() const noexcept;

    bool isContainsHeader(Header header) const noexcept;
    std::size_t contentLen() const;

    void setHost(const std::string& host);
    const std::string& host() const noexcept;

    virtual std::string getString() const;
protected:
    HttpHeader();
    HttpHeader(const HttpHeader& httpHeader);
    HttpHeader(HttpHeader&& httpHeader);

    HttpHeader& operator=(const HttpHeader& httpHeader);
    HttpHeader& operator=(HttpHeader&& httpHeader);
private:
    HeadersMap m_headersMap {};

    using BodyPtr = std::unique_ptr<std::string>;
    BodyPtr m_body{};

    friend void swap(HttpHeader& first, HttpHeader& second);
};

}
#endif
