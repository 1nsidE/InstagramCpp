#include "HttpHeader.h"

namespace Http{

HttpHeader::HttpHeader() : headers_map{}, data{nullptr}, tmp_header{Header::UNKNOWN}{}

HttpHeader::HttpHeader(const HttpHeader& http_header) : headers_map(http_header.headers_map), 
    data{http_header.data == nullptr ? nullptr : new std::string{*http_header.data}},
    tmp_header{Header::UNKNOWN}{}

HttpHeader::HttpHeader(HttpHeader&& http_header) : headers_map(std::move(http_header.headers_map)), data{http_header.data}, tmp_header{Header::UNKNOWN} {
    http_header.data = nullptr;
}        

HttpHeader::~HttpHeader(){
    if(data != nullptr){
        delete data;
    }
}

HttpHeader& HttpHeader::operator=(const HttpHeader& http_header){
    if(this == &http_header){
        return *this;
    }
    headers_map = http_header.headers_map;

    if(data != nullptr){
        delete data;
        data = nullptr;
    }

    if(http_header.data != nullptr){
        data = new std::string{*http_header.data};
    }
    
    tmp_header = Header::UNKNOWN;
    return *this;
}

HttpHeader& HttpHeader::operator=(HttpHeader&& http_header){
    if(this == &http_header){
        return *this;
    }

    headers_map = std::move(http_header.headers_map);
    data = http_header.data;
    http_header.data = nullptr;
    
    tmp_header = Header::UNKNOWN;
    http_header.tmp_header = Header::UNKNOWN;

    return *this;
}

HttpHeader& HttpHeader::operator[](Header header) noexcept {
    tmp_header = header;
    return *this;
}

HttpHeader& HttpHeader::operator=(const std::string& value){
    if(tmp_header != Header::UNKNOWN){
        add_header(tmp_header, value);
        tmp_header = Header::UNKNOWN;
   }
   return *this;
}

void HttpHeader::add_header(Header header, const std::string& _val){
    headers_map[header] = _val;
}

const std::string& HttpHeader::get_header(Header header) const noexcept {
    static const std::string empty_header{""};
    if(headers_map.count(header)){
        return headers_map.at(header);
    }else{
        return empty_header;
    }
}

const std::string& HttpHeader::operator[](Header header) const noexcept {
    return get_header(header);
}

void HttpHeader::set_data(const std::string &_data){
    if(data == nullptr){
        data = new std::string{_data};
    }else{
        (*data) = _data;
    }
}

const std::string& HttpHeader::get_data() const noexcept{
    static const std::string empty_data{""};
    return data ? *data : empty_data;
}

void HttpHeader::append_data(const std::string &_data) {
    if(data == nullptr){
        data = new std::string{_data};
    }else{
        data->append(_data);
    }
}

void HttpHeader::append_data(const char *_data) noexcept {
    if(_data == nullptr){
        return;
    }    
    if(data == nullptr){
        data = new std::string{_data};
    }else{
        data->append(_data);
    }
}

void HttpHeader::append_data(const char *_data, const size_t len) {
    if(_data == nullptr){
        throw std::invalid_argument("data cannot be nullptr");
    }
    
    if(data == nullptr){
        data = new std::string{};
    }
    data->append(_data, len);
}

size_t HttpHeader::data_len() const noexcept{
    return (data == nullptr ? 0 : data->length());
}

bool HttpHeader::contain_header(Http::Header header) const noexcept {
    return headers_map.count(header) > 0;
}

size_t HttpHeader::content_len() const {
    return (headers_map.count(Http::Header::CONTENT_LENGTH) ? static_cast<size_t>(std::stoi(headers_map.at(Http::Header::CONTENT_LENGTH))) : 0);
}

std::string HttpHeader::get_string() const{
    std::string result{};

    for(const auto &p : headers_map){
        result.append(get_str(p.first)).append(p.second).append(CRLF);
    }
    result.append(CRLF);

    if(data != nullptr){
        result.append(*data);
    }
    
    return result;
}

}
