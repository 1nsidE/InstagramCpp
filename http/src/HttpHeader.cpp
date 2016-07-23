#include "HttpHeader.h"

namespace Http{

    HttpHeader::HttpHeader(){}

    HttpHeader::HttpHeader(const HttpHeader& http_header) : headers_map(http_header.headers_map),
                                                            data{http_header.data == nullptr ? nullptr : new std::string{*http_header.data}}{}

    HttpHeader::HttpHeader(HttpHeader&& http_header) : headers_map(std::move(http_header.headers_map)), data{http_header.data} {
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

        return *this;
    }

    HttpHeader& HttpHeader::operator=(HttpHeader&& http_header){
        if(this == &http_header){
            return *this;
        }

        headers_map = std::move(http_header.headers_map);
        data = http_header.data;
        http_header.data = nullptr;

        return *this;
    }

    const std::string& HttpHeader::get_header(Header header) const noexcept {
        static const std::string empty_header{""};
        std::string header_str = to_string(header);
        return headers_map.count(header_str) ? headers_map.at(header_str) : empty_header;
    }

    const std::string& HttpHeader::operator[](Header header) const noexcept {
        return get_header(header);
    }

    std::string& HttpHeader::operator[](Header header){
        return headers_map[to_string(header)];
    }

    const std::string& HttpHeader::get_header(const std::string& header) const noexcept{
        static const std::string empty_header{""};
        std::string header_low = change_case(header);
        return headers_map.count(header_low) ? headers_map.at(header_low) : empty_header;
    }

    const std::string& HttpHeader::operator[](const std::string& header) const noexcept{
        return get_header(change_case(header));
    }

    std::string& HttpHeader::operator[](const std::string& header){
        std::string header_low = change_case(header);
        return headers_map[header_low];
    }

    void HttpHeader::add_header(Header header, const std::string& _val){
        headers_map[to_string(header)] = _val;
    }

    void HttpHeader::add_header(const std::string& header, const std::string& val){
        headers_map[change_case(header)] = val;
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

    void HttpHeader::append_data(const char *_data) {
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
        const char* header_str = to_string(header);
        return headers_map.count(header_str) > 0;
    }

    size_t HttpHeader::content_len() const {
        const std::string content_len = to_string(Http::Header::CONTENT_LENGTH);
        return headers_map.count(content_len) ? static_cast<size_t>(std::stoi(headers_map.at(content_len))) : 0;
    }

    std::string HttpHeader::get_string() const{
        std::string result{};

        for(const auto &p : headers_map){
            result.append(p.first).append(HEADER_SEPARATOR).append(p.second).append(CRLF);
        }
        result.append(CRLF);

        if(data != nullptr){
            result.append(*data);
        }

        return result;
    }

}
