#include "HttpHeader.h"

namespace Http {

HttpHeader::HttpHeader() {}

HttpHeader::HttpHeader(const HttpHeader& http_header) : headers_map(http_header.headers_map) {
    if(http_header.data){
        data = std::make_unique<std::string>(*http_header.data);
    }
}

HttpHeader::HttpHeader(HttpHeader&& http_header) : headers_map(std::move(http_header.headers_map)), data {std::move(http_header.data)} {}

HttpHeader::~HttpHeader() {}

HttpHeader& HttpHeader::operator=(const HttpHeader& http_header) {
    if (this == &http_header) {
        return *this;
    }

    headers_map = http_header.headers_map;
    data.reset();

    if (http_header.data) {
        data = std::make_unique<std::string>(*http_header.data);
    }

    return *this;
}

HttpHeader& HttpHeader::operator=(HttpHeader&& http_header) {
    if (this == &http_header) {
        return *this;
    }

    headers_map = std::move(http_header.headers_map);
    data = std::move(http_header.data);

    return *this;
}

const std::string& HttpHeader::get_header(Header header) const noexcept {
    static const std::string empty_header {"" };
    std::string header_str = to_string(header);
    
    const auto it = headers_map.find(header_str);
    return it == headers_map.end() ? empty_header : it->second;
}

const std::string& HttpHeader::operator[](Header header) const noexcept {
    return get_header(header);
}

std::string& HttpHeader::operator[](Header header) {
    return headers_map[to_string(header)];
}

const std::string& HttpHeader::get_header(const std::string& header) const noexcept {
    static const std::string empty_header {""};
    std::string header_low = change_case(header);

    const auto it = headers_map.find(header_low);
    return it == headers_map.end() ? empty_header : it->second;
}

const std::string& HttpHeader::operator[](const std::string& header) const noexcept {
    return get_header(header);
}

std::string& HttpHeader::operator[](const std::string& header) {
    std::string header_low = change_case(header);
    return headers_map[header_low];
}

void HttpHeader::add_header(Header header, const std::string& _val) {
    headers_map[to_string(header)] = _val;
}

void HttpHeader::add_header(const std::string& header, const std::string& val) {
    headers_map[change_case(header)] = val;
}

void HttpHeader::set_data(const std::string &_data) {
    data = std::make_unique<std::string>(_data);
}

const std::string& HttpHeader::get_data() const noexcept {
    if(data){
        return *data;
    }else{
        static const std::string empty_data {""};
        return empty_data;    
    }
}

void HttpHeader::append_data(const std::string &_data) {
    if (!data) {
        data = std::make_unique<std::string>(_data);
    } else {
        data->append(_data);
    }
}

void HttpHeader::append_data(const char *_data) {
    if (!_data) {
        return;
    }else if (!data) {
        data = std::make_unique<std::string>(_data);
    } else {
        data->append(_data);
    }
}

void HttpHeader::append_data(const char *_data, const size_t len) {
    if (!_data) {
        return;
    }else if (!data) {
        data = std::make_unique<std::string>();
    }
    
    data->append(_data, len);
}

size_t HttpHeader::data_len() const noexcept {
    return (!data ? 0 : data->length());
}

bool HttpHeader::contain_header(Http::Header header) const noexcept {
    const char* header_str = to_string(header);
    return headers_map.count(header_str) > 0;
}

size_t HttpHeader::content_len() const {
    const std::string content_len = to_string(Http::Header::CONTENT_LENGTH);
    const auto it = headers_map.find(content_len);
    return it == headers_map.end() ? 0 : static_cast<size_t>(std::stoi(it->second));
}

void HttpHeader::set_host(const std::string& host){
    headers_map[to_string(Header::HOST)] = host;
}

const std::string& HttpHeader::get_host() const noexcept{
    const auto it = headers_map.find(to_string(Header::HOST));
    
    if(it != headers_map.end()){
        return it->second;
    }else{
        static std::string empty_header{""};
        return empty_header;
    }
}

std::string HttpHeader::get_string() const {
    std::string result {};

    for (const auto &p : headers_map) {
        result.append(p.first).append(HEADER_SEPARATOR).append(p.second).append(CRLF);
    }
    result.append(CRLF);

    if (data) {
        result.append(*data);
    }

    return result;
}

void HttpHeader::add_header(const std::string& header){
    std::vector<std::string> tokens = tokenize(header, ':', true);
    if (tokens.size() != 2) {
        throw std::runtime_error("invalid header : " + header);
    }
    add_header(tokens[0], tokens[1]);
}

}
