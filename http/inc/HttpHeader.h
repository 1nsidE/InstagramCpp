#ifndef HTTP_HEADER_H
#define HTTP_HEADER_H

#include <unordered_map>
#include <memory>
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

    const std::string& data() const noexcept;
    void setData(const std::string& data);
    void appendData(const std::string& _data);
    void appendData(const char* _data);
    void appendData(const char *_data, const size_t len);
    size_t dataLen() const noexcept;

    bool isContainsHeader(Header header) const noexcept;
    size_t contentLen() const;

    void setHost(const std::string& host);
    const std::string& host() const noexcept;

    virtual std::string getString() const;
protected:
    HttpHeader();
    HttpHeader(const HttpHeader& httpHeader);
    HttpHeader(HttpHeader&& httpHeader);

    HttpHeader& operator=(const HttpHeader& httpHeader);
    HttpHeader& operator=(HttpHeader&& httpHeader);

    void addHeader(const std::string& header);
private:
    HeadersMap m_headersMap {};

    using DataPtr = std::unique_ptr<std::string>;
    DataPtr m_data{};

    friend void swap(HttpHeader& first, HttpHeader& second);
};

}
#endif
