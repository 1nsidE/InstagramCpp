#include "HttpHeader.h"

namespace Http {

HttpHeader::HttpHeader() {}

HttpHeader::HttpHeader(const HttpHeader& httpHeader) : m_headersMap{httpHeader.m_headersMap} {
    if(httpHeader.m_data){
        m_data = std::make_unique<std::string>(*httpHeader.m_data);
    }
}

HttpHeader::HttpHeader(HttpHeader&& httpHeader) : HttpHeader{}{
    swap(*this, httpHeader);
}

HttpHeader::~HttpHeader() {}

HttpHeader& HttpHeader::operator=(const HttpHeader& httpHeader) {
    HttpHeader copy{httpHeader};

    swap(*this, copy);
    return *this;
}

HttpHeader& HttpHeader::operator=(HttpHeader&& httpHeader) {
    swap(*this, httpHeader);
    
    HttpHeader temp{};
    swap(httpHeader, temp);
    return *this;
}

const std::string& HttpHeader::getHeader(Header header) const noexcept {
    static const std::string emptyHeader {"" };
    std::string header_str = toString(header);
    
    const auto it = m_headersMap.find(header_str);
    return it == m_headersMap.end() ? emptyHeader : it->second;
}

const std::string& HttpHeader::operator[](Header header) const noexcept {
    return getHeader(header);
}

std::string& HttpHeader::operator[](Header header) {
    return m_headersMap[toString(header)];
}

const std::string& HttpHeader::getHeader(const std::string& header) const noexcept {
    static const std::string emptyHeader {""};
    std::string header_low = changeCase(header);

    const auto it = m_headersMap.find(header_low);
    return it == m_headersMap.end() ? emptyHeader : it->second;
}

const std::string& HttpHeader::operator[](const std::string& header) const noexcept {
    return getHeader(header);
}

std::string& HttpHeader::operator[](const std::string& header) {
    std::string header_low = changeCase(header);
    return m_headersMap[header_low];
}

void HttpHeader::addHeader(Header header, const std::string& _val) {
    m_headersMap[toString(header)] = _val;
}

void HttpHeader::addHeader(const std::string& header, const std::string& val) {
    m_headersMap[changeCase(header)] = val;
}

void HttpHeader::setData(const std::string &data) {
    m_data = std::make_unique<std::string>(data);
}

const std::string& HttpHeader::data() const noexcept {
    if(m_data){
        return *m_data;
    }else{
        static const std::string emptydata {""};
        return emptydata;    
    }
}

void HttpHeader::appendData(const std::string &data) {
    if (!m_data) {
        m_data = std::make_unique<std::string>(data);
    } else {
        m_data->append(data);
    }
}

void HttpHeader::appendData(const char *data) {
    if (!data) {
        return;
    }else if (!m_data) {
        m_data = std::make_unique<std::string>(data);
    } else {
        m_data->append(data);
    }
}

void HttpHeader::appendData(const char *data, const size_t len) {
    if (!data) {
        return;
    }else if (!m_data) {
        m_data = std::make_unique<std::string>(data, len);
    }else{
        m_data->append(data, len);
    }
}

size_t HttpHeader::dataLen() const noexcept {
    return (m_data ? m_data->length() : 0);
}

bool HttpHeader::isContainsHeader(Http::Header header) const noexcept {
    const char* header_str = toString(header);
    return m_headersMap.count(header_str) > 0;
}

size_t HttpHeader::contentLen() const {
    const std::string content_len = toString(Http::Header::CONTENT_LENGTH);
    const auto it = m_headersMap.find(content_len);
    return it == m_headersMap.end() ? 0 : static_cast<size_t>(std::stoi(it->second));
}

void HttpHeader::setHost(const std::string& host){
    m_headersMap[toString(Header::HOST)] = host;
}

const std::string& HttpHeader::host() const noexcept{
    const auto it = m_headersMap.find(toString(Header::HOST));
    
    if(it != m_headersMap.end()){
        return it->second;
    }else{
        static std::string emptyHeader{""};
        return emptyHeader;
    }
}

std::string HttpHeader::getString() const {
    std::string result {};

    for (const auto &p : m_headersMap) {
        result.append(p.first).append(HEADER_SEPARATOR).append(p.second).append(CRLF);
    }
    result.append(CRLF);

    if (m_data) {
        result.append(*m_data);
    }

    return result;
}

void HttpHeader::addHeader(const std::string& header){
    std::vector<std::string> tokens = tokenize(header, ':', true);
    if (tokens.size() != 2) {
        throw std::runtime_error("invalid header : " + header);
    }
    addHeader(tokens[0], tokens[1]);
}

void swap(HttpHeader& first, HttpHeader& second){
    using std::swap;
    swap(first.m_headersMap, second.m_headersMap);
    swap(first.m_data, second.m_data);
}

}
